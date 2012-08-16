#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Table.h"
#include <QMainWindow>
#include <AddDialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void category();

private:
    Ui::MainWindow *ui;
    Table *tab;
    AddDialog *addDialog;
    void createActions();
    QLineEdit *eArea1;
    QLineEdit *eArea3;
    QLineEdit *eArea4;
    QLineEdit *eArea5;

private slots:
    void deleteSelected();
    void addButton();
    void qg();/// устанавливает значения Q и G
    void about();
};

#endif // MAINWINDOW_H
