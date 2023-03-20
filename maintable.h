#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QMainWindow>
#include <QShortcut>
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
private:
    Ui::MainTable *ui;
    QShortcut *keyCtrlC;

};

#endif // MAINTABLE_H
