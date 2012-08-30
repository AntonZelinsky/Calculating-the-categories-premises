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
    QString category;

signals:
    void change();

public slots:
    bool addEntry( const int cat, const QString &desc, double theLow );
    void addEntry( const QString &, double );
    void addEntry(const QString & );
    bool deleteEntry();
    bool save();

private slots:
    void formula(QStandardItem*);

};

#endif // TABLE_H
