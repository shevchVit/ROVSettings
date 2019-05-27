#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QPushButton>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <cstring>
#include <iostream>
#include "packets.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool is_setting();
    void fillOutputPacket();
    void send();
    bool read();
    void parseInputPacket();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ready_to_read();

private slots:
    void on_Send_Button_clicked();

    void on_SettingsEnd_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    InputPacket *m_inputpacket;
    OutputPacket *m_outputpacket;
    QUdpSocket *m_udp;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H
