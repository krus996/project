#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSerialPort>
#include<QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_btn_send_clicked();
    void on_btn_open_clicked();
    void read_data();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial_port_t;

    void baudrate_activated(const QString &arg1);

    void parity_activated(int arg1);

    void databit_activated(const QString &arg1);

    void stopbit_activated(const QString &arg1);
    int m_serical_state;

};

#endif // MAINWINDOW_H
