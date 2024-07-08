#include "settingswindow.h"
#include "ui_settingswindow.h"

settingswindow::settingswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingswindow)
{
    ui->setupUi(this);
    ui->comboBox_Device->addItem("SysTec");
    ui->comboBox_Device->addItem("VulCan");
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
