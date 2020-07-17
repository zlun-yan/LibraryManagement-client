#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QDialog>
#include <QImage>

#include <QTcpSocket>
class WelcomePage : public QDialog
{
    Q_OBJECT

public:
    WelcomePage(QTcpSocket* &socket, QWidget *parent = 0);

private:
    QImage image;

    QTcpSocket* tcpSocket;
    bool key_time;
    bool key_connect;

public slots:
    void slotConnected();
    void Timeout();
    void Timeout_2();
};

#endif // WELCOMEPAGE_H
