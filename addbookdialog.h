#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QtWidgets/QDialogButtonBox>

class addBookDialog : public QDialog
{
    Q_OBJECT

public:
    addBookDialog(QWidget *parent = 0);

    QString getBookname();
    QString getType();
    QString getPress();
    QString getWriter();
    int getYear();
    int getRestnum();
    QString getDetails();

private:
    QDialogButtonBox *createButtons();

    QLineEdit *bookEditor;
    QLineEdit *typeEditor;
    QLineEdit *pressEditor;
    QLineEdit *writerEdit;
    QSpinBox *yearEditor;
    QSpinBox *restNumEditor;
    QTextEdit *detailsEditor;

private slots:
    void revert();
    void submit();
};

#endif // ADDBOOKDIALOG_H
