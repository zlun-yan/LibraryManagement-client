#include "returndialog.h"

#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

returnDialog::returnDialog(QWidget *parent)
    : QDialog(parent)
{
    idEdit = new QLineEdit;
    button_confirm = new QPushButton;
    button_confirm->setText(tr("确认"));

    button_confirm->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    connect(button_confirm, SIGNAL(clicked(bool)), this, SLOT(confirmClicked()));

    QLabel *label = new QLabel;
    label->setText(tr("书籍编号："));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(idEdit, 0, 1);
    layout->addWidget(button_confirm, 1, 1);

    setLayout(layout);
    setWindowTitle(tr("还书"));
}

void returnDialog::confirmClicked()
{
    bookId = idEdit->text();
    if(bookId.isEmpty())
    {
        QMessageBox::information(this, tr("借书"), tr("请输入书籍编号"));
        return;
    }
    accept();
}

QString returnDialog::getBookId()
{
    return bookId;
}

