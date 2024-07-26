#include "can_adapter.h"
#include "qdebug.h"

CAN_Adapter::CAN_Adapter(QObject *parent): QObject{parent}
{
    qDebug()<<"Can Adapter created!";
}

CAN_Adapter::~CAN_Adapter()
{
    qDebug()<<"Can Adapter destroyed!";
}
