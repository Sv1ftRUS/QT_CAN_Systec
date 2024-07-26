#ifndef CAN_ADAPTER_H
#define CAN_ADAPTER_H

#include <QObject>
#include <minwindef.h>
//#include "systec_can.h"

//Systec
#include "Usbcan32.h"
#include "UsbCanLs.h"
#include "UsbCanUp.h"

class CAN_Adapter : public QObject
{
    Q_OBJECT
public:
    explicit CAN_Adapter(QObject *parent = nullptr);
    virtual ~CAN_Adapter()=0;

    //virtual UCANRET WriteMSG_Systec(tCanMsgStruct &CanMsgTx)=0;
    virtual UCANRET SendMsg(tCanMsgStruct &CanMsgTx)=0;
    virtual tCanMsgStruct ReadMsg()=0;
    virtual bool TxBufIsEmpty()=0;
    virtual bool RxBufIsEmpty()=0;
    virtual uint BusStatus()=0;
    virtual QString DeviceInfo()=0;
    virtual uint Init(tUcanInitCanParam&)=0;
    virtual uint ReInit(tUcanInitCanParam&)=0;
    virtual uint DeInit()=0;
    /*
    UCANRET WriteMSG_Systec(tCanMsgStruct &CanMsgTx);
    tCanMsgStruct ReadMSG_Systec();

    bool TxBufIsEmpty();
    bool RxBufIsEmpty();

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

*/
//signals:
    //void recivedFrame(tCanMsgStruct *CanMsgRx);//это вывод всех приходящих фреймов
    //void CANStatusChanged(tStatusStruct*);
    //void CANUSBConnectStatusChanged(int);


};

#endif // CAN_ADAPTER_H
