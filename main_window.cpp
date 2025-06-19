//#import "USBCAN32.dll"
#include <QIODevice>
#include "main_window.h"
#include "systec_can.h"
#include "qdebug.h"
#include "ui_main_window.h"
#include "can_adapter.h"
#include "validators.h"
/*
#include "QFile"
#include <QFileDialog>
#include <QtWidgets>
#include "qstring.h"
//Strings
#include <QValidator>
//CAN headers
#include <QCanBus>
#include <QCanBusFrame>
#include <QCanBusDeviceInfo>

//Systec
#include "Usbcan32.h"
#include "UsbCanLs.h"
#include "UsbCanUp.h"
*/

extern uint test2;
extern CAN_Adapter * CAN_Adapter_ptr_GLOBAL;

#include <ActiveQt/QAxWidget>
#include <QtCore>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 400);

    //----------------Word Testing----------------------------
/*
    QAxObject *pWord= new QAxObject("Word.Application");//открываем приложение
    QAxObject *pDoc = pWord->querySubObject("Documents");//получаем коллекцию документов

    QString wordFilePath = "D:\\worddoc.docx";//путь к файлу
    pDoc->dynamicCall("Open(QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,QVariant)", wordFilePath, false,false,false,"","",false);//добавляем свой документ в коллекцию

    QAxObject *pActiveDocument = pWord->querySubObject("ActiveDocument()");
    QAxObject *pRange = pActiveDocument->querySubObject("Range()");
    QAxObject *pFind = pRange->querySubObject("Find()");

    //замена строк
    QString sOld         = "[place_response_here]";
    QString sNew         = "resp11";
    bool bMatchCase      = false;
    bool bMatchWholeWord = false;
    bool bMatchWildCards = false;
    bool bReplaceAll     = false;
    QVariantList vl = { sOld, bMatchCase, bMatchWholeWord, bMatchWildCards, false, false, true, 1, false, sNew, bReplaceAll ? "2" : "1" };
    pFind->dynamicCall("Execute(QString,bool,bool,bool,bool,bool,bool,int,bool,QString,int)",vl);

    pActiveDocument->dynamicCall("SaveAs(const QString&)",wordFilePath); // сохраняем
    pWord->dynamicCall("Quit()");//выходим
*/
    CAN_Adapter::CAN_Adapter_ptr_set(CAN_Adapter_ptr);
    tUcanInitCanParam InitCanParam_p = {sizeof(tUcanInitCanParam), kUcanModeNormal, HIBYTE (USBCAN_BAUD_250kBit), LOBYTE (USBCAN_BAUD_250kBit), true, 0xFFFFFFFF, 0x00000000, 0, 0, 0};
    qDebug()<<"BaudRate_Init: "<<InitCanParam_p.m_dwBaudrate;
    CAN_Adapter_ptr->Init(InitCanParam_p);

    m_sequenceFileTimer->stop();

    auto m_hexIntegerValidator = new HexIntegerValidator(this);
    auto m_HexStringValidator = new HexStringValidator(this);
    ui->lineEdit_Tester_ID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_ECU_ID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Tracking_ID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Send_Data->setValidator(m_HexStringValidator);
    connect(ui->radioButton_testerPresent, &QRadioButton::clicked, this, [&](bool checked){//запуск тапймера testerPresent
        if(checked)
            m_testerPresentTimer->start(1000);
        else
            m_testerPresentTimer->stop();});
    connect(m_testerPresentTimer, &QTimer::timeout, [&](){//testerPresent
        CanMsgTxUDS = {TxUDSFrameId,(BYTE)(TxUDSFrameId>0xFFF ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD), 8, {0x02, 0x3E, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}, 0};
        auto ret = CAN_Adapter_ptr->SendMsg (CanMsgTxUDS);
        tracewindow.addText("Tx:  " + printCanMsg(CanMsgTxUDS)+"\n");
        if(ret)
            qDebug()<<"tester present Error:"<<(int) ret;
        ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Tx:  "+ MainWindow::printCanMsg(CanMsgTxUDS)+"\n");
    });

    connect(&Systec_CAN, &Systec_CAN::CANStatusChanged, this, &MainWindow::on_CANStatusChanged);//статус шины-CAN
    connect(&Systec_CAN, &Systec_CAN::CANUSBConnectStatusChanged, this, &MainWindow::on_CANUSBConnectStatusChanged);//статус USB-CAN

    m_busRxTimer->start(10);//запуск выгребалки из стека
    connect(m_busRxTimer, &QTimer::timeout, [&](){//вывод интересующих фреймов
            while (!CAN_Adapter_ptr->RxBufIsEmpty())
            {
                CanMsgRx = CAN_Adapter_ptr->ReadMsg();
                if(CanMsgRx.m_dwID == RxUDSFrameId)
                {
                    static qint32 multiFrameData_counter=0;
                    CanMsgRxUDS=CanMsgRx;
                    ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Rx:  " + printCanMsg(CanMsgRx)+"\n");
                    if((CanMsgRx.m_bData[0]) == (char) 0x10)// если мультифрейм
                    {
                        CanMsgRxUDS_Multi.clear();//очистить хранилище мультифрейма если это первый фрейм
                        //QString str(CanMsgRx.m_bData[1]);
                        //bool *ok=nullptr;
                        //multiFrameData_counter=str.toInt(ok, 10) - 6;
                        multiFrameData_counter=(CanMsgRx.m_bData[1])-6;//вычислить из скольки фрепймов он состоит, и установить соответствующий флаг-счетчик
                        CanMsgRxUDS_Multi.append(CanMsgRxUDS);
                        CanMsgTxUDS = {TxUDSFrameId,(BYTE)(TxUDSFrameId>0xFFF ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD), 8, {0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 0};//послать ответный фрейм о готовности приема мультифреймов
                        auto ret = CAN_Adapter_ptr->SendMsg (CanMsgTxUDS);
                        if(ret)
                            qDebug()<<"MultiFrame resp Error:"<<(int) ret;
                        else
                            ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Tx:  " + printCanMsg(CanMsgTxUDS)+"\n");
                    }
                    else if(multiFrameData_counter>0)//если флаг активен, то добавить запись в хранилище мультифрейма
                    {
                    CanMsgRxUDS_Multi.append(CanMsgRxUDS);
                    multiFrameData_counter-=7;
                    }
                }
                if(CanMsgRx.m_dwID == trackingFrameId)
                    ui->lineEdit_Tracking_Data->setText(printCanMsg(CanMsgRx));
            }
    });
    connect(m_sequenceFileTimer, &QTimer::timeout, [&](){if(!SequenceFile->atEnd()) sequenceFileProcessing(SequenceFile->readLine());});//конект таймер тика с вызовом обрабочтика sequence-файла
    connect(&settingswindow, &settingswindow::ConnectSettingsChange, this, &MainWindow::ConnectSettingsChange);

    connect(&Vul_Can, &vul_can::Vul_Can_readyRead, this, &MainWindow::recivedFrame);
    connect(&Systec_CAN, &Systec_CAN::recivedFrame, this, &MainWindow::recivedFrame); //это вывод всех приходящих фреймов
}

MainWindow::~MainWindow()
{
    pWord->dynamicCall("Quit()");//выходим
    delete ui;
}

void MainWindow::on_pushButton_Open_Sequence_clicked()
{
    //открытие текстового файла последовательности
    SequenceFile->setFileName(QFileDialog::getOpenFileName(this, "Open Sequence File", "C:/Users/Volgunov/Desktop"));
    if(!SequenceFile->open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"SequenceFile open ERROR";
    ui->label_3->setText(SequenceFile->fileName());

    //открытие шаблона вордовского файла для сохранения лога последовательности
    SequenceFileLogTemplate->setFileName(QFileDialog::getOpenFileName(this, "Open Sequence Log Template File", "C:/Users/Volgunov/Desktop"));
    if(!SequenceFileLogTemplate->open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"SequenceFileLogTemplate open ERROR";
    else
    {
        pWord= new QAxObject("Word.Application");//открываем приложение
        pDoc = pWord->querySubObject("Documents");//получаем коллекцию документов
        QString wordFilePath = SequenceFileLogTemplate->fileName();//путь к файлу
        pDoc->dynamicCall("Open(QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,QVariant)", wordFilePath, false,false,false,"","",false);//добавляем свой документ в коллекцию

        pActiveDocument = pWord->querySubObject("ActiveDocument()");
        pRange = pActiveDocument->querySubObject("Range()");
    }
    ui->label_6->setText(SequenceFileLogTemplate->fileName());

    //---------------WORD TEMPLATE--------------------------------------------
//    QString wordFilePath = SequenceFile->fileName().remove(".txt")+".docx";
//    //qDebug()<<wordFilePath;
//    pWord= new QAxObject("Word.Application");
//    pDoc = pWord->querySubObject("Documents");//получаем коллекцию документов
//    pDoc->dynamicCall("Open(QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,QVariant)", wordFilePath, false,false,false,"","",false);//добавляем свой документ в коллекцию

//    pActiveDocument = pWord->querySubObject("ActiveDocument()");
//    pRange = pActiveDocument->querySubObject("Range()");
//    pFind = pRange->querySubObject("Find()");

//    pRange->dynamicCall("SetRange(int,int)", "start", "end");
//    pRange->setProperty("Text", "Print_____Text____Range.");

//    QString sOld         = "old";
//    QString sNew         = "new";
//    bool bMatchCase      = false;
//    bool bMatchWholeWord = false;
//    bool bMatchWildCards = false;
//    bool bReplaceAll     = false;
//    QVariantList vl = { sOld, bMatchCase, bMatchWholeWord, bMatchWildCards, false, false, true, 1, false, sNew, bReplaceAll ? "2" : "1" };
//    pFind->dynamicCall("Execute(QString,bool,bool,bool,bool,bool,bool,int,bool,QString,int)",vl);

//    pActiveDocument->dynamicCall("SaveAs(const QString&)",wordFilePath); // сохраняем
//    pWord->dynamicCall("Quit()");//выходим
}


void MainWindow::on_lineEdit_Tester_ID_editingFinished()
{
    TxUDSFrameId = ((ui->lineEdit_Tester_ID->text()).toUInt(0, 16));
    //qDebug()<<TxUDSFrameId;
    ui->lineEdit_Tester_ID->setText("0x"+QString("%1").arg(TxUDSFrameId,0,16).toUpper());
}

void MainWindow::on_lineEdit_ECU_ID_editingFinished()
{
    RxUDSFrameId = ((ui->lineEdit_ECU_ID->text()).toUInt(0, 16));
    ui->lineEdit_ECU_ID->setText("0x"+QString("%1").arg(RxUDSFrameId,0,16).toUpper());
}


void MainWindow::on_pushButton_Send_clicked()
{
    QByteArray Payload=QByteArray::fromHex((ui->lineEdit_Send_Data->text()).remove(QLatin1Char(' ')).toLatin1());
    CanMsgTxUDS.m_dwID = TxUDSFrameId;
    CanMsgTxUDS.m_bFF = (TxUDSFrameId>0xFFF ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD);
    for(int i=0; i<Payload.length(); i++)
        CanMsgTxUDS.m_bData[i]=Payload[i];
    CanMsgTxUDS.m_bDLC =sizeof(CanMsgTxUDS.m_bData);
    CanMsgTxUDS.m_dwTime = 0;
    auto ret = CAN_Adapter_ptr->SendMsg (CanMsgTxUDS);
    if(ret)
        qDebug()<<"Push Button Send Error:"<<(int) ret;
    ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Tx:  "+ MainWindow::printCanMsg(CanMsgTxUDS)+"\n");
    tracewindow.addText("Tx:  " + printCanMsg(CanMsgTxUDS)+"\n");
    //TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //vul_can::SendMsgTest(CanMsgTxUDS);
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_TesterECU_Excahge->clear();
}

void MainWindow::on_lineEdit_Tracking_ID_editingFinished()
{
    trackingFrameId = ((ui->lineEdit_Tracking_ID->text()).toUInt(0, 16));
    ui->lineEdit_Tracking_ID->setText("0x"+QString("%1").arg(trackingFrameId,0,16).toUpper());
    ui->lineEdit_Tracking_Data->clear();
}

void MainWindow::on_lineEdit_Send_Data_editingFinished()
{
    ui->lineEdit_Send_Data->setText(ui->lineEdit_Send_Data->text().toUpper());
}

void MainWindow::on_plainTextEdit_TesterECU_Excahge_textChanged()
{
    ui->plainTextEdit_TesterECU_Excahge->verticalScrollBar()->setValue(ui->plainTextEdit_TesterECU_Excahge->verticalScrollBar()->maximum());//автосдвиг
}

void MainWindow::on_pushButton_Play_Sequence_clicked()
{
    if(!m_sequenceFileTimer->isActive() && SequenceFile->exists())//вызов обработчика файла
    {
        ui->pushButton_Play_Sequence->setText("PauseSequence");
        m_sequenceFileTimer->start(1);
        ui->progressBar->setValue(0);
    }
    else if (m_sequenceFileTimer->isActive() && SequenceFile->exists())
    {
        ui->pushButton_Play_Sequence->setText("ResumeSequence");
        m_sequenceFileTimer->stop();
    }
}

void MainWindow::on_CANStatusChanged(tStatusStruct* pStatus_p)
{
    switch(pStatus_p->m_wCanStatus){
        case USBCAN_CANERR_OK:
        {
        ui->label_7->setText("BusStatus: Ok");
        break;
        }
        case USBCAN_CANERR_XMTFULL:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_XMTFULL");
        break;
        }
        case USBCAN_CANERR_OVERRUN:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_OVERRUN");
        break;
        }
        case USBCAN_CANERR_BUSLIGHT:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_BUSLIGHT");
        break;
        }
        case USBCAN_CANERR_BUSHEAVY:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_BUSHEAVY");
        break;
        }
        case USBCAN_CANERR_BUSOFF:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_BUSOFF");
        break;
        }
        case USBCAN_CANERR_QOVERRUN:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_QOVERRUN");
        break;
        }
        case USBCAN_CANERR_QXMTFULL:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_QXMTFULL");
        break;
        }
        case USBCAN_CANERR_REGTEST:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_REGTEST");
        break;
        }
        case USBCAN_CANERR_MEMTEST:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_MEMTEST");
        break;
        }
        case USBCAN_CANERR_TXMSGLOST:
        {
        ui->label_7->setText("BusStatus: USBCAN_CANERR_TXMSGLOST");
        break;
        }
        default:
        break;
    }
    ui->label_5->setText(CAN_Adapter_ptr->DeviceInfo());
}

void MainWindow::on_CANUSBConnectStatusChanged(int bEvent_p)
{
    switch(bEvent_p){
        case USBCAN_EVENT_CONNECT:
        {
        ui->label_7->setText("BusStatus: Connected");
        break;
        }
        case USBCAN_EVENT_DISCONNECT:
        {
        ui->label_7->setText("BusStatus: Disconnected");
        break;
        }
        case USBCAN_EVENT_FATALDISCON:
        {
        ui->label_7->setText("BusStatus: Fatal Disconnected");
        break;
        }
        default:
        break;
    }
}

void MainWindow::recivedFrame(tCanMsgStruct *CanMsgRx)//это вывод всех приходящих фреймов
{
    //ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Rx:  " + printCanMsg(*CanMsgRx)+"\n");//это вывод всех приходящих фреймов
    tracewindow.addText("Rx:  " + printCanMsg(*CanMsgRx)+"\n");
    if(CanMsgRx->m_dwID == trackingFrameId)
        ui->lineEdit_Tracking_Data->setText(printCanMsg(*CanMsgRx));
}

void MainWindow::sequenceFileProcessing(const QString &SequenceFileStr)
{
    m_sequenceFileTimer->stop();
    //qDebug()<<SequenceFileStr;
    if(SequenceFileStr.isEmpty())
        return;
    ui->progressBar->setValue(100* SequenceFile->pos()/SequenceFile->size());
    if(SequenceFileStr.startsWith("//") || SequenceFileStr.startsWith('\n'))//коммент или пустая строка
    {
        m_sequenceFileTimer->start(1);
        return;
    }
    if(SequenceFileStr.startsWith("[time]:"))//задача временной задержки в файле сценария
    {
        auto tmpStr=SequenceFileStr.simplified();//удалил пробелы
        tmpStr=tmpStr.remove("[time]:");
        tmpStr=tmpStr.remove('\n');
        m_sequenceFileTimer->start(tmpStr.toInt());
        return;
    }
    if(SequenceFileStr.startsWith("[req]:"))//задача запроса на отправку
    {
        auto tmpStr=SequenceFileStr;
        tmpStr=tmpStr.remove("[req]:");
        tmpStr=tmpStr.remove('\n');
        tmpStr=tmpStr.remove(' ');

        QByteArray Payload=QByteArray::fromHex(tmpStr.toLatin1());
        CanMsgTxUDS.m_dwID = TxUDSFrameId;
        CanMsgTxUDS.m_bFF = (TxUDSFrameId>0xFFF ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD);
        for(int i=0; i<Payload.length(); i++)
            CanMsgTxUDS.m_bData[i]=(BYTE)Payload[i];
        CanMsgTxUDS.m_bDLC =sizeof(CanMsgTxUDS.m_bData);
        CanMsgTxUDS.m_dwTime = 0;
        auto ret = CAN_Adapter_ptr->SendMsg (CanMsgTxUDS);
        if(ret)
            qDebug()<<"Sequence File Send Error:"<<(int) ret;
        ui->plainTextEdit_TesterECU_Excahge->insertPlainText("Tx:  "+ MainWindow::printCanMsg(CanMsgTxUDS)+"\n");
        m_sequenceFileTimer->start(1);
        return;
    }
    if(SequenceFileStr.startsWith("[resp]:") && SequenceFileLogTemplate->exists())//
    {
        pFind = pRange->querySubObject("Find()");
        QString sOld = "[place_response_here]";
        QString sNew = "";
        qint8 i=0;
        if(CanMsgRxUDS_Multi.isEmpty())
            (sNew=printCanMsg(CanMsgRxUDS));
        else
            while(i<CanMsgRxUDS_Multi.size())
            {
                //qDebug()<<"isEmpty: "<<CanMsgRxUDS_Multi.isEmpty();
                //qDebug()<<"SIZE: "<<CanMsgRxUDS_Multi.size();
                //qDebug()<<"i: "<<i;
                //qDebug()<<printCanMsg(CanMsgRxUDS_Multi[i]);
                sNew=sNew+printCanMsg(CanMsgRxUDS_Multi[i])+'\n';//?????????????????????????????????????????????'\n'
                i++;
            }
        CanMsgRxUDS_Multi.clear();//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
        bool bMatchCase      = false;
        bool bMatchWholeWord = false;
        bool bMatchWildCards = false;
        bool bReplaceAll     = false;
        QVariantList vl = { sOld, bMatchCase, bMatchWholeWord, bMatchWildCards, false, false, true, 1, false, sNew, bReplaceAll ? "2" : "1" };
        pFind->dynamicCall("Execute(QString,bool,bool,bool,bool,bool,bool,int,bool,QString,int)",vl);
           m_sequenceFileTimer->start(1);
        return;
    }
    if(SequenceFileStr.startsWith("[end]") && SequenceFileLogTemplate->exists())//конец в файле сценария
    {
        ui->pushButton_Play_Sequence->setText("PlaySequence");
        ui->progressBar->setValue(100);
        m_sequenceFileTimer->stop();
        SequenceFile->seek(0);

        static qint32 counter=0;
        counter++;

        QString fileName;
        if(SequenceFileLogTemplate->fileName().contains(".docx", Qt::CaseSensitive))
                fileName=(SequenceFileLogTemplate->fileName()).remove(".docx")+"_"+QString::number(counter,10)+".docx";
        else if (SequenceFileLogTemplate->fileName().contains(".doc", Qt::CaseSensitive))
                fileName=(SequenceFileLogTemplate->fileName()).remove(".doc")+"_"+QString::number(counter,10)+".doc";
        pActiveDocument->dynamicCall("SaveAs(const QString&)", fileName); // сохраняем
//        pWord->dynamicCall("Quit()");//выходим
        return;
    }
    m_sequenceFileTimer->start(1);
    return;
}

QString MainWindow::printCanMsg(const tCanMsgStruct &CanMsg)
{
    //qDebug()<<"MAIN WINDOW m_dwID"<<CanMsg.m_dwID;
    static QString tempStr;
    tempStr.clear();
    for(auto i=0; i<CanMsg.m_bDLC; i++)
    {
        tempStr=tempStr+(CanMsg.m_bData[i]>0x0F?"0x":"0x0")+QString::number(CanMsg.m_bData[i], 16).toUpper()+"  ";
    }
    tempStr="0x"+QString::number(CanMsg.m_dwID, 16)+"   "+"["+QString::number(CanMsg.m_bDLC)+"]"+"   "+tempStr;
    return tempStr;
}

void MainWindow::on_pushButton_Settings_clicked()
{
    settingswindow.show();
}

void MainWindow::ConnectSettingsChange(int DeviceNum, int BusSpeedNum, int IDlenNum)
{
    qDebug()<<DeviceNum<<BusSpeedNum<<IDlenNum;
    switch(DeviceNum)//выбор интерфейса связт
    {
    case 0:
        CAN_Adapter_ptr = &Systec_CAN;
        break;
    case 1:
        CAN_Adapter_ptr = &Vul_Can;
        //qDebug()<<"250";
        break;
    default:
        CAN_Adapter_ptr = &Vul_Can;
        break;
    }

    auto USBCAN_BAUD = USBCAN_BAUD_500kBit;
    switch(BusSpeedNum)//BAUDRATE
    {
    case 0:
        USBCAN_BAUD = USBCAN_BAUD_500kBit;
        break;
    case 1:
        USBCAN_BAUD = USBCAN_BAUD_250kBit;
        break;
    case 2:
        USBCAN_BAUD = USBCAN_BAUD_1MBit;
        break;
    default:
        break;
    }

    //IDlength
    auto m_hexIntegerValidator = new HexIntegerValidator(this);

    switch(IDlenNum)
    {
    case 0:
        //qDebug()<<"normal";
        m_hexIntegerValidator->setMaxID(0x7FF);
        break;
    case 1:
        //qDebug()<<"extended";
        m_hexIntegerValidator->setMaxID(0x1FFFFFFFF);
        break;
    default:
        break;
    }
    ui->lineEdit_Tester_ID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_ECU_ID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Tracking_ID->setValidator(m_hexIntegerValidator);

    tUcanInitCanParam InitCanParam_p = {sizeof(tUcanInitCanParam), kUcanModeNormal, HIBYTE (USBCAN_BAUD), LOBYTE (USBCAN_BAUD), true, 0xFFFFFFFF, 0x00000000, static_cast<DWORD>(USBCAN_BAUD), 0, 0};
    //DWORD test1=HIBYTE (USBCAN_BAUD_250kBit)+LOBYTE (USBCAN_BAUD_250kBit);
    //qDebug()<<"DWORDTest: "<<test1;
    //qDebug()<<"BaudRate: "<<InitCanParam_p.m_dwBaudrate;
    CAN_Adapter_ptr->ReInit(InitCanParam_p);
    CAN_Adapter::CAN_Adapter_ptr_set(CAN_Adapter_ptr);
}

void MainWindow::on_pushButton_Trace_clicked()
{
    tracewindow.show();
}
