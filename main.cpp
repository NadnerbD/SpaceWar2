#include <QtGui/QApplication>
#include "swGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    swGame w;
    w.show();
    return a.exec();
}
