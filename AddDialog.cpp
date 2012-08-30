#include "AddDialog.h"
#include <QDebug>
#include <QTextCodec>
AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent)
{
    lSelected = new QLabel("Категория материала: ");
    cSelBox = new QComboBox;
    cSelBox->addItem("Твёрдые вещества");
    cSelBox->addItem("Жидкие вещества");
    cSelBox->addItem("Газообразные вещества");
    lDescription = new QLabel("Название материала: ");
    lTheLow = new QLabel("Низшая теплота сгорания Qн, МДж/кг:");
    eDescription = new QLineEdit;
    eTheLow = new QLineEdit;

    QRegExp EDescRegExp("[A-Za-zА-Яа-я0-9 .,]{0,35}");
    QRegExp theLowRegExp("[0-9 .,]{0,6}");
    eDescription->setValidator(new QRegExpValidator(EDescRegExp, this));
    eTheLow->setValidator(new QRegExpValidator(theLowRegExp, this));

    addButton = new QPushButton("Добавить");
    addButton->setDefault(true);
    connect( addButton, SIGNAL(clicked()), SLOT(check()) );
    closeButton = new QPushButton("Закрыть");
    connect( closeButton, SIGNAL(clicked()), this, SLOT(close()) );

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget( lSelected, 0, 0, 1, 1 );
    gridLayout->addWidget( cSelBox, 0, 1, 1, 1 );
    gridLayout->addWidget( lDescription, 1, 0, 1, 1 );
    gridLayout->addWidget( eDescription, 1, 1, 1, 1 );
    gridLayout->addWidget( lTheLow, 2, 0, 1, 1 );
    gridLayout->addWidget( eTheLow, 2, 1, 1, 1 );
    gridLayout->addWidget( addButton, 3, 0, 1, 1 );
    gridLayout->addWidget( closeButton, 3, 1, 1, 1 );
    setLayout( gridLayout );

    setWindowTitle("Добавить материал");
}

void AddDialog::check()
{
    if(eDescription->text() == "")
    {
         eDescription->setFocus();
    }
    else if(eTheLow->text() == "")
    {
        eTheLow->setFocus();
    }
    else  addButtonClicked();
}

void AddDialog::addButtonClicked()
{
    category = cSelBox->currentIndex();
    description = eDescription->text();
    eTheLow->text().replace(",",".");
    value = eTheLow->text().toDouble();
    eDescription->clear();
    eTheLow->clear();
    hide();
    emit add();
}
