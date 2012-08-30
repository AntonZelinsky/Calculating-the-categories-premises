#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "Table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8")); //настраиваем поддержку utf-8

    setWindowTitle(QString::fromUtf8("Расчёт категорий помещений [*] -  ©ЧАСУП \"Архинстрой\""));//[*] нужна для установки звёздочки в зависимости от tWindowModified

    buildWorkSpace();
    connect(s->eArea1, SIGNAL(editingFinished()),SLOT(qg()));
  /*bool b;
    QFont fnt = QFontDialog::getFont(&b);
    if(!b) {
        // Была нажата кнопка Cancel
    }
    setFont(fnt);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    connect(ui->delete_action,SIGNAL(triggered()), this, SLOT(deleteSelected())); /// DELETE
    connect(ui->exit_action, SIGNAL(triggered()),  this, SLOT(close())); /// EXIT
    connect(ui->add_action, SIGNAL(triggered()),   this, SLOT(addButton())); /// ADD
    connect(ui->save_action, SIGNAL(triggered()),  this, SLOT(save())); /// SAVE
    connect(ui->about_action, SIGNAL(triggered()), this, SLOT(about())); /// ABOUT
/*
    connect(ui->filter_action,SIGNAL(triggered()), this, SLOT(filterButton())); /// FILTER
*/
}

void MainWindow::deleteSelected()
{
    if( table->deleteEntry() ) setWindowModified(true);
}


void MainWindow::addButton()
{
    QString name = sender()->objectName();
    if (name == "add_action")
    {
        if(addDialog->isHidden())
            addDialog->show();
        else{
            addDialog->raise();
            addDialog->activateWindow();
        }
        return;
    }
    if( table->addEntry(addDialog->category, addDialog->description,addDialog->value) ) setWindowModified(true);
}
void MainWindow::save()
{
     if( table->save() )
         setWindowModified(false);
}

void MainWindow::qg()
{
    s->eArea3->setText(QString::number(table->q()));
    if(s->eArea1->text() != "0" && s->eArea1->text() != ""){
        s->eArea4->setText(QString::number( s->eArea3->text().toDouble() / s->eArea1->text().toDouble()) );
        if(s->eArea1->text() != "0" && s->eArea1->text() != ""){
            category();
        }
    }
}

/**
 * @brief Описание программы + контакты
 *
 */
void MainWindow::about(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("О программе");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Расчёт категорий помещения<br>Версия - V1.3");
    msgBox.setInformativeText("Программа для расчёта категорий помещений по взрыво-пожарной опасности, написана при поддержке кампании ЧАСУП \"Архинстрой\".<br> Зелинский Григорий Антонович<br>г.Пинск ул. ИПД 36 к. 301<br> +375(29)6931784, 8(0165)324070");
    msgBox.exec();
}

void MainWindow::category(){
    s->eArea5->setText("");
    if(s->eArea4->text().toDouble() > 0)
    {
        if(s->eArea4->text().toDouble() >= 2200.0){
            s->eArea5->setText("В1");
        }
        if(s->eArea4->text().toDouble() >= 1400.0 && s->eArea4->text().toDouble() <= 2199.99){
            s->eArea5->setText("В2");
            compare(2);
        }
        if(s->eArea4->text().toDouble() >= 200.0 && s->eArea4->text().toDouble() <= 1399.99){
            s->eArea5->setText("В3");
            compare(3);
        }
        if(s->eArea4->text().toDouble() >= 100.0 && s->eArea4->text().toDouble() <= 199.99){
            s->eArea5->setText("В4");
        }
        if(s->eArea4->text().toDouble() > 0 && s->eArea4->text().toDouble() < 99.99){
            s->eArea5->setText("Д");
        }
    }
}

void MainWindow::buildWorkSpace()
{

    QWidget *all = new QWidget;// Устанивливаем главный виджет
    s = new Widget;
    table = new Table;

    addDialog = new AddDialog();
    addDialog->setWindowModality(Qt::ApplicationModal);// делаем виджет модальным - блокирует родителя при вызове

    createActions();

    QVBoxLayout *glob = new QVBoxLayout;
    glob->addWidget( s );
    glob->addWidget( table );
    all->setLayout( glob );
    setCentralWidget( all );

    connect(table, SIGNAL(change()), this, SLOT(qg()));
    connect(addDialog, SIGNAL(add()),SLOT(addButton()));
    connect(s->eArea1, SIGNAL(editingFinished()),SLOT(qg()));
    connect(s->eArea6, SIGNAL(editingFinished()), this,SLOT(qg()));

}
void MainWindow::compare(int i)//сравнивать
{
    if(s->eArea6->text() != "0" && s->eArea6->text() != "")
    {
        if(i == 2)
        {
             qt = s->get(4) > 1400 && s->get(4) < 2200 ? 2200 : 0;// s->get(4) = g
             if(qt) if(s->get(3) >= (0.64*qt*pow(s->get(6),2))) s->set(5, "B1");
        }
        if(i == 3)
        {
             qt = s->get(4) > 200 && s->get(4) < 1400 ? 1400 : 0;
             if(qt) if( s->get(3) >= (0.64*qt*pow(s->get(6),2)) ) s->set(5, "B2");
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(isWindowModified())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Не сохранённый документ!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Вы хотите сохранить документ?");
        QPushButton* ok =  msgBox.addButton(trUtf8("Да"),QMessageBox::YesRole);
        msgBox.addButton(trUtf8("Нет"),QMessageBox::NoRole);
        msgBox.setDefaultButton(ok);
        msgBox.exec();
        if (msgBox.clickedButton() == ok) {
            table->save();
        }
    }
}
