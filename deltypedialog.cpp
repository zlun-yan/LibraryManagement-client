#include "deltypedialog.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

delTypeDialog::delTypeDialog(QWidget *parent)
    : QDialog(parent)
{
    QPushButton *closeButton = new QPushButton(tr("关闭"));
    QPushButton *submitButton = new QPushButton(tr("提交"));

    closeButton->setStyleSheet("background-color: rgb(231, 76, 60);color: rgb(255, 251, 240)");
    submitButton->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    closeButton->setDefault(true);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    typenameEdit = new QLineEdit;
    QLabel *label = new QLabel;
    label->setText(tr("分区名称："));

    QHBoxLayout *layout_1 = new QHBoxLayout;
    layout_1->addWidget(label);
    layout_1->addWidget(typenameEdit);

    QHBoxLayout *layout_2 = new QHBoxLayout;
    layout_2->addWidget(submitButton);
    layout_2->addWidget(closeButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_1);
    layout->addLayout(layout_2);

    setLayout(layout);
    setWindowTitle(tr("删除分区"));
}

void delTypeDialog::submit()
{
    typeName = typenameEdit->text();
    if (typeName.isEmpty())
    {
        QMessageBox::information(this, tr("删除分区"), tr("请输入分区名称"));
        return;
    }

    accept();
}

QString delTypeDialog::getTypeName()
{
    return typeName;
}
