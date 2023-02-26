#include "maintable.h"
#include "./ui_maintable.h"
#include <string>
#include <iomanip>
#include <QApplication>
#include <QString>
MainTable::MainTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTable)
{
   ui->setupUi(this);
ui->tableWidget->setColumnCount(1500);
for (int i =0 ; i <1500;i++){
    std::string str = std::to_string(i+64);
  // ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z");
   ui->tableWidget->setRowCount(i);
  QString h= QString::fromStdString(str);
ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<h);}
\
}
MainTable::~MainTable()
{
    delete ui;
}




//Fahrat lox i pidor
