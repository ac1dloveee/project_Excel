#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QMainWindow>
#include <QShortcut>
#include <QMenu>
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
QT_BEGIN_NAMESPACE
namespace Ui { class MainTable; }
QT_END_NAMESPACE

class MainTable : public QMainWindow
{
    Q_OBJECT

public:
    MainTable(QWidget *parent = nullptr);
    ~MainTable();

private slots:
void slotShortcutCtrlC();
void slotShortcutCtrlV();
void slotShortcutCtrlZ();
void slotDelete();
void showContextMenu(QPoint);
void ChangeBoard();
void Spans();
void Delete_cell();
void Change_font();
void Change_Color();
void Change_Color_text();
void on_pushButton_12_clicked();

void on_pushButton_10_clicked();

void on_pushButton_11_clicked();

private:
    Ui::MainTable *ui;
    QShortcut *keyCtrlC;
    QShortcut *Delete;
    QShortcut *keyCtrlV;
    QShortcut *keyCtrl;
    QShortcut *keyCtrlZ;
};

#endif // MAINTABLE_H
