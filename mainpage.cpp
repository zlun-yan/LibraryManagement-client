#include "mainpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include <QMessageBox>
#include <QHostAddress>

#include <QDebug>
#include <QDateTime>
#include <QListView>

#include "querydialog.h"
#include "borrowdialog.h"
#include "returndialog.h"
#include "addbookdialog.h"
#include "addtypedialog.h"
#include "delbookdialog.h"
#include "deltypedialog.h"

MainPage::MainPage(QTcpSocket* &socket, const QString &username, const QString &permission_in, QWidget *parent)
    : QMainWindow(parent)
{
    userNameTCP = username;
    permission = permission_in;

    tcpSocket = socket;
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

    QString msg = tr("informationSend;%1").arg(userNameTCP);
    tcpSocket->write(msg.toUtf8().data());

    createMenuBox();

    QGroupBox *queryBox = createQueryGroupBox();
    QGroupBox *userBox = createUserGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(queryBox);
    mainLayout->addWidget(userBox);

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(mainLayout);

    setWindowTitle(tr("XX图书馆"));
}

//发送命令给服务端
void MainPage::queryButtonClicked()
{
//    QString msg = userNameTCP + tr(":查询");
    if (queryModel == "not")
    {
        QMessageBox::information(this, tr("查询"), tr("请选择一种查询关键词"));
        return;
    }
    QString msg = tr("querySend;%1;%2").arg(queryModel).arg(queryEdit->text());
    tcpSocket->write(msg.toUtf8().data());
}

void MainPage::Borrow()
{
//    QString msg = userNameTCP + tr(":借书");
    borrowDialog *dialog = new borrowDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;
    QString bookId = dialog->getBookId();
    delete dialog;

    QString msg = tr("borrowSend;%1;%2").arg(userNameTCP).arg(bookId);
    tcpSocket->write(msg.toUtf8().data());
}

void MainPage::Return()
{
//    QString msg = userNameTCP + tr(":还书");
    returnDialog *dialog = new returnDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;
    QString bookId = dialog->getBookId();
    delete dialog;

    QString msg = tr("returnSend;%1;%2").arg(userNameTCP).arg(bookId);
    tcpSocket->write(msg.toUtf8().data());
}

void MainPage::addBook()
{
//    QString msg = userNameTCP + tr(":添加书籍");
    addBookDialog *dialog = new addBookDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;

    QString msg = tr("addBookSend;%1;%2;%3;%4;%5;%6;%7").arg(dialog->getBookname()).arg(dialog->getPress()).arg(dialog->getType()).arg(dialog->getWriter()).arg(dialog->getYear()).arg(dialog->getRestnum()).arg(dialog->getDetails());
    tcpSocket->write(msg.toUtf8().data());

    delete dialog;
}

void MainPage::addType()
{
//    QString msg = userNameTCP + tr(":添加分区");
    addTypeDialog *dialog = new addTypeDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;

    QString msg = tr("addTypeSend;%1;%2").arg(dialog->getType()).arg(dialog->getAddress());
    tcpSocket->write(msg.toUtf8().data());

    delete dialog;
}

void MainPage::delBook()
{
//    QString msg = userNameTCP + tr(":删除书籍");
    delBookDialog *dialog = new delBookDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;

    QString msg = tr("delBookSend;%1").arg(dialog->getBookId());
    tcpSocket->write(msg.toUtf8().data());

    delete dialog;
}

void MainPage::delType()
{
//    QString msg = userNameTCP + tr(":删除分区");
    delTypeDialog *dialog = new delTypeDialog(this);
    if(dialog->exec() != QDialog::Accepted)  return;

    QString msg = tr("delTypeSend;%1").arg(dialog->getTypeName());
    tcpSocket->write(msg.toUtf8().data());

    delete dialog;
}

void MainPage::slotConnected()
{
    QMessageBox::information(this, tr("客户端"), tr("与服务器重新连接"));
}

void MainPage::slotDisconnected()
{
    QMessageBox::information(this, tr("错误"), tr("与服务器断开连接"));
    close();
}

//从服务端接受命令
void MainPage::dataReceived()
{
    QByteArray array = tcpSocket->readAll();
    QString msg = array.data();

    QStringList order = msg.split(";");
    if (order.at(0) == "informationReceive")
    {
        permission = order.at(1);
        borrowNum = order.at(2);
        QString totBorrowBook = order.at(3);
        QString totBorrowDate = order.at(4);
        borrowBook = totBorrowBook.split("|");
        borrowDate = totBorrowDate.split("|");

        updateUserInformation();
    }
    else if (order.at(0) == "queryReceive")
    {
        if (order.at(1) == "accept")
        {
            queryDialog *dialog = new queryDialog(order.at(2), order.at(3), order.at(4), order.at(5), order.at(6), order.at(7), order.at(8), order.at(9), this);
            dialog->exec();
            delete dialog;
        }
        else
        {
            QMessageBox::information(this, tr("查询结果"), tr("没有找到相关书籍"));
        }
    }
    else if (order.at(0) == "borrowReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("借书"), tr("成功"));
            QString msg = tr("informationSend;%1").arg(userNameTCP);
            tcpSocket->write(msg.toUtf8().data());
        }
        else
        {
            QMessageBox::information(this, tr("借书"), tr("失败"));
        }
    }
    else if (order.at(0) == "returnReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("还书"), tr("成功"));
            QString msg = tr("informationSend;%1").arg(userNameTCP);
            tcpSocket->write(msg.toUtf8().data());
        }
        else
        {
            QMessageBox::information(this, tr("还书"), tr("失败"));
        }
    }
    else if (order.at(0) == "addBookReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("添加书籍"), tr("成功"));
        }
        else
        {
            if (order.at(2) == "NotFoundType")
            {
                int choice = QMessageBox::question(this, tr("添加书籍"), tr("您选择的分区不存在\n是否需要添加一个分区？"), QMessageBox::Yes | QMessageBox::No);

                if(choice == QMessageBox::Yes)
                {
                    addType();
                }
            }
        }
    }
    else if (order.at(0) == "addTypeReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("添加分区"), tr("成功"));
        }
        else
        {
            QMessageBox::information(this, tr("添加分区"), tr("失败"));
        }
    }
    else if (order.at(0) == "delBookReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("删数书籍"), tr("成功"));
        }
        else
        {
            QMessageBox::information(this, tr("删除书籍"), tr("失败"));
        }
    }
    else if (order.at(0) == "delTypeReceive")
    {
        if (order.at(1) == "accept")
        {
            QMessageBox::information(this, tr("删数分区"), tr("成功"));
        }
        else
        {
            QMessageBox::information(this, tr("删除分区"), tr("失败"));
        }
    }
    else
    {
        qDebug()<<msg;
    }
}

//#
QGroupBox* MainPage::createQueryGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("查询"));

    queryEdit = new QLineEdit;
    confirmButton = new QPushButton;
    confirmButton->setText(tr("查询"));

    confirmButton->setStyleSheet("background-color: rgb(248, 147, 29);color: rgb(255, 251, 240)");

    queryCombo = new QComboBox;
    queryCombo->addItem(tr("<关键词>"));
    queryCombo->addItem(tr("书名"));
    queryCombo->addItem(tr("分区"));
    queryCombo->addItem(tr("出版社"));
    queryCombo->addItem(tr("作者"));
    queryCombo->setView(new QListView());

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(queryEdit);
    layout->addWidget(queryCombo);
    layout->addWidget(confirmButton);

    connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(queryButtonClicked()));
    connect(queryCombo, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(queryChanged(const QString &)));

    box->setLayout(layout);
    return box;
}

void MainPage::updateUserInformation()
{
    userInformation->clear();
    if(permission == "manager" || permission == "root")
    {
        userInformation->append(tr("管理员 %1 , 你好").arg(userNameTCP));
    }
    else if (permission == "student")
    {
        userInformation->append(tr("同学 %1 , 你好").arg(userNameTCP));
    }

    userInformation->append(tr("你已借书 %1 本:").arg(borrowNum));
    for (int i = 0; i < borrowBook.count(); i++)
    {
        userInformation->append(tr("%1    %2").arg(borrowBook.at(i)).arg(borrowDate.at(i)));
    }
}

QGroupBox* MainPage::createUserGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("用户信息"));

    userInformation = new QTextEdit;
    userInformation->setReadOnly(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(userInformation);

    box->setLayout(layout);
    return box;
}

void MainPage::queryChanged(const QString &text)
{
    if(text == "书名")  queryModel = "bookname";
    else if(text == "分区")  queryModel = "type";
    else if(text == "出版社")  queryModel = "press";
    else if(text == "作者")  queryModel = "writer";
    else queryModel = "not";
}

void MainPage::createMenuBox()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("操作菜单"));
    QAction *borrowAction = new QAction(tr("借书"), this);
    QAction *returnAction = new QAction(tr("还书"), this);
    borrowAction->setShortcut(tr("Ctrl+B"));
    returnAction->setShortcut(tr("Ctrl+R"));

    fileMenu->addAction(borrowAction);
    fileMenu->addAction(returnAction);

    connect(borrowAction, SIGNAL(triggered(bool)), this, SLOT(Borrow()));
    connect(returnAction, SIGNAL(triggered(bool)), this, SLOT(Return()));

    if (permission == "manager")
    {
        QAction *addAction = new QAction(tr("添加书籍"), this);
        QAction *addTypeAction = new QAction(tr("添加分区"), this);
        QAction *deleteAction = new QAction(tr("删除书籍"), this);
        QAction *deleteTypeAction = new QAction(tr("删除分区"), this);

        addAction->setShortcut(tr("Ctrl+A"));
        addTypeAction->setShortcut(tr("Ctrl+Shift+A"));
        deleteAction->setShortcut(tr("Ctrl+D"));
        deleteTypeAction->setShortcut(tr("Ctrl+Shift+D"));

        fileMenu->addSeparator();
        fileMenu->addAction(addAction);
        fileMenu->addAction(addTypeAction);
        fileMenu->addAction(deleteAction);
        fileMenu->addAction(deleteTypeAction);
        fileMenu->addSeparator();

        connect(addAction, SIGNAL(triggered(bool)), this, SLOT(addBook()));
        connect(addTypeAction, SIGNAL(triggered(bool)), this, SLOT(addType()));
        connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(delBook()));
        connect(deleteTypeAction, SIGNAL(triggered(bool)), this, SLOT(delType()));
    }


    QAction *quitAction = new QAction(tr("退出"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

// 重写closeEvent: 退出时发送退出消息给服务端
void MainPage::closeEvent(QCloseEvent *event)
{
    QString msg = tr("%1: Leave").arg(userNameTCP);
    tcpSocket->write(msg.toUtf8().data());

    event->accept(); // 接受退出信号，程序退出
}
