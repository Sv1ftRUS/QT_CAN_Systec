#ifndef VUL_CAN_H
#define VUL_CAN_H

#include <QObject>
#include <QtWidgets>
#include <can_adapter.h>
#include <QDebug>
#include <QSerialPort.h>
#include <QSerialPortInfo>

#define PC_toCAN_msgLength 36

enum msgType //типы сообщений между адаптером и PC
{
    PC_toCAN_State,
    PC_toCAN,
    CAN_toPC_State,
    CAN_toPC
};

class vul_can : public CAN_Adapter //, QSerialPort
{
    Q_OBJECT
public:
    explicit vul_can(QObject *parent = nullptr);
    ~vul_can() override;

    UCANRET SendMsg(tCanMsgStruct &CanMsgTx) override;
    //static UCANRET SendMsgTest(tCanMsgStruct &CanMsgTx);
    tCanMsgStruct ReadMsg() override;

    bool TxBufIsEmpty() override;
    bool RxBufIsEmpty() override;

    uint BusStatus() override;
    uint Init(tUcanInitCanParam&) override;
    uint ReInit(tUcanInitCanParam&) override;
    uint DeInit() override;
    QString DeviceInfo() override;

    QQueue<tCanMsgStruct> TxQueue;
    QQueue<tCanMsgStruct> RxQueue;

    QSerialPort* Vul_Can = new QSerialPort;

   // void serialPortRecieve();
   // void serialPortTransmit();

    tCanMsgStruct CanMsgRx;// = new tCanMsgStruct;
    tCanMsgStruct CanMsgTx;

public slots:
    void Vul_Can_RxSlot();

signals:
    void Vul_Can_readyRead(tCanMsgStruct *CanMsgRx);

private:
    //----для либы Systec
    //tCanMsgStruct CanMsgRx;// = new tCanMsgStruct;
    //tCanMsgStruct CanMsgTx;
    //tStatusStruct *pStatus_p = new tStatusStruct();
};

#endif // VUL_CAN_H
