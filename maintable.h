#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QMainWindow>

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

private:
    Ui::MainTable *ui;
};

#endif // MAINTABLE_H
