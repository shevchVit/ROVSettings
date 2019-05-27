#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_udp = new QUdpSocket;
    m_inputpacket = new InputPacket;
    m_outputpacket = new OutputPacket;
    m_udp->bind(QHostAddress("192.168.1.4"), 5000);

    QPixmap bkgnd("white.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    m_timer = new QTimer(this);
    m_timer->setInterval(250);
    m_timer->start();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(ready_to_read()));
}

bool MainWindow::is_setting()
{
    return  m_outputpacket->is_settings;
}

void MainWindow::send()
{
    m_udp->writeDatagram((char *)(m_outputpacket),sizeof(*m_outputpacket), QHostAddress("192.168.1.5"), 5000);
}

bool MainWindow::read()
{
    QHostAddress *adress = new QHostAddress();
    if(m_udp->hasPendingDatagrams())
    {
        m_udp->readDatagram((char *)(m_inputpacket), sizeof(*m_inputpacket), adress);
        return true;
    }
    else return false;
}

void MainWindow::ready_to_read()
{
    if(read()) ui->Status_Label->setText("Ok");
    else ui->Status_Label->setText("Can't resieve data");
    parseInputPacket();
}

void  MainWindow::fillOutputPacket()
{
    m_outputpacket->is_settings = true;
    m_outputpacket->axis_X = int8_t(ui->X_Value->value());
    m_outputpacket->axis_Y = int8_t(ui->Y_Value->value());
    m_outputpacket->axis_Z = int8_t(ui->Z_Value->value());
    m_outputpacket->axis_W = int8_t(ui->W_Value->value());
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
    m_outputpacket->YawToSet = uint16_t(ui->YawToSet_Value->value());
    m_outputpacket->PitchToSet = uint16_t(ui->PitchToSet_Value->value());
    m_outputpacket->RollToSet = uint16_t(ui->RollToSet_Value->value());
    m_outputpacket->DepthToSet = uint16_t(ui->DepthToSet_Value->value());
    m_outputpacket->yaw_regulator = ui->YawReg_Enabler->isChecked();
    m_outputpacket->pitch_regulator = ui->PitchReg_Enabler->isChecked();
    m_outputpacket->roll_regulator = ui->RollReg_Enabler->isChecked();
    m_outputpacket->depth_regulator = ui->DepthReg_Enabler->isChecked();
}

void MainWindow::parseInputPacket()
{
    ui->Yaw_Value->setText(QString::number(double(m_inputpacket->yaw)));
    ui->Pitch_Value->setText(QString::number(double(m_inputpacket->pitch)));
    ui->Roll_Value->setText(QString::number(double(m_inputpacket->roll)));
    ui->Depth_Value->setText(QString::number(double(m_inputpacket->depth)));
    ui->Temperature_Value->setText(QString::number(double(m_inputpacket->temperature)));
    ui->Core_Value->setText(QString::number(double(m_inputpacket->core)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Send_Button_clicked()
{
    fillOutputPacket();
    send();
}

void MainWindow::on_SettingsEnd_clicked()
{
    fillOutputPacket();
    m_outputpacket->is_settings = false;
    send();
    QFile out("Data.txt");
    out.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&out);
    stream.setCodec("UTF-8");

    stream << "YawKp = " << m_outputpacket->YawKp << '\n';
    stream << "YawKi = " << m_outputpacket->YawKi << '\n';
    stream << "YawKd = " << m_outputpacket->YawKd << '\n';
    stream << "PitchKp = " << m_outputpacket->PitchKp << '\n';
    stream << "PitchKi = " << m_outputpacket->PitchKi << '\n';
    stream << "PitchKd = " << m_outputpacket->PitchKd << '\n';
    stream << "RollKp = " << m_outputpacket->RollKp << '\n';
    stream << "RollKi = " << m_outputpacket->RollKi << '\n';
    stream << "RollKd = " << m_outputpacket->RollKd << '\n';
    stream << "DepthKp = " << m_outputpacket->DepthKp << '\n';
    stream << "DepthKi = " << m_outputpacket->DepthKi << '\n';
    stream << "DepthKd = " << m_outputpacket->DepthKd << '\n';

    out.close();
    this->close();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        QPixmap bkgnd("anime.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
    }
    else
    {
        QPixmap bkgnd("white.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog;
    QFile file(dialog.getOpenFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    double ui_data[12] = {0};
    for(int idx = 0; !in.atEnd(); idx++)
    {
        QString line = in.readLine();
        int i = 0;
        for(i = 0; i < line.size(); i++)
        {
            if(line.at(i) == '=') break;
        }
        QString data;
        for(i = i + 2; i < line.size(); i++)
        {
            data += line.at(i);
        }
        ui_data[idx] = data.toDouble();
    }
    ui->YawKp_Value->setValue(ui_data[0]);
    ui->YawKi_Value->setValue(ui_data[1]);
    ui->YawKd_Value->setValue(ui_data[2]);
    ui->PitchKp_Value->setValue(ui_data[3]);
    ui->PitchKi_Value->setValue(ui_data[4]);
    ui->PitchKd_Value->setValue(ui_data[5]);
    ui->RollKp_Value->setValue(ui_data[6]);
    ui->RollKi_Value->setValue(ui_data[7]);
    ui->RollKd_Value->setValue(ui_data[8]);
    ui->DepthKp_Value->setValue(ui_data[9]);
    ui->DepthKi_Value->setValue(ui_data[10]);
    ui->DepthKd_Value->setValue(ui_data[11]);

}

void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog dialog;
    QFile out(dialog.getSaveFileName() + ".txt");
    out.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&out);
    stream.setCodec("UTF-8");
    fillOutputPacket();

    stream << "YawKp = " << m_outputpacket->YawKp << '\n';
    stream << "YawKi = " << m_outputpacket->YawKi << '\n';
    stream << "YawKd = " << m_outputpacket->YawKd << '\n';
    stream << "PitchKp = " << m_outputpacket->PitchKp << '\n';
    stream << "PitchKi = " << m_outputpacket->PitchKi << '\n';
    stream << "PitchKd = " << m_outputpacket->PitchKd << '\n';
    stream << "RollKp = " << m_outputpacket->RollKp << '\n';
    stream << "RollKi = " << m_outputpacket->RollKi << '\n';
    stream << "RollKd = " << m_outputpacket->RollKd << '\n';
    stream << "DepthKp = " << m_outputpacket->DepthKp << '\n';
    stream << "DepthKi = " << m_outputpacket->DepthKi << '\n';
    stream << "DepthKd = " << m_outputpacket->DepthKd << '\n';

    out.close();
}
