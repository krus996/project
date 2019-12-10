#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial_port_t=new QSerialPort();
    connect(serial_port_t,SIGNAL(readyRead()),this,SLOT(read_data()));

    m_serical_state=0;
    QStringList portList;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        portList<< info.portName();
    }
    qSort(portList.begin(),portList.end());
    ui->comboBox_port->addItems(portList);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::read_data()
{
    QByteArray buf;
    buf=serial_port_t->readAll();
    QString s=buf;
    qDebug() << s << endl;
    ui->textEdit_recv->append(s);
}
void MainWindow::on_btn_send_clicked()
{
    QString str=ui->textEdit_send->toPlainText();
    QByteArray buf=str.toLatin1();
    char *temp=buf.data();
    serial_port_t->write(temp);
}
void MainWindow::on_btn_open_clicked()
{
    QSerialPortInfo *port_info=new QSerialPortInfo(ui->comboBox_port->currentText());
    serial_port_t->setPort(*port_info);
    if(m_serical_state==0)
    {
        bool serial_port_state=serial_port_t->open(QIODevice::ReadWrite);
        if(serial_port_state)
        {
            ui->comboBox_port->setEnabled(false);
            ui->btn_open->setText("关闭串口");
            baudrate_activated(ui->comboBox_baudrate->currentText());
            parity_activated(ui->comboBox_parity->currentIndex());
            databit_activated(ui->comboBox_databit->currentText());
            stopbit_activated(ui->comboBox_stopbit->currentText());
            m_serical_state=1;
        }
        else
            QMessageBox::warning(this,"警告","串口打开失败");

    }
    else
    {
        ui->btn_open->setText("打开串口");
        ui->comboBox_port->setEnabled(true);
        m_serical_state=0;
        serial_port_t->close();
    }
}
void MainWindow::baudrate_activated(const QString &arg1)
{
    switch(arg1.toInt())
    {
    case 1200:
        serial_port_t->setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        serial_port_t->setBaudRate(QSerialPort::Baud2400);
        break;
    case 9600:
        serial_port_t->setBaudRate(QSerialPort::Baud9600);
        break;
    case 38400:
        serial_port_t->setBaudRate(QSerialPort::Baud38400);
        break;
    case 115200:
        serial_port_t->setBaudRate(QSerialPort::Baud115200);
        break;
     }
}
void MainWindow::parity_activated(int arg1)
{
    switch(arg1)
    {
    case 0:
        serial_port_t->setParity(QSerialPort::NoParity);
        break;
    case 1:
        serial_port_t->setParity(QSerialPort::OddParity);
        break;
    case 2:
        serial_port_t->setParity(QSerialPort::EvenParity);
        break;
    }

}
void MainWindow::databit_activated(const QString &arg1)
{
    switch(arg1.toInt())
     {
     case 5:
         serial_port_t->setDataBits(QSerialPort::Data5);
         break;
     case 6:
         serial_port_t->setDataBits(QSerialPort::Data6);
         break;
     case 7:
         serial_port_t->setDataBits(QSerialPort::Data7);
         break;
     case 8:
         serial_port_t->setDataBits(QSerialPort::Data8);
         break;
    }
}
void MainWindow::stopbit_activated(const QString &arg1)
{
    switch(arg1.toInt())
     {
     case 1:
         serial_port_t->setStopBits(QSerialPort::OneStop);
         break;
     case 2:
         serial_port_t->setStopBits(QSerialPort::TwoStop);
         break;
     }

}


