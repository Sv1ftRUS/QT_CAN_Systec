#ifndef SYSTEC_CAN_H
#define SYSTEC_CAN_H

#include <QObject>
#include <QtWidgets>
#include <can_adapter.h>

//Systec
#include "Usbcan32.h"
#include "UsbCanLs.h"
#include "UsbCanUp.h"
//#include "mainwindow.h"


//#define RxBufSize 100
//#define TxBufSize 100


class Systec_CAN : public CAN_Adapter //public QObject
{
    Q_OBJECT
public:
    explicit Systec_CAN(QObject *parent = nullptr);
    ~Systec_CAN() override;

    UCANRET SendMsg(tCanMsgStruct &CanMsgTx) override;
    tCanMsgStruct ReadMsg() override;

    bool TxBufIsEmpty() override;
    bool RxBufIsEmpty() override;

    uint BusStatus() override;
    uint Init(tUcanInitCanParam&) override;
    uint ReInit(tUcanInitCanParam&) override;
    uint DeInit() override;
    QString DeviceInfo() override;

    //CAN_Adapter::~CAN_Adapter();

    //QStack<tCanMsgStruct> TxStack;
    //QStack<tCanMsgStruct> RxStack;
    QQueue<tCanMsgStruct> TxQueue;
    QQueue<tCanMsgStruct> RxQueue;


private:
    //----для либы Systec
    tUcanHandle *pUcanHandle_p = new tUcanHandle();// can;
    tCanMsgStruct CanMsgRx;// = new tCanMsgStruct;
    tCanMsgStruct CanMsgTx;
    tStatusStruct *pStatus_p = new tStatusStruct();

    //tCanMsgStruct RxBuf[RxBufSize];
    //tCanMsgStruct TxBuf[TxBufSize];

    //bool PushRxBuf(tCanMsgStruct);
    //tCanMsgStruct * PopRxBuf();

    //bool PushTxBuf(tCanMsgStruct);
    //tCanMsgStruct * PopTxBuf();

    static void PUBLIC AppEventCallback (tUcanHandle UcanHandle_p, TBYTE bEvent_p);
    static void PUBLIC AppConnectControlCallback(BYTE bEvent_p, DWORD dwParam_p);
    //tCanMsgStruct CanMsgRxUDS;// = new tCanMsgStruct;
    //tCanMsgStruct CanMsgTxUDS;// = new tCanMsgStruct;
    //QString printCanMsg(const tCanMsgStruct &CanMsgTxUDS);



    //void PUBLIC AppEventCallback1 (tUcanHandle UcanHandle_p, TBYTE bEvent_p);
    //static void AppEventCallbackEx (tUcanHandle UcanHandle_p, TBYTE bEvent_p, void* pArg_p);
    //void AppEventCallback (tUcanHandle UcanHandle_p, TBYTE bEvent_p);


signals:
    void recivedFrame(tCanMsgStruct *CanMsgRx);//это вывод всех приходящих фреймов
    void CANStatusChanged(tStatusStruct*);
    void CANUSBConnectStatusChanged(int);

};

#endif // SYSTEC_CAN_H
