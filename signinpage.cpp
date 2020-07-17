#include "signinpage.h"

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMessageBox>

#include "changepsddialog.h"

SignInPage::SignInPage(QTcpSocket* &socket, QWidget *parent)
    : QDialog(parent)
{
    tcpSocket = socket;
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

    nameLabel = new QLabel;
    nameLabel->setText(tr("用户名："));
    psdLabel = new QLabel;
    psdLabel->setText(tr("密码："));

    nameEdit = new QLineEdit;
    psdEdit = new QLineEdit;
    psdEdit->setEchoMode(QLineEdit::Password);

    button_confirm = new QPushButton;
    button_confirm->setText("确认");

    button_change = new QPushButton;
    button_change->setText("修改密码");

    button_change->setStyleSheet("background-color: rgb(52, 152, 219);color: rgb(255, 251, 240)");
    button_confirm->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    connect(button_confirm, SIGNAL(clicked(bool)), this, SLOT(confirmClicked()));
    connect(button_change, SIGNAL(clicked(bool)), this, SLOT(changeClicked()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button_confirm);
    buttonLayout->addWidget(button_change);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameEdit, 0, 1);
    mainLayout->addWidget(psdLabel, 1, 0);
    mainLayout->addWidget(psdEdit, 1, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(mainLayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    setWindowTitle(tr("登录"));

    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
}

SignInPage::~SignInPage()
{
}

void SignInPage::confirmClicked()
{
    username = nameEdit->text();
    QString psd = psdEdit->text();
    if (username.isEmpty() || psd.isEmpty())
    {
        QMessageBox::information(this, tr("登录"), tr("请输入用户名和密码"));
        return;
    }

    QString msg = tr("confirmSend;%1;%2").arg(username).arg(psd);
    tcpSocket->write(msg.toUtf8().data());
}

void SignInPage::changeClicked()
{
    changePsdDialog *dialog = new changePsdDialog(this);
    nowDialog = dialog;
    if(dialog->exec() != QDialog::Accepted)  return;
    QString userName = dialog->getUserName();
    QString psd = dialog->getPsd();
    nowDialog = NULL;
    delete dialog;

    QString msg = tr("changePsdSend;%1;%2").arg(userName).arg(psd);
    tcpSocket->write(msg.toUtf8().data());
}

void SignInPage::slotConnected()
{
    QMessageBox::information(this, tr("登录"), tr("与服务器重新连接"));
}

void SignInPage::slotDisconnected()
{
    QMessageBox::information(this, tr("错误"), tr("与服务器的连接关闭"));
    delete nowDialog;
    reject();
}

void SignInPage::dataReceived()
{
    QByteArray array = tcpSocket->readAll();
    QString msg = array.data();

    information = msg.split(";", QString::SkipEmptyParts);
    if (information.at(0) == "confirmReceive")
    {
        if (information.at(1) == "accept")
        {
            permission = information.at(2);
            accept();
        }
        else if (information.at(1) == "reject")
        {
            QMessageBox::information(this, tr("登录"), tr("用户名或密码错误"));
        }
    }
    else if (information.at(0) == "changePsdReceive")
    {
        if (information.at(1) == "accept")
        {
            QMessageBox::information(this, tr("修改密码"), tr("成功"));
        }
        else if (information.at(1) == "reject")
        {
            QMessageBox::information(this, tr("修改密码"), tr("失败"));
        }
    }
    else
    {
        qDebug()<<msg;
    }
}

QString SignInPage::getUsername()
{
    return username;
}

QString SignInPage::getPermission()
{
    return permission;
}
