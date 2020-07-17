#include "welcomepage.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QMessageBox>

WelcomePage::WelcomePage(QTcpSocket* &socket, QWidget *parent)
    : QDialog(parent)
{
    tcpSocket = socket;
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));

    QHostAddress *serverIP = new QHostAddress();
    QString ip = "127.0.0.1";
    if(!serverIP->setAddress(ip))
    {
        QMessageBox::information(this, tr("错误"), tr("无法与服务器连接"));
    }
    tcpSocket->connectToHost(*serverIP, 8209);


    QLabel *label = new QLabel;
    image.load(":/Images/welcome.jpg");
    label->setPixmap(QPixmap::fromImage(image));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    key_time = false;
    key_connect = false;
    QTimer *timer = new QTimer;
    timer->setInterval(3000);
    timer->setSingleShot(true);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(Timeout()));

    QTimer *timer_2 = new QTimer;
    timer_2->setInterval(30000);
    timer_2->setSingleShot(true);
    timer_2->start();
    connect(timer_2, SIGNAL(timeout()), this, SLOT(Timeout_2()));
}

void WelcomePage::slotConnected()
{
    qDebug()<<"connect complete";
    key_connect = true;
    if (key_connect && key_time)
    {
        accept();
    }
}

void WelcomePage::Timeout()
{
    qDebug()<<"time complete";
    key_time = true;
    if (key_connect && key_time)
    {
        accept();
    }
}

void WelcomePage::Timeout_2()
{
    qDebug()<<"timeout";
    QMessageBox::information(this, tr("错误"), tr("连接超时"));
    reject();
}
