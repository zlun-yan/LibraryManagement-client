#ifndef DELTYPEDIALOG_H
#define DELTYPEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class delTypeDialog : public QDialog
{
    Q_OBJECT

public:
    delTypeDialog(QWidget *parent = 0);

    QString getTypeName();

private:
    QLineEdit *typenameEdit;
    QString typeName;

private slots:
    void submit();
};

#endif // DELTYPEDIALOG_H
