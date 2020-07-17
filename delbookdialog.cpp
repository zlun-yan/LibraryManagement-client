#include "delbookdialog.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

delBookDialog::delBookDialog(QWidget *parent)
    : QDialog(parent)
{
    QPushButton *closeButton = new QPushButton(tr("关闭"));
    QPushButton *submitButton = new QPushButton(tr("提交"));

    closeButton->setStyleSheet("background-color: rgb(231, 76, 60);color: rgb(255, 251, 240)");
    submitButton->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    closeButton->setDefault(true);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    idEdit = new QLineEdit;
    QLabel *label = new QLabel;
    label->setText(tr("书籍编号："));

    QHBoxLayout *layout_1 = new QHBoxLayout;
    layout_1->addWidget(label);
    layout_1->addWidget(idEdit);

    QHBoxLayout *layout_2 = new QHBoxLayout;
    layout_2->addWidget(submitButton);
    layout_2->addWidget(closeButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_1);
    layout->addLayout(layout_2);

    setLayout(layout);
    setWindowTitle(tr("删除书籍"));
}

void delBookDialog::submit()
{
    id = idEdit->text();
    if (id.isEmpty())
    {
        QMessageBox::information(this, tr("删除书籍"), tr("请输入书籍编号"));
        return;
    }

    accept();
}

QString delBookDialog::getBookId()
{
    return id;
}
