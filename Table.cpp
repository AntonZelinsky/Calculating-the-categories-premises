#include "Table.h"
#include <QDebug>
#include "NotEditableDelegate.h"
Table::Table(QWidget *parent) :
    QTableView(parent)
{
    model_ = new QStandardItemModel(0, 3, this);
    in = 0; // блакирует возможность повторного добовлений значения и пересчёта

    QStringList head; // Заполняем заголовок таблицы
    head<<"Название материала"<<"Коли-во, G кг."<<"НТС Qн, МДж/кгˉ¹ "<<"ПНМ Q, МДжˉ² ";
    QStringList headTIP;
    headTIP<<"Название материала"<<"Коли-во, G кг."<<"Низшая теплота сгорания Qн, МДж/кгˉ¹"<<"Пожарная нагрузка материала Q, МДжˉ²";
    for(int i = 0; i < 4; i++){
        model_->setHorizontalHeaderItem(i, new QStandardItem(head[i]));
        model_->horizontalHeaderItem(i)->setToolTip(headTIP[i]);//подсказки в заголовке
    }

    setItemDelegateForColumn(0, new NotEditableDelegate());//Запрет  на редактирование колонок, создан класс
    setItemDelegateForColumn(2, new NotEditableDelegate());//NotEditableDelegate  в ктором предопрелён метод
    setItemDelegateForColumn(3, new NotEditableDelegate());//createEditor запрещающий  редактировать колонки
    open();/// вызов этой функции обязателен до соединения сигнала itemChanged и слота formula
    connect(model_, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(formula(QStandardItem*)));
    this->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
//  horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setStretchLastSection(true);
    setModel(model_);
    resizeColumnToContents(0);
    resizeColumnToContents(2);
    resizeColumnToContents(3);
    resizeRowsToContents();
}

void Table::addEntry( const QString &desc, double theLow)
{
    QStringList list;
    list<<desc.toUtf8()<<"0"<<QString::number(theLow)<<"0";
    model_->insertRow(model_->rowCount());
    in = 1;
    for(int i = 0; i < 4; i++)
    {
        model_->setItem(model_->rowCount()-1, i, new QStandardItem(list[i]));
    }
    in = 0;
}

bool Table::addEntry( const int cat, const QString &desc, double theLow)
{
    category = (cat == 0 ? "Твердые вещества" : cat == 1 ? "Жидкие вещества" : "Газообразные вещества" );
    for(int is = 0; is < model_->rowCount(); is++)
        if(model_->item(is,0)->text() == category)
        {
            QStringList list;
            list<<desc.toUtf8()<<"0"<<QString::number(theLow)<<"0";
            model_->insertRow(++is);
            in = 1;
            for(int i = 0; i < 4; i++)
            {
                model_->setItem(is, i, new QStandardItem(list[i]));
            }
            in = 0;
            return true;
        }
    return false;
}

bool Table::deleteEntry(){
    QModelIndexList indexes( selectedIndexes() );
    if(indexes.isEmpty()){
        QMessageBox::warning(this,"Ошибка","Не выделена ячейка");
        return false;
    }
    else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Удаление");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Удаление материала.");
        msgBox.setInformativeText("Вы уверены?");
        msgBox.addButton(trUtf8("Да"),QMessageBox::YesRole);
        QPushButton* no = msgBox.addButton(trUtf8("Нет"),QMessageBox::NoRole);
        msgBox.setDefaultButton(no);
        msgBox.exec();
        if (msgBox.clickedButton() == no) {
            return false;
        }
    }
    model_->removeRow(indexes[0].row());
    return true;
}

void Table::addEntry(const QString &set){
    model_->insertRow(model_->rowCount());
    model_->setItem(model_->rowCount()-1,1, new QStandardItem("0"));/// невидимые  ячейки  заполняем
    model_->setItem(model_->rowCount()-1,2, new QStandardItem("0"));/// нулями, чтобы небыло проблем
    model_->setItem(model_->rowCount()-1,3, new QStandardItem("0"));/// при манипуляциях со строками
    model_->setItem(model_->rowCount()-1,0, new QStandardItem(set));
    this->setSpan(model_->rowCount()-1,0,1,4);
}

void Table::open()
{
    if (!QFile::exists("./data.xml"))
    {
        QMessageBox::critical(this,"Ошибка","Файл date.xml не найден!");
        return;
    }

    QFile file("./data.xml");
    if( !file.open(QIODevice::ReadOnly) )
    {
        QMessageBox::critical(this,"Ошибка","Файл date.xml используется другим приложением!");
       return;
    }

    QXmlStreamReader xml(&file);
    xml.readNext();
    xml.readNext();
    xml.readNextStartElement();
    while (!xml.atEnd()){
        if(xml.isStartElement()){
            if(xml.name() == "substance"){
                Q_ASSERT(xml.isStartElement() && xml.name() == "substance");
                addEntry(xml.attributes().value("name").toString());
            }
            if(xml.name() == "element"){
                Q_ASSERT(xml.isStartElement() && xml.name() == "element");
                QString Temp = xml.attributes().value("value").toUtf8();
                Temp.replace(",", ".");
                addEntry(xml.attributes().value("name").toString(), Temp.toDouble());
            }
            xml.readNext();
        }
        xml.readNext();
    }
}

bool Table::save()
{
    QFile file("./data.xml");
    if( !file.open(QIODevice::WriteOnly) )
    {
        QMessageBox::critical(this,"Ошибка","Файл date.xml используется другим приложением!");
        return false;
    }
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("materials");
    for(int i =0; i <model_->rowCount(); i++){
        if(model_->item(i,2)->text().toDouble() == 0){
            if(i != 0) xml.writeEndElement();
            xml.writeStartElement("substance");
            xml.writeAttribute("name", model_->item(i,0)->text());
        }
        else {
            xml.writeStartElement("element");
            xml.writeAttribute("name", model_->item(i,0)->text());// вывод названия материала
            xml.writeAttribute("value", model_->item(i,2)->text());// вывод значения
            xml.writeEndElement();
        }
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    file.close();
    QMessageBox::information(this,"Сохранение","Файл сохранён");
    return true;
}

void Table::formula(QStandardItem *item)
{
    if(!in){
        temp = 0;
        temp = ( model_->item(item->row(),1)->text().toDouble()) * (model_->item(item->row(),2)->text().toDouble() );
        model_->item(item->row(),3)->setText(QString::number(temp));//заносим значение в новую ячейку
    }
    emit change();
}

double Table::q()
{
    temp = 0;
    if(!in){
        for(int i = 0; i < model_->rowCount(); i++){
            temp += model_->item(i,3)->text().toDouble();
        }
    }
    return temp;
}
