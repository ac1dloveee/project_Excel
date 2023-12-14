#include "right_mouse_button.h"
#include <QMenu>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QAction>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QApplication>
ContextMenuDemo::ContextMenuDemo( QWidget* parent )
    : QWidget( parent ) {

    m_menu = new QMenu( this );
    QAction* exitAction = m_menu->addAction( "Exit" );
    connect( exitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );
}

ContextMenuDemo::~ContextMenuDemo() {
}

void ContextMenuDemo::contextMenuEvent( QContextMenuEvent* e ) {
    if( m_menu ) {
        m_menu->exec( e->globalPos() );
    }
}
