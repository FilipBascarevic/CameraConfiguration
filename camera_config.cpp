#include "camera_config.h"
#include <QtMath>

/* UART Auto Detect Configuration
     *
     * @param serialPortName represent name of serial port for which we try to find configuration

     * @resuilt is true if action is successful, otherwise is false
*/

bool SLX_III_class::UART_Auto_Detect_Configuration(QString serialPortName)
{

    // counter which represent BaudRate. It can be form 0 to 4
    int baud_rate_cnt = 0;
    // counter which represent StopBits and Parity. It can be form 0 to 5
    int stop_bits_parity_cnt = 0;

    QSerialPort::BaudRate serialBaudRate = QSerialPort::Baud9600;
    QSerialPort::StopBits serialStopBits = QSerialPort::OneStop;
    QSerialPort::Parity serialParity = QSerialPort::NoParity;
    QSerialPort::DataBits serialDataBits = QSerialPort::Data8;

    QTextStream out(stdout);

    while(1) {

        // close serial port
        close();

        // Configure BaudRate
        switch (baud_rate_cnt) {
            case 0:
                    serialBaudRate = QSerialPort::Baud9600;
                    break;
            case 1:
                    serialBaudRate = QSerialPort::Baud19200;
                    break;
            case 2:
                    serialBaudRate = QSerialPort::Baud38400;
                    break;
            case 3:
                    serialBaudRate = QSerialPort::Baud57600;
                    break;
            case 4:
                    serialBaudRate = QSerialPort::Baud115200;
                    break;
            default:
                    out << "Unknown configuration of BaudRate" << endl;
                    break;
        }

        // Configure StopBits and Parity
        switch (baud_rate_cnt) {
            case 0:
                    serialStopBits = QSerialPort::OneStop;
                    serialParity = QSerialPort::NoParity;
                    break;
            case 1:
                    serialStopBits = QSerialPort::TwoStop;
                    serialParity = QSerialPort::NoParity;
                    break;
            case 2:
                    serialStopBits = QSerialPort::OneStop;
                    serialParity = QSerialPort::EvenParity;
                    break;
            case 3:
                    serialStopBits = QSerialPort::TwoStop;
                    serialParity = QSerialPort::EvenParity;
                    break;
            case 4:
                    serialStopBits = QSerialPort::OneStop;
                    serialParity = QSerialPort::OddParity;
                    break;
            case 5:
                    serialStopBits = QSerialPort::TwoStop;
                    serialParity = QSerialPort::OddParity;
                    break;
            default:
                    out << "Unknown configuration of StopBits and Parity" << endl;
                    break;
        }

        // Open Serial Port
        open(serialPortName, serialBaudRate, serialDataBits, serialStopBits, serialParity);

        // Try reading of UART register. If reading is successfull, this is correct configuration and break loop.
        // If it is not, increase counter/counters and try other configuration.
        int read_value;
        if (Configure_Baud_Rate(READ, &read_value, 500) == 0){
            // Reading is successfull. We found configuration.
            // Break while loop.
            // UART configuration user can check in a class fields
            break;
        }
        else {
            // Try other configuration
            if (baud_rate_cnt == 4 && stop_bits_parity_cnt == 5) {
                out << "Program can't find optimal configuration << endl";
                return false;
            }
            else if (stop_bits_parity_cnt == 5){
                baud_rate_cnt++;
                stop_bits_parity_cnt = 0;
            }
            else {
                stop_bits_parity_cnt++;
            }
        }

    }

    return true;
}

int SLX_III_class::check_responce_READ(char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len, char *value, int valLen)
{

    QTextStream out(stdout);

    // Check response
    for(int i = 0; i < buff_send_len-1; i++) {
        if(buff_send[i] != buff_receive[i]) {
            out << "Echo is not valid in READ mode" << endl;
            return -1;
        }
    }
    // Check is last caracter equal with '>'
    if(buff_receive[buff_receive_len-1] != '>') {
        out << "Last received caracter in Echo isn't '>'" << endl;
        return -1;
    }
    // result of READ operation
    for(int i = 0; i < valLen; i++)
    {
        value[i] = buff_receive[buff_send_len - 1 + i];
    }

    return 0;
}

int SLX_III_class::check_responce_SET(char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len)
{

    QTextStream out(stdout);

    if (buff_send_len == buff_receive_len) {
        for(int i = 0; i < buff_send_len; i++) {
            if(buff_send[i] != buff_receive[i]) {
                out << "Echo is not valid in SET mode" << endl;
                return -1;
            }
        }
    }
    else {
        out << "Echo message must have the same length as sent message!!!" << endl;
    }

    return 0;
}

void SLX_III_class::convert_number_to_char_array(int number, char *array, int arrayLen, bool sign)
{
    int curr_pos = 0;

    // Determine sign if it is neccesery
    if (sign) {
        if (number > 0)
            array[curr_pos] = '+';
        else
            array[curr_pos] = '-';

        curr_pos++;
    }
    number = abs(number);
    // Determine digits of number
    for (int i = 0; i < arrayLen; i++) {
        int devider = static_cast <int> (qPow(10, arrayLen - 1 - i));
        int digit = number / devider;
        array[curr_pos] = static_cast <char> ('0' + digit);
        number = number - digit * devider;
        curr_pos++;
    }

}

int SLX_III_class::convert_char_array_to_number(char *array, int *number, int arrayLen, bool sign)
{
    int curr_pos = 0;
    int curr_number = 0;

    QTextStream out(stdout);

    // Determine sign if it is neccesery
    if (sign)
        curr_pos++;

    // Determine digits of number
    for (int i = 0; i < arrayLen; i++) {
        int devider = static_cast <int> (qPow(10, arrayLen - 1 - i));
        int digit = static_cast <int> (array[curr_pos] - '0');//number / devider;
        curr_number += devider * digit;
        curr_pos++;
    }

    if (sign) {
        if (array[0] == '-') {
            *number = 0 - curr_number;
        }
        else if (array[0] == '+') {
            *number = curr_number;
        }
        else {
            out << "First sign is different then - or +" << endl;
            return -1;
        }
    }
    else {
        *number = curr_number;
    }
    return 0;
}
