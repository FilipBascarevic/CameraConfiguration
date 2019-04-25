#include <QCoreApplication>
#include <camera_config.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Serial serial;
    //availableSerialPorts();
    //int result;
    //int number;
    //char buff[6] = {'-', '0', '0', '1', '2', '3'};
    SLX_III_class camera;
    //result = camera.convert_char_array_to_number(&buff[0], &number, 5, true);



    return a.exec();
}
