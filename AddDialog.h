#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QRegExpValidator>
#include <QComboBox>

class AddDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *lSelected;
    QComboBox *cSelBox;
    QLabel *lDescription;
    QLabel *lTheLow;
    QLineEdit *eDescription;
    QLineEdit *eTheLow;
    QPushButton *addButton;
    QPushButton *closeButton;

    void addButtonClicked();

public:
    explicit AddDialog(QWidget *parent = 0);
    QString description;
    double value;
    int category;

signals:
    void add();

private slots:
    void check();

};

#endif // ADDDIALOG_H
