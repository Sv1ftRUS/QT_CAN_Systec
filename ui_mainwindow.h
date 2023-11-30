/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_ECU_ID;
    QLineEdit *lineEdit_Tracking_Data;
    QLabel *label_2;
    QRadioButton *radioButton_testerPresent;
    QLabel *label_4;
    QLineEdit *lineEdit_Tracking_ID;
    QComboBox *comboBox_IDlen;
    QComboBox *comboBox_BusSpeed;
    QLineEdit *lineEdit_Tester_ID;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_Send_Data;
    QPlainTextEdit *plainTextEdit_TesterECU_Excahge;
    QPushButton *pushButton_Send;
    QPushButton *pushButton_Clear;
    QGridLayout *gridLayout_1;
    QPushButton *pushButton_Open_Sequence;
    QLabel *label_3;
    QProgressBar *progressBar;
    QPushButton *pushButton_Play_Sequence;
    QLabel *label_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMouseTracking(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("release/Wave.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(60);
        sizePolicy1.setVerticalStretch(22);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAutoFillBackground(false);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_ECU_ID = new QLineEdit(centralwidget);
        lineEdit_ECU_ID->setObjectName(QString::fromUtf8("lineEdit_ECU_ID"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_ECU_ID->sizePolicy().hasHeightForWidth());
        lineEdit_ECU_ID->setSizePolicy(sizePolicy2);
        lineEdit_ECU_ID->setMinimumSize(QSize(120, 22));

        gridLayout_2->addWidget(lineEdit_ECU_ID, 1, 1, 1, 1);

        lineEdit_Tracking_Data = new QLineEdit(centralwidget);
        lineEdit_Tracking_Data->setObjectName(QString::fromUtf8("lineEdit_Tracking_Data"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_Tracking_Data->sizePolicy().hasHeightForWidth());
        lineEdit_Tracking_Data->setSizePolicy(sizePolicy3);
        lineEdit_Tracking_Data->setMinimumSize(QSize(258, 0));
        lineEdit_Tracking_Data->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_Tracking_Data, 2, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(48, 22));
        label_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        radioButton_testerPresent = new QRadioButton(centralwidget);
        radioButton_testerPresent->setObjectName(QString::fromUtf8("radioButton_testerPresent"));
        radioButton_testerPresent->setMinimumSize(QSize(140, 24));

        gridLayout_2->addWidget(radioButton_testerPresent, 0, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(70, 22));
        label_4->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_Tracking_ID = new QLineEdit(centralwidget);
        lineEdit_Tracking_ID->setObjectName(QString::fromUtf8("lineEdit_Tracking_ID"));
        sizePolicy3.setHeightForWidth(lineEdit_Tracking_ID->sizePolicy().hasHeightForWidth());
        lineEdit_Tracking_ID->setSizePolicy(sizePolicy3);
        lineEdit_Tracking_ID->setMinimumSize(QSize(120, 22));

        gridLayout_2->addWidget(lineEdit_Tracking_ID, 2, 1, 1, 1);

        comboBox_IDlen = new QComboBox(centralwidget);
        comboBox_IDlen->setObjectName(QString::fromUtf8("comboBox_IDlen"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox_IDlen->sizePolicy().hasHeightForWidth());
        comboBox_IDlen->setSizePolicy(sizePolicy4);
        comboBox_IDlen->setMinimumSize(QSize(80, 24));
        comboBox_IDlen->setEditable(false);

        gridLayout_2->addWidget(comboBox_IDlen, 0, 3, 1, 1);

        comboBox_BusSpeed = new QComboBox(centralwidget);
        comboBox_BusSpeed->setObjectName(QString::fromUtf8("comboBox_BusSpeed"));
        sizePolicy4.setHeightForWidth(comboBox_BusSpeed->sizePolicy().hasHeightForWidth());
        comboBox_BusSpeed->setSizePolicy(sizePolicy4);
        comboBox_BusSpeed->setMinimumSize(QSize(80, 24));

        gridLayout_2->addWidget(comboBox_BusSpeed, 1, 3, 1, 1);

        lineEdit_Tester_ID = new QLineEdit(centralwidget);
        lineEdit_Tester_ID->setObjectName(QString::fromUtf8("lineEdit_Tester_ID"));
        lineEdit_Tester_ID->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEdit_Tester_ID->sizePolicy().hasHeightForWidth());
        lineEdit_Tester_ID->setSizePolicy(sizePolicy5);
        lineEdit_Tester_ID->setMinimumSize(QSize(120, 22));

        gridLayout_2->addWidget(lineEdit_Tester_ID, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);


        gridLayout->addLayout(horizontalLayout, 9, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEdit_Send_Data = new QLineEdit(centralwidget);
        lineEdit_Send_Data->setObjectName(QString::fromUtf8("lineEdit_Send_Data"));
        lineEdit_Send_Data->setEnabled(true);
        sizePolicy.setHeightForWidth(lineEdit_Send_Data->sizePolicy().hasHeightForWidth());
        lineEdit_Send_Data->setSizePolicy(sizePolicy);
        lineEdit_Send_Data->setMinimumSize(QSize(480, 20));

        gridLayout_3->addWidget(lineEdit_Send_Data, 0, 0, 1, 1);

        plainTextEdit_TesterECU_Excahge = new QPlainTextEdit(centralwidget);
        plainTextEdit_TesterECU_Excahge->setObjectName(QString::fromUtf8("plainTextEdit_TesterECU_Excahge"));
        sizePolicy.setHeightForWidth(plainTextEdit_TesterECU_Excahge->sizePolicy().hasHeightForWidth());
        plainTextEdit_TesterECU_Excahge->setSizePolicy(sizePolicy);
        plainTextEdit_TesterECU_Excahge->setMinimumSize(QSize(480, 20));
        plainTextEdit_TesterECU_Excahge->setMaximumSize(QSize(480, 110));
        plainTextEdit_TesterECU_Excahge->setBaseSize(QSize(400, 50));
        plainTextEdit_TesterECU_Excahge->setReadOnly(true);

        gridLayout_3->addWidget(plainTextEdit_TesterECU_Excahge, 1, 0, 1, 1);

        pushButton_Send = new QPushButton(centralwidget);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));
        sizePolicy4.setHeightForWidth(pushButton_Send->sizePolicy().hasHeightForWidth());
        pushButton_Send->setSizePolicy(sizePolicy4);
        pushButton_Send->setMinimumSize(QSize(80, 24));

        gridLayout_3->addWidget(pushButton_Send, 0, 1, 1, 1);

        pushButton_Clear = new QPushButton(centralwidget);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_Clear->sizePolicy().hasHeightForWidth());
        pushButton_Clear->setSizePolicy(sizePolicy6);
        pushButton_Clear->setMinimumSize(QSize(80, 24));

        gridLayout_3->addWidget(pushButton_Clear, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 3, 0, 1, 1);

        gridLayout_1 = new QGridLayout();
        gridLayout_1->setObjectName(QString::fromUtf8("gridLayout_1"));
        pushButton_Open_Sequence = new QPushButton(centralwidget);
        pushButton_Open_Sequence->setObjectName(QString::fromUtf8("pushButton_Open_Sequence"));
        sizePolicy3.setHeightForWidth(pushButton_Open_Sequence->sizePolicy().hasHeightForWidth());
        pushButton_Open_Sequence->setSizePolicy(sizePolicy3);
        pushButton_Open_Sequence->setMinimumSize(QSize(112, 24));
        pushButton_Open_Sequence->setMaximumSize(QSize(112, 24));
        pushButton_Open_Sequence->setBaseSize(QSize(117, 20));
        pushButton_Open_Sequence->setLayoutDirection(Qt::RightToLeft);

        gridLayout_1->addWidget(pushButton_Open_Sequence, 0, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy7);
        label_3->setMinimumSize(QSize(260, 24));
        label_3->setMaximumSize(QSize(100, 20));

        gridLayout_1->addWidget(label_3, 0, 1, 1, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(260, 24));
        progressBar->setValue(0);

        gridLayout_1->addWidget(progressBar, 2, 1, 1, 1);

        pushButton_Play_Sequence = new QPushButton(centralwidget);
        pushButton_Play_Sequence->setObjectName(QString::fromUtf8("pushButton_Play_Sequence"));
        sizePolicy3.setHeightForWidth(pushButton_Play_Sequence->sizePolicy().hasHeightForWidth());
        pushButton_Play_Sequence->setSizePolicy(sizePolicy3);
        pushButton_Play_Sequence->setMinimumSize(QSize(112, 24));
        pushButton_Play_Sequence->setLayoutDirection(Qt::RightToLeft);

        gridLayout_1->addWidget(pushButton_Play_Sequence, 2, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(false);

        gridLayout_1->addWidget(label_6, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_1, 8, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);


        gridLayout->addLayout(verticalLayout, 10, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        comboBox_IDlen->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CAN_Test", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Tester ID:</p></body></html>", nullptr));
        lineEdit_ECU_ID->setText(QCoreApplication::translate("MainWindow", "0x765", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>ECU ID:</p></body></html>", nullptr));
        radioButton_testerPresent->setText(QCoreApplication::translate("MainWindow", "Tester Present", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>tracking ID:</p></body></html>", nullptr));
        lineEdit_Tracking_ID->setInputMask(QString());
        lineEdit_Tracking_ID->setText(QCoreApplication::translate("MainWindow", "0x0", nullptr));
        comboBox_IDlen->setCurrentText(QString());
        comboBox_IDlen->setPlaceholderText(QString());
        lineEdit_Tester_ID->setText(QCoreApplication::translate("MainWindow", "0x745", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "DeviceStatus:", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        pushButton_Open_Sequence->setText(QCoreApplication::translate("MainWindow", "Open Sequence", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "no .txt-sequence file selected", nullptr));
        pushButton_Play_Sequence->setText(QCoreApplication::translate("MainWindow", "Play Sequence", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "no .docx-report file selected", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "DeviceInfo:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
