#include <QCoreApplication>
#include "apploop.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    AppLoop appLoop;
    appLoop.run();

    return application.exec();
}
