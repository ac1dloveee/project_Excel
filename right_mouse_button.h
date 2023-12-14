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
#include <QWidget>

class QMenu;

class ContextMenuDemo : public QWidget {
    Q_OBJECT

public:
    ContextMenuDemo( QWidget* parent = 0 );
    ~ContextMenuDemo();

protected:
    void contextMenuEvent( QContextMenuEvent* e );

private:
    QMenu* m_menu;

};

#endif // RIGHT_MOUSE_BUTTON_H
