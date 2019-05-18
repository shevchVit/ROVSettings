#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPixmap bkgnd("C:\\Users\\Vitaliy\\Desktop\\anime.jpg");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, bkgnd);
//    this->setPalette(palette);
    m_udp = new QUdpSocket;
    m_inputpacket = new InputPacket;
    m_outputpacket = new OutputPacket;
    m_udp->bind(QHostAddress("192.168.1.4"), 5000);
}

void MainWindow::send()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << m_outputpacket->isSettigsEnd;
    out << m_outputpacket->axis_X;
    out << m_outputpacket->axis_Y;
    out << m_outputpacket->axis_Z;
    out << m_outputpacket->axis_W;
    out << m_outputpacket->YawKp;
    out << m_outputpacket->YawKi;
    out << m_outputpacket->YawKd;
    out << m_outputpacket->PitchKp;
    out << m_outputpacket->PitchKi;
    out << m_outputpacket->PitchKd;
    out << m_outputpacket->RollKp;
    out << m_outputpacket->RollKi;
    out << m_outputpacket->RollKd;
    out << m_outputpacket->DepthKp;
    out << m_outputpacket->DepthKi;
    out << m_outputpacket->DepthKd;
    out << m_outputpacket->YawToSet;
    out << m_outputpacket->PitchToSet;
    out << m_outputpacket->RollToSet;
    out << m_outputpacket->DepthToSet;
    out << m_outputpacket->regulators[0];
    out << m_outputpacket->regulators[1];
    out << m_outputpacket->regulators[2];
    out << m_outputpacket->regulators[3];
    m_udp->writeDatagram(data, QHostAddress("192.168.1.4"), 5000);
}

void MainWindow::read()
{
    QByteArray data;
    QHostAddress *adress = new QHostAddress();
    m_udp->readDatagram(data.data(), data.size(), adress);
}

void  MainWindow::fillOutputPacket()
{
    m_outputpacket->axis_X = int8_t(ui->X_Value->text().toInt());
    m_outputpacket->axis_Y = int8_t(ui->Y_Value->text().toInt());
    m_outputpacket->axis_Z = int8_t(ui->Z_Value->text().toInt());
    m_outputpacket->axis_W = int8_t(ui->W_Value->text().toInt());
    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->YawKi = float(ui->YawKi_Value->value());
    m_outputpacket->YawKd = float(ui->YawKd_Value->value());
    m_outputpacket->PitchKp = float(ui->PitchKp_Value->value());
    m_outputpacket->PitchKi = float(ui->PitchKi_Value->value());
    m_outputpacket->PitchKd = float(ui->PitchKd_Value->value());
    m_outputpacket->RollKp = float(ui->RollKp_Value->value());
    m_outputpacket->RollKi = float(ui->RollKi_Value->value());
    m_outputpacket->RollKd = float(ui->RollKd_Value->value());
    m_outputpacket->DepthKp = float(ui->DepthKp_Value->value());
    m_outputpacket->DepthKi = float(ui->DepthKi_Value->value());
    m_outputpacket->DepthKd = float(ui->DepthKd_Value->value());
    m_outputpacket->YawToSet = float(ui->YawToSet_Value->value());
    m_outputpacket->PitchToSet = float(ui->PitchToSet_Value->value());
    m_outputpacket->RollToSet = float(ui->RollToSet_Value->value());
    m_outputpacket->DepthToSet = float(ui->DepthToSet_Value->value());
    m_outputpacket->regulators[0] = ui->YawReg_Enabler;
    m_outputpacket->regulators[1] = ui->PitchReg_Enabler;
    m_outputpacket->regulators[2] = ui->RollReg_Enabler;
    m_outputpacket->regulators[3] = ui->DepthReg_Enabler;
}

void MainWindow::parseInputPacket()
{
    ui->Yaw_Value->setText(QString::number(double(m_inputpacket->Yaw)));
    ui->Pitch_Value->setText(QString::number(double(m_inputpacket->Pitch)));
    ui->Roll_Value->setText(QString::number(double(m_inputpacket->Roll)));
    ui->Depth_Value->setText(QString::number(double(m_inputpacket->Depth)));
}

void MainWindow::run()
{
    fillOutputPacket();
    send();
    read();
    parseInputPacket();
}

MainWindow::~MainWindow()
{
    delete ui;
}
