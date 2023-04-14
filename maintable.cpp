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
#include <QTableWidgetItem>
#include <QWidget>
#include <QPoint>
#include <QAction>
#include <QApplication>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>
#include <QUndoCommand>
#include <QUndoStack>
#include <QPen>
#include <QUndoGroup>
MainTable::MainTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTable)
{
            ui->setupUi(this);
            ui->bee_cell_table-> setRowCount (4096);
            ui->bee_cell_table-> setColumnCount (4096);
            ui->bee_cell_table->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(ui->bee_cell_table, SIGNAL(customContextMenuRequested(QPoint)), SLOT(showContextMenu(QPoint)));
            QStringList bee_cell_table_list;
            bee_cell_table_list << "A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z";
            for (int i =1 ; i <= 163 ; i++)
            {
                bee_cell_table_list << "A"+ QString::number(i) <<"B" + QString::number(i)<<"C" + QString::number(i) <<"D" + QString::number(i) <<"E" +QString::number(i)<<"F" + QString::number(i)<<"G" + QString::number(i)<<"H" + QString::number(i)<<"I" + QString::number(i)<<"J" + QString::number(i)<<"K" + QString::number(i)<<"L" + QString::number(i)<<"M" + QString::number(i)<<"N" + QString::number(i)<<"O" + QString::number(i)<<"P" + QString::number(i)<<"Q"+ QString::number(i)<<"R"+ QString::number(i)<<"S" + QString::number(i)<<"T" + QString::number(i)<<"U" + QString::number(i)<<"V" + QString::number(i)<<"W" + QString::number(i)<<"X" + QString::number(i)<<"Y" + QString::number(i)<<"Z" + QString::number(i);
            }
            for (int i = 0 ; i <=4096;i++)
            {
                for (int j =0 ; j<=4096 ; j++)
                {
                  //Заполнение ячеек таблицы пустыми значениями
                  ui->bee_cell_table->setItem(i, j, new QTableWidgetItem(""));
                }
            }
        ui->bee_cell_table->setHorizontalHeaderLabels( bee_cell_table_list);
        //Подключение слотов клавиш
        keyCtrlC = new QShortcut(this);
        keyCtrlC->setKey(Qt::CTRL + Qt::Key_C);
        connect (keyCtrlC,SIGNAL(activated()),this,SLOT(slotShortcutCtrlC()));
        keyCtrlV = new QShortcut(this);
        keyCtrlV->setKey(Qt::CTRL + Qt::Key_V);
        connect (keyCtrlV,SIGNAL(activated()),this,SLOT(slotShortcutCtrlV()));
        keyCtrlZ = new QShortcut(this);
        keyCtrlZ->setKey(Qt::CTRL + Qt::Key_Z);
        connect (keyCtrlZ,SIGNAL(activated()),this,SLOT(slotShortcutCtrlZ()));
        Delete = new QShortcut(this);
        Delete->setKey(Qt::Key_Delete );
        connect (Delete,SIGNAL(activated()),this,SLOT(slotDelete()));
}
MainTable::~MainTable()
{
    delete ui;
}
//Реализация CTRL+C
void MainTable::slotShortcutCtrlC()
{
    QClipboard * clipboard = QApplication::clipboard();
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    QString Buffer;
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    //Нахождение выбранной области
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
       int Row_1 = 0;
       int Row_2;
       int Column_2;
       for (int i =Row_mn ;i <=Row_mx ; i++)
       {
           for (int j = Column_mn ; j<=Column_mx;j++)
           {
               if (ui->bee_cell_table->item(i,j)->text()!= "")
               {
               if (j != Column_mx){
               Buffer +=ui->bee_cell_table->item(i,j)->text() + "\t";
               }
               else {
                   Buffer +=ui->bee_cell_table->item(i,j)->text();
               }
               }
               else
               {
                   if (j != Column_mx){
                   Buffer +="\t";
                   }
               }
           }
           if (i != Row_mx)
           {
           Buffer+="\n";
           }
       }
       clipboard->setText(Buffer);
}
// РЕАЛИЗАЦИЯ CTRl+V
void MainTable::slotShortcutCtrlV()
{
    QClipboard* c_board=QApplication::clipboard();
    QString Buffer = c_board->text();
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    //НАХОЖДЕНИЕ ВЫБРАННОЙ ЯЧЕЙКИ КУДА НЕОБХОДИМО ВСТАВИТЬ
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    Row = Row_mn;
    Column = Column_mn;
    std::string Buffer_str = Buffer.toStdString();
    for (int i =0 ; i <Buffer_str.size(); i++)
    {
        if (Buffer_str[i]== '\t')
        {
            Column++;
        }
        if (Buffer_str[i]== '\n')
        {
            Row++;
            Column = Column_mn;
        }
        if (Buffer_str[i] != '\t' && Buffer_str[i] != '\n')
        {
            std::string reserve;
            while ( i < Buffer_str.size() && Buffer_str[i] != '\t' && Buffer_str[i] !='\n')
            {
                reserve+=Buffer_str[i];
                i++;
            }
            i--;
            ui->bee_cell_table->setItem(Row, Column, new QTableWidgetItem(QString::fromStdString(reserve)));
        }
    }
}

void MainTable::slotShortcutCtrlZ()
{

}
//УДаление значений из выбранной области
void MainTable::slotDelete()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    QString Buffer;
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}
void MainTable::showContextMenu(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* editBoard = new QAction(tr("Изменить границы"), this);
    QAction* Span = new QAction(tr("Объденить ячейки"), this);
    connect(Span, SIGNAL(triggered()), this, SLOT(Spans()));
    QAction* deleteCell = new QAction(tr("Очистить ячейки"), this);
    connect(deleteCell, SIGNAL(triggered()), this, SLOT(Delete_cell()));
    QAction* editFont = new QAction(tr("Изменить шрифт"), this);
    connect(editFont, SIGNAL(triggered()), this, SLOT(Change_font()));
    QAction* editColor = new QAction(tr("Изменить цвет заливки ячейки"), this);
    connect(editColor, SIGNAL(triggered()), this, SLOT(Change_Color()));
    QAction* editColor_text = new QAction(tr("Изменить цвет текста ячейки"), this);
    connect(editColor_text, SIGNAL(triggered()), this, SLOT(Change_Color_text()));
    menu->addAction(editBoard);
    menu->addAction(Span);
    menu->addAction(deleteCell);
    menu->addAction(editFont);
    menu->addAction(editColor);
    menu->addAction(editColor_text);
    menu->popup(ui->bee_cell_table->viewport()->mapToGlobal(pos));
}
void MainTable::ChangeBoard()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             //ui->bee_cell_table->item(i,j)->setTextAlignment()
        }
    }
}

void MainTable::Spans()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    QString Buffer;
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    QMessageBox::warning(this,"Внимание!","Будет сохранено только верхнее левое значение!");
    ui->bee_cell_table->setSpan(Row_mn,Column_mn,Row_mx-Row_mn+1,Column_mx-Column_mn+1);
}
void MainTable::Delete_cell()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}
void MainTable::Change_font()
{
    bool ok ;
    QFont font = QFontDialog::getFont(&ok,QFont ("Segoe UI", 9));
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setFont(font);
        }
    }
}
void MainTable::Change_Color()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setBackground(QBrush(color));
        }
    }
}

void MainTable::Change_Color_text()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setForeground(color);
        }
    }
}

void MainTable::on_pushButton_12_clicked()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setTextAlignment(Qt::AlignRight);
        }
    }
}


void MainTable::on_pushButton_10_clicked()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setTextAlignment(Qt::AlignLeft);
        }
    }
}


void MainTable::on_pushButton_11_clicked()
{
    QList<QTableWidgetItem*> items = ui->bee_cell_table->selectedItems();
    int Row_mn =0 , Row_mx =0;
    int Column_mn =0 , Column_mx = 0;
    int count = items.count();
    int Row =0 ;
    int Column =0;
    for (int i =0 ; i < count ; i++)
    {
       if (i == 0)
       {
       Row_mn = ui->bee_cell_table->row(items.at(i));
       Column_mn = ui->bee_cell_table->column(items.at(i));
       Column_mx = Column_mn;
       Row_mx = Row_mn;
       }
       Row = ui->bee_cell_table->row(items.at(i));
       Column = ui->bee_cell_table->column(items.at(i));
       if (Column < Column_mn )
       {
           Column_mn = Column;
       }
       if (Column > Column_mx)
       {
           Column_mx =Column;
       }
       if (Row < Row_mn )
       {
           Row_mn = Row;
       }
       if (Row > Row_mx)
       {
           Row_mx =Row;
       }
    }
    for (int i =Row_mn ;i <=Row_mx ; i++)
    {
        for (int j = Column_mn ; j<=Column_mx;j++)
        {
             ui->bee_cell_table->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}
