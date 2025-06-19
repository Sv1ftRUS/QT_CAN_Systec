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

    virtual UCANRET SendMsg(tCanMsgStruct &CanMsgTx)=0;
    virtual tCanMsgStruct ReadMsg()=0;
    virtual bool TxBufIsEmpty()=0;
    virtual bool RxBufIsEmpty()=0;
    virtual uint BusStatus()=0;
    virtual QString DeviceInfo()=0;
    virtual uint Init(tUcanInitCanParam&)=0;
    virtual uint ReInit(tUcanInitCanParam&)=0;
    virtual uint DeInit()=0;

    static CAN_Adapter *CAN_Adapter_ptr_get();
    static bool CAN_Adapter_ptr_set(CAN_Adapter *);

private:
    static CAN_Adapter * CAN_Adapter_self_ptr;

signals:
    void recivedFrame(tCanMsgStruct *CanMsgRx);//это вывод всех приходящих фреймов
    //void CANStatusChanged(tStatusStruct*);
    //void CANUSBConnectStatusChanged(int);
};
#endif // CAN_ADAPTER_H
