#ifndef DELBOOKDIALOG_H
#define DELBOOKDIALOG_H

#include <QDialog>
#include <QLineEdit>

class delBookDialog : public QDialog
{
    Q_OBJECT

public:
    delBookDialog(QWidget *parent = 0);

    QString getBookId();

private:
    QLineEdit *idEdit;
    QString id;

private slots:
    void submit();
};

#endif // DELBOOKDIALOG_H
