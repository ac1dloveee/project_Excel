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
   ui->tableWidget->setColumnCount(100);
   ui->tableWidget->setRowCount(100);
}
MainTable::~MainTable()
{
    delete ui;
}




//Fahrat lox i pidor
