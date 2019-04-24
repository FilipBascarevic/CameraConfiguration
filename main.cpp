#include <QCoreApplication>
#include <camera_config.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Serial serial;
    //availableSerialPorts();



    return a.exec();
}
