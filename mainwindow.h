#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include <QAxWidget> // для работы с вордом
#include <QAxObject> // для работы с вордом

//File
#include <QFile>
#include <QFileDialog>

//Strings
#include <QValidator>
#include <QRegularExpression>
#include "qstring.h"

//CAN headers
#include <QCanBus>
#include <QCanBusFrame>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>

//Systec
#include "systec_can.h"

#include "Usbcan32.h"
#include "UsbCanLs.h"
#include "UsbCanUp.h"

#define bitIDlen11
//#define bitIDlen29
#ifdef bitIDlen11
#define BAUDRATE USBCAN_BAUD_500kBit
#define testerID 0x745
#define ECUID 0x765
#define VALIDATORMAXID 0x7FF
#endif

#ifdef bitIDlen29
#define BAUDRATE USBCAN_BAUD_250kBit
#define testerID 0x18DA40F1;
#define ECUID 0x18DAF140;
#define VALIDATORMAXID 0x1FFFFFFFF;
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//class HexIntegerValidator;
//class HexStringValidator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Open_Sequence_clicked();

    void on_pushButton_Send_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Play_Sequence_clicked();

    void on_lineEdit_Tester_ID_editingFinished();

    void on_lineEdit_Tracking_ID_editingFinished();

    void on_lineEdit_ECU_ID_editingFinished();

    void on_lineEdit_Send_Data_editingFinished();

    void on_plainTextEdit_TesterECU_Excahge_textChanged();

    void on_CANStatusChanged(tStatusStruct * pStatus_p);

    void on_CANUSBConnectStatusChanged(int bEvent_p);
    //void recivedFrame(tCanMsgStruct *CanMsgRx);

    void on_comboBox_BusSpeed_currentIndexChanged(int index);

    void on_comboBox_IDlen_currentIndexChanged(int index);

private:

    Ui::MainWindow *ui;
    //----для либы Qt
    //QCanBusDevice   *m_device;
    //QCanBusFrame    *RxFrame = new QCanBusFrame(QCanBusFrame::DataFrame);
    //QCanBusFrame    *RxUDSFrame = new QCanBusFrame(QCanBusFrame::DataFrame);
    //QCanBusFrame    *TxUDSFrame = new QCanBusFrame(QCanBusFrame::DataFrame);
    //QCanBusDevice::Filter filter;
    //QList<QCanBusDevice::Filter> filterList;

    //----для либы Systec
    Systec_CAN Systec_CAN_obj;// = new Systec_CAN(this);
    tUcanHandle *pUcanHandle_p = new tUcanHandle();// can;
    tCanMsgStruct CanMsgRx;// = new tCanMsgStruct;
    tCanMsgStruct CanMsgRxUDS;// = new tCanMsgStruct;
    tCanMsgStruct CanMsgTxUDS;// = new tCanMsgStruct;
    QQueue<tCanMsgStruct> CanMsgRxUDS_Multi;
    QString printCanMsg(const tCanMsgStruct &CanMsgTxUDS);

    QTimer *m_busRxTimer= new QTimer(this);
    QTimer *m_busTxTimer= new QTimer(this);
    QTimer *m_testerPresentTimer= new QTimer(this);
    QTimer *m_sequenceFileTimer= new QTimer(this);
    QFile *SequenceFile = new QFile();
    QFile *SequenceFileLogTemplate = new QFile();

    //void framesProcessingRx(const QCanBusFrame &CanFrameRx);
    void sequenceFileProcessing(const QString &);

    uint TxUDSFrameId = testerID;
    uint RxUDSFrameId = ECUID;
    uint trackingFrameId=0x0;

    //temp for Word template

    QAxObject *pWord= new QAxObject();
    QAxObject *pDoc = new QAxObject();
    QAxObject *pActiveDocument = new QAxObject();
    QAxObject *pRange = new QAxObject();
    QAxObject *pFind = new QAxObject();
};




class HexIntegerValidator : public QValidator
{
    Q_OBJECT
public:
    explicit HexIntegerValidator(QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &) const;

    void setMaxID(qint64 maxID=0x7FF);

private:
    uint m_maximum = 0x7FF;
};

class HexStringValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HexStringValidator(QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const;

    void setMaxLength(int maxLength);

private:
    int m_maxLength = 0;
};

#endif // MAINWINDOW_H
