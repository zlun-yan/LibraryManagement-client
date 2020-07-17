#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class queryDialog : public QDialog
{
    Q_OBJECT

public:
    queryDialog(const QString totBookId, const QString totBookName, const QString totPress, const QString totType, const QString totWriter, const QString totYear, const QString totRestNum, const QString totDetails, QWidget *parent = 0);
    ~queryDialog();

private:
    int nowIndex = 0;
    int maxx;
    QStringList bookId;
    QStringList bookName;
    QStringList bookPress;
    QStringList bookType;
    QStringList bookWriter;
    QStringList bookYear;
    QStringList bookNum;
    QStringList bookDetails;

    QTextEdit *bookInformation;
    QPushButton *button_previous;
    QPushButton *button_next;

    QLabel *posLabel;

    void updateInformation();

private slots:
    void previousClicked();
    void nextClicked();
};

#endif // QUERYDIALOG_H
