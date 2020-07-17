#include "addbookdialog.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

addBookDialog::addBookDialog(QWidget *parent)
    : QDialog(parent)
{
    QDialogButtonBox *buttonBox = createButtons();

    QLabel *bookLabel = new QLabel(tr("书名:"));
    QLabel *typeLabel = new QLabel(tr("分区:"));
    QLabel *pressLabel = new QLabel(tr("出版社:"));
    QLabel *writerLabel = new QLabel(tr("作者:"));
    QLabel *yearLabel = new QLabel(tr("出版时间:"));
    QLabel *numLabel = new QLabel(tr("添加数量:"));

    bookEditor = new QLineEdit;
    typeEditor = new QLineEdit;
    pressEditor = new QLineEdit;
    writerEdit = new QLineEdit;

    yearEditor = new QSpinBox;
    yearEditor->setMinimum(1900);
    yearEditor->setMaximum(QDate::currentDate().year());
    yearEditor->setValue(yearEditor->maximum());
    yearEditor->setReadOnly(false);

    restNumEditor = new QSpinBox;
    restNumEditor->setMinimum(1);
    restNumEditor->setMaximum(1000);
    restNumEditor->setValue(1);
    restNumEditor->setReadOnly(false);

    detailsEditor = new QTextEdit;
    detailsEditor->setPlaceholderText(tr("简介"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(bookLabel, 0, 0);
    mainLayout->addWidget(bookEditor, 0, 1);
    mainLayout->addWidget(typeLabel, 1, 0);
    mainLayout->addWidget(typeEditor, 1, 1);
    mainLayout->addWidget(pressLabel, 2, 0);
    mainLayout->addWidget(pressEditor, 2, 1);
    mainLayout->addWidget(writerLabel, 3, 0);
    mainLayout->addWidget(writerEdit, 3, 1);
    mainLayout->addWidget(yearLabel, 4, 0);
    mainLayout->addWidget(yearEditor, 4, 1);
    mainLayout->addWidget(numLabel, 5, 0);
    mainLayout->addWidget(restNumEditor, 5, 1);

    mainLayout->addWidget(detailsEditor, 0, 2, 6, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(mainLayout);
    layout->addWidget(buttonBox);

    setLayout(layout);
    setWindowTitle(tr("添加书籍"));
}

void addBookDialog::submit()
{
    QString book = bookEditor->text();
    QString type = typeEditor->text();
    QString press = pressEditor->text();
    QString writer = writerEdit->text();

    if(book.isEmpty() || type.isEmpty() || press.isEmpty() || writer.isEmpty())
    {
        QMessageBox::information(this, tr("添加书籍"), tr("请输入书名、分区、出版社和作者！"));
        return;
    }

    accept();
}

void addBookDialog::revert()
{
    bookEditor->clear();
    typeEditor->clear();
    pressEditor->clear();
    writerEdit->clear();
    yearEditor->setValue(QDate::currentDate().year());
    restNumEditor->setValue(QDate::currentDate().year());
    detailsEditor->clear();
}

QDialogButtonBox *addBookDialog::createButtons()
{
    QPushButton *closeButton = new QPushButton(tr("关闭"));
    QPushButton *revertButton = new QPushButton(tr("撤销"));
    QPushButton *submitButton = new QPushButton(tr("提交"));

    closeButton->setDefault(true);
    closeButton->setStyleSheet("background-color: rgb(231, 76, 60);color: rgb(255, 251, 240)");
    revertButton->setStyleSheet("background-color: rgb(52, 152, 219);color: rgb(255, 251, 240)");
    submitButton->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

//    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

QString addBookDialog::getBookname()
{
    return bookEditor->text();
}

QString addBookDialog::getType()
{
    return typeEditor->text();
}

QString addBookDialog::getPress()
{
    return pressEditor->text();
}

QString addBookDialog::getWriter()
{
    return writerEdit->text();
}

int addBookDialog::getYear()
{
    return yearEditor->value();
}

int addBookDialog::getRestnum()
{
    return restNumEditor->value();
}

QString addBookDialog::getDetails()
{
    return detailsEditor->toPlainText();
}
