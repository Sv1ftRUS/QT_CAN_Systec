#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "qdebug.h"

namespace Ui {
class settingswindow;
}

class settingswindow : public QDialog
{
    Q_OBJECT

public:
    explicit settingswindow(QWidget *parent = nullptr);
    ~settingswindow();

private slots:
    void on_pushButton_Ok_clicked();

    //void on_comboBox_BusSpeed_currentIndexChanged(int index);

private:
    Ui::settingswindow *ui;

signals:
    void ConnectSettingsChange(int, int, int);
};

#endif // SETTINGSWINDOW_H
