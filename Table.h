#ifndef TABLE_H
#define TABLE_H
#include <QtGui>

class Table : public  QTableView
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = 0);
    void open();
    double q();

private:
    QStandardItemModel *model_;
    double temp;
    int in;

signals:
    void change();

public slots:
    void addEntry( const QString &, double );
    void addEntry(const QString & );
    void deleteEntry();
    void save();

private slots:
    void formula(QStandardItem*);

};

#endif // TABLE_H
