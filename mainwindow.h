#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <cstring>
#include "packets.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void run();
    void fillOutputPacket();
    void send();
    void read();
    void parseInputPacket();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    InputPacket *m_inputpacket;
    OutputPacket *m_outputpacket;
    QUdpSocket *m_udp;
};

#endif // MAINWINDOW_H
