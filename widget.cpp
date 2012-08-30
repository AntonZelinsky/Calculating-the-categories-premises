#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *lab1 = new QLabel(trUtf8("Площадь помещения (участка), м² (S):"));
    eArea1 = new QLineEdit(tr(""));
    eArea1->setToolTip("Admin: S-площадь помещения пожарной нагрузки определяется  как ее линейная проекция на пол<br> в пределах пожарного участка ( не менее 10 м2 и не более площади помещеня), м2.");
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

    QLabel *lab3 = new QLabel(trUtf8("Пожарная нагрузка участка,  Q = "));
    eArea3 = new QLineEdit("");
    eArea3->setToolTip("Q = ∑Gᵢ*Qнᵢ");
    eArea3->setReadOnly(true);
    QHBoxLayout *lay3 = new QHBoxLayout();
    lay3->addWidget(lab3);
    lay3->addWidget(eArea3);

    QLabel *lab4 = new QLabel(trUtf8("Удельная пожарная нагрузка, g ="));
    eArea4 = new QLineEdit("");
    eArea4->setToolTip("g = Q/S");
    eArea4->setReadOnly(true);
    QHBoxLayout *lay4 = new QHBoxLayout();
    lay4->addWidget(lab4);
    lay4->addWidget(eArea4);

    QLabel *lab5 = new QLabel("Категория:");
    lab5->setToolTip("Удельная пожарная нагрузка на участке МДж /м²,g");
    eArea5 = new QLineEdit;
    eArea5->setToolTip("В1 - Более 2200<br>В2 - 1400–2200<br>В3 - 200–1400<br>В4 - 100–200");
    eArea5->setReadOnly(true);
    QHBoxLayout *lay5 = new QHBoxLayout();
    lay5->addWidget(lab5);
    lay5->addWidget(eArea5);

    QLabel *lab6 = new QLabel("Минимальное расстояние, H :");
    lab6->setToolTip("Минимальное расстояние от поверхности пожарной нагрузки до нижнего пояса ферм перекрытия (покрытия), Н м");
    eArea6 = new QLineEdit("0");
    eArea6->setValidator(new QRegExpValidator(QRegExp("[0-9.]{0,3}"), this));
    QHBoxLayout *lay6 = new QHBoxLayout();
    lay6->addWidget(lab6);
    lay6->addWidget(eArea6);

    edit<<eArea1<<eArea2<<eArea3<<eArea4<<eArea5<<eArea6;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addLayout( lay1, 0, 0 );
    gridLayout->addLayout( lay2, 1, 0 );
    gridLayout->addLayout( lay3, 0, 1 );
    gridLayout->addLayout( lay4, 1, 1 );
    gridLayout->addLayout( lay5, 0, 2 );
    gridLayout->addLayout( lay6, 1, 2 );

    setLayout( gridLayout );

}
double Widget::get(int i){
    i--;
    return edit[i]->text().toDouble();
}

void Widget::set(int i, QString s)
{
    i--;
    edit[i]->setText(s);
}
