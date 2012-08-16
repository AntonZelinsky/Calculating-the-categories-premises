#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QtGui>
#include "Table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8")); //настраиваем поддержку utf-8

    tab = new Table;
    addDialog = new AddDialog();
    addDialog->setWindowModality(Qt::ApplicationModal);// делаем виджет модальным - блокирование родителя

    //Устанивливаем главный виджет
    QWidget *main = new QWidget;
    QLabel *lab1 = new QLabel(trUtf8("Площадь помещения (участка), м² (S):"));
    eArea1 = new QLineEdit(tr(""));
    eArea1->setToolTip("Admin: S-площадь помещения пожарной нагрузки определяется  как ее линейная проекция на пол<br> в пределах пожарного участка ( не менее 10 м2 и не более площади помещеня), м2.");
    connect(eArea1, SIGNAL(editingFinished()),SLOT(qg()));
    QHBoxLayout *lay1 = new QHBoxLayout();
    lay1->addWidget(lab1);
    lay1->addWidget(eArea1);

    QLabel *lab2 = new QLabel(trUtf8("Площадь помещения, м² (S):"));
    QLineEdit *eArea2 = new QLineEdit(tr(""));
    QRegExp areaRegExp("[0-9.]{0,6}");
    eArea2->setEnabled(false);
    eArea1->setValidator(new QRegExpValidator(areaRegExp, this));
    eArea2->setValidator(new QRegExpValidator(areaRegExp, this));
    QHBoxLayout *lay2 = new QHBoxLayout();
    lay2->addWidget(lab2);
    lay2->addWidget(eArea2);

    QLabel *lab3 = new QLabel(trUtf8("Пожарная нагрузка участка  Q = "));
    eArea3 = new QLineEdit(tr(""));
    eArea3->setReadOnly(true);
    QHBoxLayout *lay3 = new QHBoxLayout();
    lay3->addWidget(lab3);
    lay3->addWidget(eArea3);

    QLabel *lab4 = new QLabel(trUtf8("Удельная пожарная нагрузка g ="));
    eArea4 = new QLineEdit(tr(""));
    eArea4->setReadOnly(true);
    QHBoxLayout *lay4 = new QHBoxLayout();
    lay4->addWidget(lab4);
    lay4->addWidget(eArea4);

    QLabel *lab5 = new QLabel("Категория:");
    lab5->setToolTip("Удельная пожарная нагрузка на участке МДж /м²,g");
    eArea5 = new QLineEdit();
    eArea5->setReadOnly(true);
    QHBoxLayout *lay5 = new QHBoxLayout();
    lay5->addWidget(lab5);
    lay5->addWidget(eArea5);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addLayout( lay1, 0, 0 );
    gridLayout->addLayout( lay2, 1, 0 );
    gridLayout->addLayout( lay3, 0, 1 );
    gridLayout->addLayout( lay4, 1, 1 );
    gridLayout->addWidget( tab,  2, 0, 2, 0 );
    gridLayout->addLayout( lay5, 0, 2 );

    main->setLayout( gridLayout );
    createActions();
    setWindowModified(false);// Звёздаочка в заголовке программы
    setWindowTitle(QString::fromUtf8("Расчёт категорий помещений [*] - ©Архинстрой"));//[*] нужна для установки звёздочки в зависимости от tWindowModified
    setCentralWidget(main);

    connect(tab, SIGNAL(change()), this, SLOT(qg()));
    connect(addDialog, SIGNAL(add()),SLOT(addButton()));
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
    connect(ui->save_action, SIGNAL(triggered()),  tab, SLOT(save())); /// SAVE
    connect(ui->about_action, SIGNAL(triggered()), this, SLOT(about())); /// ABOUT

 /*
    connect(ui->filter_action,SIGNAL(triggered()), this, SLOT(filterButton())); /// FILTER
*/
}

void MainWindow::deleteSelected()
{
    tab->deleteEntry();
    setWindowModified(true);// Звёздаочка в заголовке программы
}


void MainWindow::addButton(){
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
    tab->addEntry(addDialog->description,addDialog->value);
}

void MainWindow::qg(){
    this->eArea3->setText(QString::number(tab->q()));
    if(eArea1->text() != "0" && eArea1->text() != ""){
        eArea4->setText(QString::number( eArea3->text().toDouble() / eArea1->text().toDouble()) );
        if(eArea1->text() != "0" && eArea1->text() != ""){
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
    msgBox.setText("Расчёт категорий помещения<br>Версия - V1.0");
    msgBox.setInformativeText("Программа для расчёта категорий помещений по взрыво-пожарной опасности, написана при поддержке кампании ЧАСУП \"Архинстрой\".<br> Зелинский Григорий Антонович<br>г.Пинск ул. ИПД 36 к. 301<br> +375(29)6931784, 8(0165)324070");
    msgBox.exec();
}

void MainWindow::category(){
    eArea5->setText("");
    qDebug()<<eArea4->text().toDouble();
    if(eArea4->text().toDouble() >= 2200){
        eArea5->setText("В1");
    }
    if(eArea4->text().toDouble() >= 1400 && eArea4->text().toDouble() <= 2199.9){
        eArea5->setText("В2");
    }
    if(eArea4->text().toDouble() >= 180 && eArea4->text().toDouble() <= 1399.9){
        eArea5->setText("В3");
    }
    if(eArea4->text().toDouble() >= 1 && eArea4->text().toDouble() <= 179.9){
        eArea5->setText("В4");
    }
}
