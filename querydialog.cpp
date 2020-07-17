#include "querydialog.h"

#include <QGridLayout>
#include <QDebug>

queryDialog::queryDialog(const QString totBookId, const QString totBookName, const QString totPress, const QString totType, const QString totWriter, const QString totYear, const QString totRestNum, const QString totDetails, QWidget *parent)
    : QDialog(parent)
{
    bookId = totBookId.split("|");
    bookName = totBookName.split("|");
    bookPress = totPress.split("|");
    bookType = totType.split("|");
    bookWriter = totWriter.split("|");
    bookYear = totYear.split("|");
    bookNum = totRestNum.split("|");
    bookDetails = totDetails.split("|");

    maxx = bookId.count();
    posLabel = new QLabel;
    posLabel->setText(tr("查询结果：1/%1").arg(maxx));
    posLabel->setAlignment(Qt::AlignRight);

    bookInformation = new QTextEdit;
    bookInformation->setReadOnly(true);
    updateInformation();

    button_previous = new QPushButton;
    button_previous->setText(tr("上一个"));
    button_next = new QPushButton;
    button_next->setText(tr("下一个"));

    button_previous->setStyleSheet("background-color: rgb(52, 152, 219);color: rgb(255, 251, 240)");
    button_next->setStyleSheet("background-color: rgb(26, 188, 156);color: rgb(255, 251, 240)");

    button_previous->setEnabled(nowIndex > 0);
    button_next->setEnabled(nowIndex < maxx - 1);

    connect(button_previous, SIGNAL(clicked(bool)), this, SLOT(previousClicked()));
    connect(button_next, SIGNAL(clicked(bool)), this, SLOT(nextClicked()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(bookInformation, 0, 0, 1, 2);
    layout->addWidget(posLabel, 1, 1);
    layout->addWidget(button_previous, 2, 0);
    layout->addWidget(button_next, 2, 1);

    setLayout(layout);
    setWindowTitle(tr("查询结果"));;
}

queryDialog::~queryDialog()
{
    qDebug()<<"queryDialog";
}

void queryDialog::previousClicked()
{
    nowIndex = nowIndex - 1;
    button_previous->setEnabled(nowIndex > 0);
    button_next->setEnabled(nowIndex < maxx - 1);
    updateInformation();

    posLabel->setText(tr("查询结果：%1/%2").arg(nowIndex + 1).arg(maxx));
}

void queryDialog::nextClicked()
{
    nowIndex = nowIndex + 1;
    button_previous->setEnabled(nowIndex > 0);
    button_next->setEnabled(nowIndex < maxx - 1);
    updateInformation();

    posLabel->setText(tr("查询结果：%1/%2").arg(nowIndex + 1).arg(maxx));
}

void queryDialog::updateInformation()
{
    bookInformation->clear();
    bookInformation->append(tr("书籍编号：%1").arg(bookId.at(nowIndex)));
    bookInformation->append(tr("书名：%1").arg(bookName.at(nowIndex)));
    bookInformation->append(tr("出版社：%1").arg(bookPress.at(nowIndex)));
    bookInformation->append(tr("书籍分区：%1").arg(bookType.at(nowIndex)));
    bookInformation->append(tr("作者：%1").arg(bookWriter.at(nowIndex)));
    bookInformation->append(tr("出版年份：%1").arg(bookYear.at(nowIndex)));
    bookInformation->append(tr("剩余数量：%1").arg(bookNum.at(nowIndex)));
    bookInformation->append(tr("简介：\n%1").arg(bookDetails.at(nowIndex)));
}
