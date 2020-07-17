#ifndef SIGNINPAGE_H
#define SIGNINPAGE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <QTcpSocket>

class SignInPage : public QDialog
{
    Q_OBJECT

public:
    SignInPage(QTcpSocket* &socket, QWidget *parent = 0);
    ~SignInPage();

    QString getUsername();
    QString getPermission();

private:
    QLabel *nameLabel;
    QLabel *psdLabel;

    QLineEdit *nameEdit;
    QLineEdit *psdEdit;

    QPushButton *button_confirm;
    QPushButton *button_change;

    QTcpSocket* tcpSocket;

    QString username;
    QString permission;
    QStringList information;

    QDialog *nowDialog = NULL;

public slots:
    void confirmClicked();
    void changeClicked();

    void slotConnected();
    void slotDisconnected();
    void dataReceived();
};

#endif // SIGNINPAGE_H
