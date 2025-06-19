#ifndef TRACE_WINDOW_H
#define TRACE_WINDOW_H

#include <QWidget>
#include "qscrollbar.h"// <--удали это
#include <QLineEdit>
#include "can_adapter.h"
//#include "mainwindow.h"
#include <QTimer>

class HexIntegerValidator;
class HexStringValidator;
class DecIntegerValidator;

namespace Ui {
class Trace_window;
}

class Trace_window : public QWidget
{
    Q_OBJECT

public:
    explicit Trace_window(QWidget *parent = nullptr);
    ~Trace_window();
    void addText(const QString &str);

private slots:
    void on_pushButton_Clear_clicked();

    void on_lineEdit_Tx1MsgID_editingFinished();

    void on_lineEdit_Tx2MsgID_editingFinished();

    void on_lineEdit_Tx3MsgID_editingFinished();

    void on_pushButton_Tx1MsgSend_clicked();

    void on_pushButton_Tx2MsgSend_clicked();

    void on_pushButton_Tx3MsgSend_clicked();

private:
    Ui::Trace_window *ui;

    QTimer *m_Msg1TxTimer= new QTimer(this);
    QTimer *m_Msg2TxTimer= new QTimer(this);
    QTimer *m_Msg3TxTimer= new QTimer(this);
    QTimer *m_BusLoadTimer= new QTimer(this);
    uint m_BusLoadCounter = 0;

    bool SendOnPushAndTime(const QLineEdit*,const QLineEdit*);
    QString printCanMsg(const tCanMsgStruct &CanMsg);
};

#endif // TRACE_WINDOW_H
