#ifndef RIGHT_MOUSE_BUTTON_H
#define RIGHT_MOUSE_BUTTON_H
#include <QMenu>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QAction>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QKeyEvent>
class Right_mouse_button
{
private:
    QMenu *pop_menu; //Меню по правой клавише
    QAction *Action; //
public:
    Right_mouse_button();
public slots :
    void on_customContextMenuRequested(QPoint pos);
    void copyData();
};

#endif // RIGHT_MOUSE_BUTTON_H
