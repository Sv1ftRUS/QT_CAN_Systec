#include "settings_window.h"
#include "ui_settings_window.h"

//class QSerialPortInfo;
//class QDebug;
#include "qserialportinfo.h"

settingswindow::settingswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingswindow)
{
    ui->setupUi(this);
    ui->comboBox_Device->addItem("SysTec");
    //ui->comboBox_Device->addItem("VulCan");

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    qDebug() <<"COM-Port INFO:";
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            qDebug() << "\n"
                     << "Port:" << portInfo.portName() << "\n"
                     << "Location:" << portInfo.systemLocation() << "\n"
                     << "Description:" << portInfo.description() << "\n";
            ui->comboBox_Device->addItem(portInfo.portName());
    }
    ui->comboBox_BusSpeed->addItem("500 kBit/s");
    ui->comboBox_BusSpeed->addItem("250 kBit/s");
    ui->comboBox_IDlen->addItem("ID 11 Bit");
    ui->comboBox_IDlen->addItem("ID 29 Bit");
}

settingswindow::~settingswindow()
{
    delete ui;
}

void settingswindow::on_pushButton_Ok_clicked()
{
    this->hide();
    emit settingswindow::ConnectSettingsChange(ui->comboBox_Device->currentIndex(), ui->comboBox_BusSpeed->currentIndex(), ui->comboBox_IDlen->currentIndex());
}
