#include <QCoreApplication>
#include <camera_config.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    SLX_III_class camera;
    //Serial response;
    availableSerialPorts();

    bool camera_status = camera.open("COM1", camera.BaudRate, camera.DataBits, camera.StopBits, camera.Parity);

    //availableSerialPorts();

    //char send_data[5] = {'<', 'R', 'A', 'P', '>'};
    //char receive_data[6];
    //int num_writes = camera.write(send_data, 5);
    //int num_read = camera.read(receive_data, 6, false);
    out << endl;

    //out << "DRE/AGO Message Group" << endl;
    out << "Reading :" << endl;

    //char value = 0;
    int value = 0;
    int result = camera.Turbulence_Mitigation_Level(SLX_III_class::READ, &value);
    //int result = camera.TEC_Stable(SLX_III_class::READ);

    out << "Returned value is value = " << value << endl;

    if (!result) {
        out << "Successful Reading ..." << endl;
    }
    else {
        value = 'O';
    }

    out << endl;
    out << "Writing :" << endl;

    //value = 'G';
    //value = -12345;
    result = camera.Turbulence_Mitigation_Level(SLX_III_class::SET, &value);
    //result = camera.TEC_Stable(SLX_III_class::SET);

    if (!result) {
        out << "Successful Writing ..." << endl;
    }

    out << endl;
    out << "Engineering :" << endl;

    //value = 'G';
    //value = -12345;
    result = camera.Turbulence_Mitigation_Level(SLX_III_class::ENG, &value);
    //result = camera.TEC_Stable(SLX_III_class::ENG);

    if (!result) {
        out << "Successful Engineering ..." << endl;
    }

    camera.close();
    //response.close();



    //camera.UART_Auto_Detect_Configuration("COM1");
    //if (!camera.check_responce_READ(buff_send, 5, buff_receive, 9, buff, 9-5))
    //{
    //   out << "Success" << endl;
    //}
    //else {
    //    out << "Fail" << endl;
    //}

    //camera.convert_char_array_to_number(buff,&value,9-5-1, true);

    //camera.open("COM1", camera.BaudRate, camera.DataBits, camera.StopBits, camera.Parity);
    //result = camera.convert_char_array_to_number(&buff[0], &number, 5, true);



    return a.exec();
}
