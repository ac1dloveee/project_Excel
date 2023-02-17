#include "maintable.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainTable w;
    w.show();
    return a.exec();
}
