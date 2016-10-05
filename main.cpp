#include "danton.h"
#include "about.h"
#include "preferences.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    danton w;
     w.resize(1020, 680);
    w.show();

    return a.exec();
}
