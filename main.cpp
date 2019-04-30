#include <QCoreApplication>
#include <camera_config.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    //Serial serial;
    //availableSerialPorts();
    //int result;
    //int number;
    //char buff[6] = {'-', '0', '0', '1', '2', '3'};
    char buff_send[5] = {'<', 'R', 'A', 'P', '>'};
    char buff_receive[9] = {'<', 'R', 'A', 'P', '-', '1', '2', '1', '>'};
    char *buff = new char[9-5];
    int value = 0;
    SLX_III_class camera;
    if (!camera.check_responce_READ(buff_send, 5, buff_receive, 9, buff, 9-5))
    {
       out << "Success" << endl;
    }
    else {
        out << "Fail" << endl;
    }

    camera.convert_char_array_to_number(buff,&value,9-5-1, true);

    //camera.open("COM1", camera.BaudRate, camera.DataBits, camera.StopBits, camera.Parity);
    //result = camera.convert_char_array_to_number(&buff[0], &number, 5, true);



    return a.exec();
}
