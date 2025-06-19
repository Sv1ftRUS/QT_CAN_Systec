#include "trace_window.h"
#include "ui_trace_window.h"
#include "main_window.h"
#include "validators.h"
#include "chrono"
#include "time.h"

//extern CAN_Adapter * CAN_Adapter_ptr_GLOBAL;

Trace_window::Trace_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Trace_window)
{
    ui->setupUi(this);
    auto m_hexIntegerValidator = new HexIntegerValidator(this);
    auto m_HexStringValidator = new HexStringValidator(this);
    auto m_hexIntegerValidator_CycleTime = new DecIntegerValidator(this);
    //m_hexIntegerValidator_CycleTime->setMaxID(1000);
    //HexIntegerValidator *m_hexIntegerValidator;

    ui->lineEdit_Tx1MsgID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Tx2MsgID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Tx3MsgID->setValidator(m_hexIntegerValidator);
    ui->lineEdit_Tx1MsgCycle->setValidator(m_hexIntegerValidator_CycleTime);
    ui->lineEdit_Tx2MsgCycle->setValidator(m_hexIntegerValidator_CycleTime);
    ui->lineEdit_Tx3MsgCycle->setValidator(m_hexIntegerValidator_CycleTime);
    ui->lineEdit_Tx1MsgData->setValidator(m_HexStringValidator);
    ui->lineEdit_Tx2MsgData->setValidator(m_HexStringValidator);
    ui->lineEdit_Tx3MsgData->setValidator(m_HexStringValidator);
    m_BusLoadTimer->start(1000);
    connect(m_BusLoadTimer, &QTimer::timeout, [&](){ui->label_BusLoad->setText("BusLoad: "+QString("%1").arg(m_BusLoadCounter,0,10)+" F/S");m_BusLoadCounter=0;m_BusLoadTimer->start(1000);});
    connect(m_Msg1TxTimer, &QTimer::timeout, [&](){SendOnPushAndTime(ui->lineEdit_Tx1MsgID, ui->lineEdit_Tx1MsgData);});
    connect(m_Msg2TxTimer, &QTimer::timeout, [&](){SendOnPushAndTime(ui->lineEdit_Tx2MsgID, ui->lineEdit_Tx2MsgData);});
    connect(m_Msg3TxTimer, &QTimer::timeout, [&](){SendOnPushAndTime(ui->lineEdit_Tx3MsgID, ui->lineEdit_Tx3MsgData);});

}

Trace_window::~Trace_window()
{
    delete ui;
}

void Trace_window::addText(const QString &str)
{
    if(!ui->pushButton_Pause->isChecked())
    {
            ui->plainTextEdit_Trace->insertPlainText(str);
            ui->plainTextEdit_Trace->verticalScrollBar()->setValue(ui->plainTextEdit_Trace->verticalScrollBar()->maximum());
    }
    m_BusLoadCounter++;
}

void Trace_window::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_Trace->clear();
}

void Trace_window::on_lineEdit_Tx1MsgID_editingFinished()
{
    auto str = ((ui->lineEdit_Tx1MsgID->text()).toUInt(0, 16));
    ui->lineEdit_Tx1MsgID->setText("0x"+QString("%1").arg(str,0,16).toUpper());
}

void Trace_window::on_lineEdit_Tx2MsgID_editingFinished()
{
    auto str = ((ui->lineEdit_Tx2MsgID->text()).toUInt(0, 16));
    ui->lineEdit_Tx2MsgID->setText("0x"+QString("%1").arg(str,0,16).toUpper());
}

void Trace_window::on_lineEdit_Tx3MsgID_editingFinished()
{
    auto str = ((ui->lineEdit_Tx3MsgID->text()).toUInt(0, 16));
    ui->lineEdit_Tx3MsgID->setText("0x"+QString("%1").arg(str,0,16).toUpper());
}

void Trace_window::on_pushButton_Tx1MsgSend_clicked()
{
    SendOnPushAndTime(ui->lineEdit_Tx1MsgID, ui->lineEdit_Tx1MsgData);
    if(ui->checkBox_Msg1Cycle->checkState() && !ui->pushButton_Tx1MsgSend->isFlat())
    {
        ui->pushButton_Tx1MsgSend->setFlat(1);
        m_Msg1TxTimer->start((ui->lineEdit_Tx1MsgCycle->text()).toInt());
    }
    else
    {
        ui->pushButton_Tx1MsgSend->setFlat(0);
        m_Msg1TxTimer->stop();
    }
}

void Trace_window::on_pushButton_Tx2MsgSend_clicked()
{
    SendOnPushAndTime(ui->lineEdit_Tx2MsgID, ui->lineEdit_Tx2MsgData);
    if(ui->checkBox_Msg2Cycle->checkState() && !ui->pushButton_Tx2MsgSend->isFlat())
    {
        ui->pushButton_Tx2MsgSend->setFlat(1);
        m_Msg2TxTimer->start((ui->lineEdit_Tx2MsgCycle->text()).toInt());
    }
    else
    {
        ui->pushButton_Tx2MsgSend->setFlat(0);
        m_Msg2TxTimer->stop();
    }
}

void Trace_window::on_pushButton_Tx3MsgSend_clicked()
{
    SendOnPushAndTime(ui->lineEdit_Tx3MsgID, ui->lineEdit_Tx3MsgData);
    if(ui->checkBox_Msg3Cycle->checkState() && !ui->pushButton_Tx3MsgSend->isFlat())
    {
        ui->pushButton_Tx3MsgSend->setFlat(1);
        m_Msg3TxTimer->start((ui->lineEdit_Tx3MsgCycle->text()).toInt());
    }
    else
    {
        ui->pushButton_Tx3MsgSend->setFlat(0);
        m_Msg3TxTimer->stop();
    }
}

QString Trace_window::printCanMsg(const tCanMsgStruct &CanMsg)
{
    auto start = std::chrono::high_resolution_clock::now();
    //auto start=clock();
    static QString tempStr;
    tempStr.clear();

    for(auto i=0; i<CanMsg.m_bDLC; i++)
    {
        tempStr=tempStr+(CanMsg.m_bData[i]>0x0F?"0x":"0x0")+QString::number(CanMsg.m_bData[i], 16).toUpper()+"  ";
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto int_s = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    qDebug()<<"func PrintCanMsg() execution time: "<<int_s.count();
    //auto end=clock();
    //qDebug()<<"PrintCanMsg: "<<"start="<<start<<"/end="<<end<<"  end-start: "<<end-start;
    tempStr="0x"+QString::number(CanMsg.m_dwID, 16)+"   "+"["+QString::number(CanMsg.m_bDLC)+"]"+"   "+tempStr;
    return tempStr;
}

bool Trace_window::SendOnPushAndTime(const QLineEdit *MsgId,const QLineEdit* MsgData)
{
    static tCanMsgStruct CanMsg;
    CanMsg.m_dwID = ((MsgId->text()).toUInt(0, 16));
    CanMsg.m_bFF = (CanMsg.m_dwID>0xFFF ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD);
    QByteArray Payload=QByteArray::fromHex((MsgData->text()).remove(QLatin1Char(' ')).toLatin1());
    for(int i=0; i<Payload.length(); i++)
        CanMsg.m_bData[i]=Payload[i];
    CanMsg.m_bDLC =sizeof(CanMsg.m_bData);
    CanMsg.m_dwTime = 0;
    CAN_Adapter * ptr=CAN_Adapter::CAN_Adapter_ptr_get();
    auto ret=ptr->SendMsg(CanMsg);
    if(ret)
        qDebug()<<"Push Button Send Error:"<<(int) ret;
    ui->plainTextEdit_Trace->insertPlainText("Tx:  "+ printCanMsg(CanMsg)+"\n");
    ui->plainTextEdit_Trace->verticalScrollBar()->setValue(ui->plainTextEdit_Trace->verticalScrollBar()->maximum());//автосдвиг
    return true;
}

