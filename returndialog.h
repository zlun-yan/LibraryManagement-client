#ifndef RETURNDIALOG_H
#define RETURNDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class returnDialog : public QDialog
{
    Q_OBJECT

public:
    returnDialog(QWidget *parent = 0);

    QString getBookId();

private:
    QString bookId;

    QLineEdit *idEdit;
    QPushButton *button_confirm;

private slots:
    void confirmClicked();
};


#endif // RETURNDIALOG_H
