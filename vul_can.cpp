#include "vul_can.h"

vul_can::vul_can(QObject *parent) : CAN_Adapter{parent}//, QSerialPort{parent}
{

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    Vul_Can->setBaudRate(921600);//(9600);//(230400);//(460800);
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
  //поэксперементируй с выравниванием полей
    qDebug()<<"VulCan_send";
    static QByteArray Arr(PC_toCAN_msgLength, 0xCC);
    Arr[0]=PC_toCAN;//msgType
    Arr[1]=0x00;//msgType
    Arr[2]=0x00;//msgType
    Arr[3]=0x00;//msgType
    Arr[4]=(unsigned char) ((CanMsgTx.m_dwID & (0x000000FF))>>0);//uint32_t StdId
    Arr[5]=(unsigned char) ((CanMsgTx.m_dwID & (0x0000FF00))>>8);//uint32_t StdId
    Arr[6]=(unsigned char) ((CanMsgTx.m_dwID & (0x00FF0000))>>16);//uint32_t StdId
    Arr[7]=(unsigned char) ((CanMsgTx.m_dwID & (0xFF000000))>>24);//uint32_t StdId
    Arr[8]=(unsigned char) ((CanMsgTx.m_dwID & (0x000000FF))>>0);//uint32_t ExtId
    Arr[9]=(unsigned char) ((CanMsgTx.m_dwID & (0x0000FF00))>>8);//uint32_t ExtId
    Arr[10]=(unsigned char) ((CanMsgTx.m_dwID & (0x00FF0000))>>16);//uint32_t ExtId
    Arr[11]=(unsigned char) ((CanMsgTx.m_dwID & (0xFF000000))>>24);//uint32_t ExtId
    Arr[12]=(unsigned char) ((CanMsgTx.m_bFF & 0x80)>>5);//uint32_t IDE
    Arr[13]=0x00;//uint32_t IDE
    Arr[14]=0x00;//uint32_t IDE
    Arr[15]=0x00;//uint32_t IDE
    Arr[16]=(unsigned char) ((CanMsgTx.m_bFF & 0x40)>>6);//uint32_t RTR
    Arr[17]=0x00;//uint32_t RTR
    Arr[18]=0x00;//uint32_t RTR
    Arr[19]=0x00;//uint32_t RTR
    Arr[20]=(unsigned char) (CanMsgTx.m_bDLC);//uint32_t DLC
    Arr[21]=0x00;//uint32_t DLC
    Arr[22]=0x00;//uint32_t DLC
    Arr[23]=0x00;//uint32_t DLC
    Arr[24]=0x00;//FunctionalState TransmitGlobalTime
    Arr[25]=0x00;//FunctionalState TransmitGlobalTime
    Arr[26]=0x00;//FunctionalState TransmitGlobalTime
    Arr[27]=0x00;//FunctionalState TransmitGlobalTime
    //data
    Arr[28]=CanMsgTx.m_bData[0];
    Arr[29]=CanMsgTx.m_bData[1];
    Arr[30]=CanMsgTx.m_bData[2];
    Arr[31]=CanMsgTx.m_bData[3];
    Arr[32]=CanMsgTx.m_bData[4];
    Arr[33]=CanMsgTx.m_bData[5];
    Arr[34]=CanMsgTx.m_bData[6];
    Arr[35]=CanMsgTx.m_bData[7];
    Vul_Can->write(Arr, PC_toCAN_msgLength);
    //Vul_Can->write(Arr, PC_toCAN_msgLength);
    //Vul_Can->write(Arr, PC_toCAN_msgLength);

    return 0;
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
    //qDebug()<<45;
    return RxQueue.isEmpty();

}

uint vul_can::BusStatus()
{
    qDebug()<<5;

}

uint vul_can::Init(tUcanInitCanParam &InitCanParam_p)
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

uint vul_can::ReInit(tUcanInitCanParam &InitCanParam_p)
{
    //COM-Port INFO
    /*
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
        }*/
    RxQueue.clear();
    TxQueue.clear();

    static QByteArray Arr(PC_toCAN_msgLength, 0xCC);
    /*
    //----DISCONNECT CAN----
    Arr[0]=PC_toCAN_State;//msgType
    Arr[1]=0x00;
    Arr[2]=0x00;
    Arr[3]=0x00;
    Arr[4]=0x00;//Communication - Disconnect
    Vul_Can->write(Arr, PC_toCAN_msgLength);
    qDebug()<<"Disconnect CAN";
    */
    //----INIT CAN----
    Arr[0]=PC_toCAN_State;//msgType
    Arr[1]=0x00;
    Arr[2]=0x00;
    Arr[3]=0x00;
            //(unsigned char) PC_toCAN_State;
    Arr[4]=0x03;//Communication - Init
    Arr[5]=0x01;//Instance

    qDebug()<<USBCAN_BAUD_500kBit;
    qDebug()<<InitCanParam_p.m_dwBaudrate;
    if(InitCanParam_p.m_dwBaudrate==USBCAN_BAUD_500kBit)//что-то тут не работает, всегда InitCanParam_p.m_dwBaudrate=0
    {
        Arr[6]=0x08;//Prescaler/ 8-500kbit/s    16-250kbit/s <---Check-Ok!
        qDebug()<<"InitValue 0x08";
    }
    else
    {
        Arr[6]=0x10;//Prescaler/ 8-500kbit/s    16-250kbit/s <---Check-Ok!
        qDebug()<<"InitValue 0x10";
    }


    Arr[7]=0x00;//Mode CAN_MODE_NORMAL

    Arr[8]=0x00;//SyncJumpWidth = CAN_SJW_1TQ
    Arr[9]=0x00;
    Arr[10]=0x00;
    Arr[11]=0x00;

    Arr[12]=0x00;//TimeSeg1 CAN_BS1_7TQ
    Arr[13]=0x00;
    Arr[14]=0x06;//500кбит/с
    Arr[15]=0x00;

    Arr[16]=0x00; //TimeSeg2 CAN_BS2_1TQ
    Arr[17]=0x00;
    Arr[18]=0x00;
    Arr[19]=0x00;

    Arr[20]=0x00;//TimeTriggeredMode
    Arr[21]=0x00;//AutoBusOff
    Arr[22]=0x00;//AutoWakeUp
    Arr[23]=0x00;//AutoRetransmission
    Arr[24]=0x00;//ReceiveFifoLocked
    Arr[25]=0x00;//TransmitFifoPriority
    Arr[26]=0x00;
    Arr[27]=0x00;
    Arr[28]=0x00;
    Arr[29]=0x00;
    Arr[30]=0x00;
    Arr[31]=0x00;
    Arr[32]=0x00;
    Arr[33]=0x00;
    Arr[34]=0x00;
    Arr[35]=0x00;
    qDebug()<<"Connect CAN Arr:"<<Arr;
    Vul_Can->write(Arr, PC_toCAN_msgLength);
    /*
    //----CONNECT CAN----
    Arr[0]=PC_toCAN_State;//msgType
    Arr[1]=0x00;
    Arr[2]=0x00;
    Arr[3]=0x00;
    Arr[4]=0x01;//Communication - Connect
    Vul_Can->write(Arr, PC_toCAN_msgLength);
    qDebug()<<"Connect CAN";
    */
    qDebug()<<"Reinit vulcan";
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
