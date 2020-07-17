#ifndef CHANGEPSDDIALOG_H
#define CHANGEPSDDIALOG_H

#include <QDialog>
#include <QLineEdit>

class changePsdDialog : public QDialog
{
    Q_OBJECT

public:
    changePsdDialog(QWidget *parent = 0);

    QString getUserName();
    QString getPsd();

private:
    QLineEdit *nameEdit;
    QLineEdit *psdEdit;
    QLineEdit *rePsdEdit;

private slots:
    void confirmClicked();
};

#endif // CHANGEPSDDIALOG_H
