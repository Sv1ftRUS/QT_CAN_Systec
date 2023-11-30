#ifndef SYSTEC_CAN_H
#define SYSTEC_CAN_H

#include <QObject>
#include <QtWidgets>

//Systec
#include "Usbcan32.h"
#include "UsbCanLs.h"
#include "UsbCanUp.h"
//#include "mainwindow.h"


//#define RxBufSize 100
//#define TxBufSize 100

class Systec_CAN : public QObject
{
    Q_OBJECT
public:
    explicit Systec_CAN(QObject *parent = nullptr);
    ~Systec_CAN();

    //bool HW_Init_Systec();
    //bool HW_DeInit_Systec();

    //uint readtest(tUcanHandle UcanHandle_p);

    UCANRET WriteMSG_Systec(tCanMsgStruct &CanMsgTx);
    tCanMsgStruct ReadMSG_Systec();

    bool TxBufIsEmpty();
    bool RxBufIsEmpty();
    //void TxBufClear();
    //void RxBufClear();

    uint BUS_Status_Systec();
    uint CAN_Init_Systec(tUcanInitCanParam&);
    uint CAN_ReInit_Systec(tUcanInitCanParam&);
    uint CAN_DeInit_Systec();
    QString DeviceInfo();

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
    //static void recivedFrame(tCanMsgStruct *CanMsgRx);
    void CANStatusChanged(tStatusStruct*);
    void CANUSBConnectStatusChanged(int);

};

#endif // SYSTEC_CAN_H
