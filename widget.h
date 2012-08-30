#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    
    double get(int i);//получить значение QlineEdit i-го
    void set(int i, QString s);//установить занчение(s) QlineEdit i-го
    QLineEdit *eArea1;
    QLineEdit *eArea3;
    QLineEdit *eArea4;
    QLineEdit *eArea5;
    QLineEdit *eArea6;
private:
    QList<QLineEdit*> edit;

signals:
    
public slots:
    
};

#endif // WIDGET_H
