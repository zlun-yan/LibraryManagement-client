#ifndef ADDTYPEDIALOG_H
#define ADDTYPEDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QtWidgets/QDialogButtonBox>

class addTypeDialog : public QDialog
{
    Q_OBJECT

public:
    addTypeDialog(QWidget *parent = 0);

    QString getAddress();
    QString getType();

private:
    QDialogButtonBox *createButtons();

    QLineEdit *addressEditor;
    QLineEdit *typeEditor;

private slots:
    void revert();
    void submit();
};

#endif // ADDTYPEDIALOG_H
