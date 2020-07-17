#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include <QGroupBox>

#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>

#include <QTcpSocket>

#include <QCloseEvent>

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    MainPage(QTcpSocket* &socket, const QString &username, const QString &permission_in, QWidget *parent = 0);

private:
    void updateUserInformation();
    void closeEvent(QCloseEvent *event);    // 重写closeEvent的申明
    QString userNameTCP;
    QString permission;
    QString borrowNum;
    QStringList borrowBook;
    QStringList borrowDate;


    QTcpSocket *tcpsocket;

    QString queryModel = "not";

    QGroupBox *createQueryGroupBox();
    QGroupBox *createUserGroupBox();
    void createMenuBox();

    QTextEdit *userInformation;
    QTextEdit *bookText;

    QLineEdit *queryEdit;
    QComboBox *queryCombo;
    QPushButton *confirmButton;

    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;

private slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();

    void queryButtonClicked();
    void queryChanged(const QString &text);

    void Borrow();
    void Return();
    void addBook();
    void addType();
    void delBook();
    void delType();
};

#endif // MAINPAGE_H
