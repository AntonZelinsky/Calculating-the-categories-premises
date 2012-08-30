#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Table.h"
#include <QMainWindow>
#include <AddDialog.h>
#include <widget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    Table *table;
    AddDialog *addDialog;
    void createActions();
    void category();//расчитать категорию
    void buildWorkSpace();
    QTabWidget *tab;
    Widget *s;

    int qt;
private slots:
    void deleteSelected();
    void addButton();
    void qg();/// устанавливает значения Q и G
    void about();
    void save();
    void compare(int i);
};

#endif // MAINWINDOW_H
