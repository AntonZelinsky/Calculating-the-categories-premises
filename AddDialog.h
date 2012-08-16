#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QtGui>
#include <QDialog>

class AddDialog : public QDialog
{
    Q_OBJECT

private:
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

signals:
    void add();

private slots:
    void check();

};

#endif // ADDDIALOG_H
