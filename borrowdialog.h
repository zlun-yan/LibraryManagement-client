#ifndef BORROWDIALOG_H
#define BORROWDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class borrowDialog : public QDialog
{
    Q_OBJECT

public:
    borrowDialog(QWidget *parent = 0);

    QString getBookId();

private:
    QString bookId;

    QLineEdit *idEdit;
    QPushButton *button_confirm;

private slots:
    void confirmClicked();
};

#endif // BORROWDIALOG_H
