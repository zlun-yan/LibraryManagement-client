#include "addtypedialog.h"

#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

addTypeDialog::addTypeDialog(QWidget *parent)
    : QDialog(parent)
{
    addressEditor = new QLineEdit;
    typeEditor = new QLineEdit;

    QLabel *addressLabel = new QLabel;
    addressLabel->setText(tr("分区位置:"));
    QLabel *typeLabel = new QLabel;
    typeLabel->setText(tr("分区名称:"));

    QDialogButtonBox *buttonBox = createButtons();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(typeLabel, 0, 0);
    layout->addWidget(typeEditor, 0, 1);
    layout->addWidget(addressLabel, 1, 0);
    layout->addWidget(addressEditor, 1, 1);
    layout->addWidget(buttonBox, 2, 0, 1, 2);

    setLayout(layout);
    setWindowTitle(tr("添加分区"));
}

void addTypeDialog::submit()
{
    QString address = addressEditor->text();
    QString type = typeEditor->text();

    if(address.isEmpty() || type.isEmpty())
    {
        QMessageBox::information(this, tr("添加分区"), tr("请输入分区名称和位置！"));
        return;
    }

    accept();
}

void addTypeDialog::revert()
{
    addressEditor->clear();
    typeEditor->clear();
}

QDialogButtonBox *addTypeDialog::createButtons()
{
    QPushButton *closeButton = new QPushButton(tr("关闭"));
    QPushButton *revertButton = new QPushButton(tr("撤销"));
    QPushButton *submitButton = new QPushButton(tr("提交"));

    closeButton->setDefault(true);
    closeButton->setStyleSheet("background-color: rgb(231, 76, 60);color: rgb(255, 251, 240)");
    revertButton->setStyleSheet("background-color: rgb(52, 152, 219);color: rgb(255, 251, 240)");
    submitButton->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

QString addTypeDialog::getAddress()
{
    return addressEditor->text();
}

QString addTypeDialog::getType()
{
    return typeEditor->text();
}

