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

   ui->tableWidget->setRowCount(i);
  QString h= QString::fromStdString(str);}

\
}
MainTable::~MainTable()
{
    delete ui;
}




//Fahrat lox i pidor
