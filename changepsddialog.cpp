#include "changepsddialog.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

changePsdDialog::changePsdDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel(tr("用户名:"));
    QLabel *psdLabel = new QLabel(tr("新密码:"));
    QLabel *rePsdLabel = new QLabel(tr("重新输入密码:"));

    nameEdit = new QLineEdit;
    psdEdit = new QLineEdit;
    psdEdit->setEchoMode(QLineEdit::Password);
    rePsdEdit = new QLineEdit;
    rePsdEdit->setEchoMode(QLineEdit::Password);

    QPushButton *button_confirm = new QPushButton;
    button_confirm->setText(tr("确认"));
    QPushButton *button_cancel = new QPushButton;
    button_cancel->setText(tr("取消"));

    button_cancel->setStyleSheet("background-color: rgb(231, 76, 60);color: rgb(255, 251, 240)");
    button_confirm->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    connect(button_confirm, SIGNAL(clicked(bool)), this, SLOT(confirmClicked()));
    connect(button_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button_confirm);
    buttonLayout->addWidget(button_cancel);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameEdit, 0, 1);
    mainLayout->addWidget(psdLabel, 1, 0);
    mainLayout->addWidget(psdEdit, 1, 1);
    mainLayout->addWidget(rePsdLabel, 2, 0);
    mainLayout->addWidget(rePsdEdit, 2, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(mainLayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    setWindowTitle(tr("修改密码"));
}

void changePsdDialog::confirmClicked()
{
    QString name = nameEdit->text();
    QString psd = psdEdit->text();
    QString rePsd = rePsdEdit->text();

    if (name.isEmpty() || psd.isEmpty())
    {
        QMessageBox::information(this, tr("修改密码"), tr("请输入用户名和密码"));
        return;
    }
    if (rePsd.isEmpty())
    {
        QMessageBox::information(this, tr("修改密码"), tr("请确认密码"));
        return;
    }
    if (psd != rePsd)
    {
        QMessageBox::information(this, tr("修改密码"), tr("两次输入的密码不一致"));
        return;
    }

    accept();
}

QString changePsdDialog::getUserName()
{
    return nameEdit->text();
}

QString changePsdDialog::getPsd()
{
    return psdEdit->text();
}
