#include "signinpage.h"
#include <QApplication>

#include "mainpage.h"

#include <QDebug>
#include <QTcpSocket>

#include "welcomepage.h"

#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/flatwhite.css");

    if(file.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(file.readAll());
        a.setStyleSheet(style);
        file.close();
    }
    else
    {
        qDebug("Open failed");
    }

    QTcpSocket *tcpSocket = new QTcpSocket;

    WelcomePage *welcomePage = new WelcomePage(tcpSocket);
    welcomePage->setStyleSheet("QWidget {font-family:'Microsoft YaHei';font-size: 15px;}");
    if(welcomePage->exec() != QDialog::Accepted)  return -2;
    delete welcomePage;

    SignInPage *dialog = new SignInPage(tcpSocket);
    dialog->setStyleSheet("QWidget {font-family:'Microsoft YaHei';font-size: 15px;}");
    if(dialog->exec() != QDialog::Accepted)  return -1;

    QString username = dialog->getUsername();
    QString permission = dialog->getPermission();
    delete dialog;

    //传过去的时候也要传用户名
    MainPage m(tcpSocket, username, permission);
    m.setStyleSheet("QWidget {font-family:'Microsoft YaHei';font-size: 15px;}");
    m.show();

    return a.exec();
}
