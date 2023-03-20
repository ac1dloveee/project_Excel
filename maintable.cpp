#include "maintable.h"
#include "./ui_maintable.h"
#include <string>
#include <iomanip>
#include <QApplication>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>
MainTable::MainTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTable)
{
            ui->setupUi(this);
            ui->bee_cell_table-> setRowCount (1500);
            ui->bee_cell_table-> setColumnCount (1500);
            QStringList bee_cell_table_list;
            bee_cell_table_list << "A"<<"B"<<"C" <<"D"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z";
            for (int i =1 ; i <= 58 ; i++)
            {
                bee_cell_table_list << "A"+ QString::number(i) <<"B" + QString::number(i)<<"C" + QString::number(i) <<"D" + QString::number(i)<<"F" + QString::number(i)<<"G" + QString::number(i)<<"H" + QString::number(i)<<"I" + QString::number(i)<<"J" + QString::number(i)<<"K" + QString::number(i)<<"L" + QString::number(i)<<"M" + QString::number(i)<<"N" + QString::number(i)<<"O" + QString::number(i)<<"P" + QString::number(i)<<"Q"+ QString::number(i)<<"R"+ QString::number(i)<<"S" + QString::number(i)<<"T" + QString::number(i)<<"U" + QString::number(i)<<"V" + QString::number(i)<<"W" + QString::number(i)<<"X" + QString::number(i)<<"Y" + QString::number(i)<<"Z" + QString::number(i);
            }
            ui->bee_cell_table->setHorizontalHeaderLabels( bee_cell_table_list);
            //ui->bee_cell_table->setSpan(1,2,3,2); // ОБЪЕДИНЕНИЕ ЯЧЕЕК
keyCtrlC = new QShortcut(this);
keyCtrlC->setKey(/*Qt::CTRL +*/ Qt::Key_C);
connect (keyCtrlC,SIGNAL(activated()),this,SLOT(slotShortcutCtrlC()));
}
MainTable::~MainTable()
{
    delete ui;
}
void MainTable::slotShortcutCtrlC()
{
    QClipboard * clipboard = QApplication::clipboard();
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    QString Buffer;
    int Row_1 = 0;
    int Row_2 = 0;
    int count = items.count();
    for (int i =0 ; i < count ; i++)
    {
       Row_2 = ui->bee_cell_table->row(items.at(i));
       QTableWidgetItem *item = items.at(i);
       if (i == 0)
       {
       Row_1 = Row_2;
       Buffer += item->text();
       continue;
       }
       if (Row_1 != Row_2)
       {
       Row_1 = Row_2;
       Buffer +="\n";
       }
       else
       {
       Buffer +="\t";
       }
       Buffer += item->text();
       qDebug()<<Buffer;
    }
    clipboard->setText(Buffer);
}




