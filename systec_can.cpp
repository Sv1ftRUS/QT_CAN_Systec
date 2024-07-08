#include "systec_can.h"
//#include "mainwindow.h"
#include <minwindef.h>

//int b=7777;
//extern int a;
Systec_CAN * Systec_CAN_ptr=nullptr;

Systec_CAN::Systec_CAN(QObject *parent)
    : QObject{parent}
{
    Systec_CAN_ptr=this;
}

uint Systec_CAN::CAN_Init_Systec(tUcanInitCanParam &InitCanParam_p)
{
    qDebug()<<"Library ver.:"<<UcanGetVersion();
    RxQueue.clear();
    TxQueue.clear();
    if(auto errorCode=UcanInitHardware (pUcanHandle_p, USBCAN_ANY_MODULE, AppEventCallback))
    {
        qDebug()<<"HW_Init error:"<<errorCode;
        return errorCode;
    }
    //tUcanInitCanParam InitCanParam_p = {sizeof(tUcanInitCanParam), kUcanModeNormal, HIBYTE (USBCAN_BAUD_500kBit), LOBYTE (USBCAN_BAUD_500kBit), true, 0xFFFFFFFF, 0x00000000, 0, 0, 0};
    if(auto errorCode= UcanInitCanEx (*pUcanHandle_p, &InitCanParam_p))
    {
        qDebug()<<"CAN_Init error:"<<errorCode;
        return errorCode;
    }
    qDebug()<<"Firmware:"<<USBCAN_MAJOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Revision:"<<USBCAN_MINOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Release:"<<USBCAN_RELEASE_VER(UcanGetFwVersion(*pUcanHandle_p));
    UcanInitHwConnectControl (AppConnectControlCallback);
    emit Systec_CAN_ptr->CANStatusChanged(Systec_CAN_ptr->pStatus_p);
    return 0;
}

uint Systec_CAN::CAN_ReInit_Systec(tUcanInitCanParam &InitCanParam_p)
{
    //UcanSetBaudrate (*pUcanHandle_p, HIBYTE (InitCanParam_p.m_dwBaudrate), LOBYTE (InitCanParam_p.m_dwBaudrate));

    qDebug()<<"reinit CAN";
    if(auto errorCode=UcanDeinitCan(*pUcanHandle_p))
    {
        qDebug()<<"reinit DeinitCAN_Init error:"<<errorCode;
        return errorCode;
    }
    RxQueue.clear();
    TxQueue.clear();
    /*if(auto errorCode=UcanInitHardware (pUcanHandle_p, USBCAN_ANY_MODULE, AppEventCallback))
    {
        qDebug()<<"reinit HW_Init error:"<<errorCode;
        return errorCode;
    }*/
    //tUcanInitCanParam InitCanParam_p = {sizeof(tUcanInitCanParam), kUcanModeNormal, HIBYTE (USBCAN_BAUD_500kBit), LOBYTE (USBCAN_BAUD_500kBit), true, 0xFFFFFFFF, 0x00000000, 0, 0, 0};
    if(auto errorCode= UcanInitCanEx (*pUcanHandle_p, &InitCanParam_p))
    {
        qDebug()<<"reinit CAN_Init error:"<<errorCode;
        return errorCode;
    }
    //qDebug()<<"Firmware:"<<USBCAN_MAJOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Revision:"<<USBCAN_MINOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Release:"<<USBCAN_RELEASE_VER(UcanGetFwVersion(*pUcanHandle_p));
    //UcanInitHwConnectControl (AppConnectControlCallback);
    emit Systec_CAN_ptr->CANStatusChanged(Systec_CAN_ptr->pStatus_p);

    return 0;
}

void PUBLIC Systec_CAN::AppConnectControlCallback(BYTE bEvent_p, DWORD dwParam_p)
{
        emit Systec_CAN_ptr->CANUSBConnectStatusChanged((int)bEvent_p);
}

void PUBLIC Systec_CAN::AppEventCallback(tUcanHandle UcanHandle_p, TBYTE bEvent_p)
{
    switch(bEvent_p)
    {
    case(USBCAN_EVENT_RECEIVE):
    {
        //qDebug()<<"FrameRecieved";
        //tCanMsgStruct CanMsgRx;
        //Systec_CAN_ptr->readtest(UcanHandle_p);
        UCANRET ret = UcanReadCanMsg (UcanHandle_p, &Systec_CAN_ptr->CanMsgRx);// из-за этого прога падает
        if(ret)
            qDebug()<<"Read Messege Error: "<<(int)ret;
        //Systec_CAN_ptr->RxStack.push(Systec_CAN_ptr->CanMsgRx);
        Systec_CAN_ptr->RxQueue.enqueue(Systec_CAN_ptr->CanMsgRx);
        break;
    }
    case(USBCAN_EVENT_STATUS):
    {
        qDebug()<<"CAN Status Changed";
        //tStatusStruct* pStatus_p = nullptr;
        UcanGetStatus (UcanHandle_p, Systec_CAN_ptr->pStatus_p);
        emit Systec_CAN_ptr->CANStatusChanged(Systec_CAN_ptr->pStatus_p);
        break;
    }
    }

}
/*
uint Systec_CAN::readtest(tUcanHandle UcanHandle_p)
{
    UcanReadCanMsg (UcanHandle_p, &Systec_CAN_ptr->CanMsgRx);
    if(Systec_CAN_ptr->CanMsgRx.m_dwID==0x765)
            Systec_CAN_ptr->RxStack.push(Systec_CAN_ptr->CanMsgRx);
    return 0;
}
*/
uint Systec_CAN::BUS_Status_Systec()
{
    return UcanGetStatus (*pUcanHandle_p, pStatus_p);
}

UCANRET Systec_CAN::WriteMSG_Systec(tCanMsgStruct &CanMsgTx)
{
    //qDebug()<<CanMsgTx.m_dwID;
    //CanMsgTx.m_dwID=(quint32)0x18DD;//A40F1;
    //qDebug()<<CanMsgTx.m_dwID;
    return UcanWriteCanMsg (*pUcanHandle_p, &CanMsgTx);
}

tCanMsgStruct Systec_CAN::ReadMSG_Systec()
{
    //return RxStack.pop();
    return RxQueue.dequeue();
}

bool Systec_CAN::RxBufIsEmpty()
{
    //return RxStack.isEmpty();
    return RxQueue.isEmpty();
}

bool Systec_CAN::TxBufIsEmpty()
{
    return TxQueue.isEmpty();
}
/*
void Systec_CAN::RxBufClear()
{
    return RxStack.clear();
}

void Systec_CAN::TxBufClear()
{
    return TxStack.clear();
}
*/

QString Systec_CAN::DeviceInfo()
{
    tUcanHardwareInfo* pHwInfo_p=new tUcanHardwareInfo();
    UcanGetHardwareInfo (*pUcanHandle_p, pHwInfo_p);
    return ("Device Info\nHWnumber:"+ QString::number(pHwInfo_p->m_dwSerialNr)+"  Firmware:"+(QString::number(USBCAN_MAJOR_VER(UcanGetFwVersion(*pUcanHandle_p))) +"  Revision:"+QString::number(USBCAN_MINOR_VER(UcanGetFwVersion(*pUcanHandle_p)))+"  Release:"+QString::number(USBCAN_RELEASE_VER(UcanGetFwVersion(*pUcanHandle_p)))));
}

uint Systec_CAN::CAN_DeInit_Systec()
{
    UcanDeinitCan (*pUcanHandle_p);
    UcanDeinitHardware(*pUcanHandle_p);
    return 0;
}

Systec_CAN::~Systec_CAN()
{

}
