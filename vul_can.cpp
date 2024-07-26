#include "vul_can.h"

vul_can::vul_can(QObject *parent) : CAN_Adapter{parent}//, QSerialPort{parent}
{

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    Vul_Can->setBaudRate(230400);//
    Vul_Can->setDataBits(QSerialPort::Data8);
    Vul_Can->setParity(QSerialPort::NoParity);
    Vul_Can->setStopBits(QSerialPort::OneStop);
    Vul_Can->setFlowControl(QSerialPort::NoFlowControl);
    Vul_Can->setPortName("COM10");
    if (!Vul_Can->open(QIODevice::ReadWrite)) {
         // если подключится не получится, то покажем сообщение с ошибкой
         //QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        qDebug()<<"Error opening COM port";
         return;
     }
    //connect(&Vul_Can, &QIODevice::readyRead, this, [=](){emit Vul_Can_readyRead(&CanMsgRx);});
    //connect(&Vul_Can, &QIODevice::readyRead, this, [=](){vul_can::RxQueue.enqueue(Vul_Can.readAll());emit Vul_Can_readyRead(&CanMsgRx);});
    connect(Vul_Can, &QIODevice::readyRead, this, &vul_can::Vul_Can_RxSlot);
}

vul_can::~vul_can()
{
    qDebug()<<1;

}

BYTE vul_can::SendMsg(tCanMsgStruct &CanMsgTx)
{
    qDebug()<<1;
}

tCanMsgStruct vul_can::ReadMsg()
{
    qDebug()<<2;
    return RxQueue.dequeue();
}

bool vul_can::TxBufIsEmpty()
{
    qDebug()<<3;
    return TxQueue.isEmpty();

}

bool vul_can::RxBufIsEmpty()
{
    qDebug()<<45;
    return RxQueue.isEmpty();

}

uint vul_can::BusStatus()
{
    qDebug()<<5;

}

uint vul_can::Init(tUcanInitCanParam &)
{
    //COM-Port INFO
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    qDebug() <<"COM-Port INFO:";
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            qDebug() << "\n"
                     << "Port:" << portInfo.portName() << "\n"
                     << "Location:" << portInfo.systemLocation() << "\n"
                     << "Description:" << portInfo.description() << "\n"
                     << "Manufacturer:" << portInfo.manufacturer() << "\n"
                     << "Serial number:" << portInfo.serialNumber() << "\n"
                     << "Vendor Identifier:"
                     << (portInfo.hasVendorIdentifier()
                         ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                         : QByteArray()) << "\n"
                     << "Product Identifier:"
                     << (portInfo.hasProductIdentifier()
                         ? QByteArray::number(portInfo.productIdentifier(), 16)
                         : QByteArray());
        }
    RxQueue.clear();
    TxQueue.clear();

    //tUcanInitCanParam InitCanParam_p = {sizeof(tUcanInitCanParam), kUcanModeNormal, HIBYTE (USBCAN_BAUD_500kBit), LOBYTE (USBCAN_BAUD_500kBit), true, 0xFFFFFFFF, 0x00000000, 0, 0, 0};
    //if(auto errorCode= UcanInitCanEx (*pUcanHandle_p, &InitCanParam_p))
    {
        //qDebug()<<"CAN_Init error:"<<errorCode;
        //return errorCode;
    }
    //qDebug()<<"Firmware:"<<USBCAN_MAJOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Revision:"<<USBCAN_MINOR_VER(UcanGetFwVersion(*pUcanHandle_p))<<"  Release:"<<USBCAN_RELEASE_VER(UcanGetFwVersion(*pUcanHandle_p));
    //UcanInitHwConnectControl (AppConnectControlCallback);
    //emit Systec_CAN_ptr->CANStatusChanged(Systec_CAN_ptr->pStatus_p);
    return 0;
}

uint vul_can::ReInit(tUcanInitCanParam &)
{
    //COM-Port INFO
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    qDebug() <<"COM-Port INFO:";
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            qDebug() << "\n"
                     << "Port:" << portInfo.portName() << "\n"
                     << "Location:" << portInfo.systemLocation() << "\n"
                     << "Description:" << portInfo.description() << "\n"
                     << "Manufacturer:" << portInfo.manufacturer() << "\n"
                     << "Serial number:" << portInfo.serialNumber() << "\n"
                     << "Vendor Identifier:"
                     << (portInfo.hasVendorIdentifier()
                         ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                         : QByteArray()) << "\n"
                     << "Product Identifier:"
                     << (portInfo.hasProductIdentifier()
                         ? QByteArray::number(portInfo.productIdentifier(), 16)
                         : QByteArray());
        }
    RxQueue.clear();
    TxQueue.clear();

}

uint vul_can::DeInit()
{
    qDebug()<<6;

}

QString vul_can::DeviceInfo()
{
    qDebug()<<7;

}

void vul_can::Vul_Can_RxSlot()
{
    auto Arr = Vul_Can->readAll();//.toHex();
    //qDebug()<<Arr.data()<<"|"<<Arr[1]<<"|"<<Arr[2]<<"|"<<Arr[3]<<"|";
    //qDebug()<<Arr.toHex();

    CanMsgRx.m_dwID=((unsigned char)Arr[0]) | (((unsigned char)Arr[1])<<8) | (((unsigned char)Arr[2])<<16) | (((unsigned char)(Arr[3])&0x1F) << 24);
    //CanMsgRx.m_dwID=((unsigned char)Arr[0]&0xFF) | ((Arr[1]&0xFF)<<8) | ((Arr[2]&0xFF)<<16) | (((Arr[3])&0x1F) << 24);
//    qDebug()<<"VUL CAN m_dwID"<<CanMsgRx.m_dwID;
//    qDebug()<<"VUL CAN m_dwID0"<<(Arr[0]&0xFF);
//    qDebug()<<"VUL CAN m_dwID1"<<(Arr[1]<<8);
//    qDebug()<<"VUL CAN m_dwID2"<<((((uint64_t)Arr[2])<<16)&0x00FF0000);
//    qDebug()<<"VUL CAN m_dwID2_1"<<Arr[2];
//    uint32_t tempVar=Arr[2];
//    qDebug()<<"VUL CAN m_dwID2_2"<<tempVar;//&0x00FF0000);
//    qDebug()<<"VUL CAN m_dwID2_3"<<((tempVar<<16));//&0x00FF0000);
//    qDebug()<<"VUL CAN m_dwID3"<<(((Arr[3])&0x1F) << 24);
    CanMsgRx.m_bFF=0;
    CanMsgRx.m_bDLC=Arr[4] & 0x0F;
    CanMsgRx.m_bData[0]=Arr[5];
    CanMsgRx.m_bData[1]=Arr[6];
    CanMsgRx.m_bData[2]=Arr[7];
    CanMsgRx.m_bData[3]=Arr[8];
    CanMsgRx.m_bData[4]=Arr[9];
    CanMsgRx.m_bData[5]=Arr[10];
    CanMsgRx.m_bData[6]=Arr[11];
    CanMsgRx.m_bData[7]=Arr[12];
    //RxQueue.enqueue(CanMsgRx);
    emit Vul_Can_readyRead(&CanMsgRx);
}
