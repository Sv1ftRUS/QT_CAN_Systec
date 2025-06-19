#include "can_adapter.h"
#include "qdebug.h"

CAN_Adapter * CAN_Adapter::CAN_Adapter_self_ptr=NULL;

CAN_Adapter::CAN_Adapter(QObject *parent): QObject{parent}
{
    //qDebug()<<"Can Adapter created!";
}

CAN_Adapter::~CAN_Adapter()
{
    //qDebug()<<"Can Adapter destroyed!";
}

CAN_Adapter* CAN_Adapter::CAN_Adapter_ptr_get()
{
    return CAN_Adapter_self_ptr;
}

bool CAN_Adapter::CAN_Adapter_ptr_set(CAN_Adapter *ptr)
{
    CAN_Adapter_self_ptr=ptr;
    return true;
}

