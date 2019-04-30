/** user_interface_group.cpp
 *
 * Implemented all messages in User Interface Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"
#include <QThread>

/* Configure RS422 Communications Baud Rate
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - 9600 baud
     *                  * 1 - 19200 baud
     *                  * 2 - 38400 baud
     *                  * 3 - 57600 baud
     *                  * 4 - 115200 baud
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Configure_Baud_Rate(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'U';
    buff_send[3] = 'R';
    buff_send[4] = 'B';
    if(dir == READ) {
        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);

        // Check do we receive 7 characters
        if (numRead == 7) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead), false) < 0){
                out << "Method isn't converted array of char into number!!!" << endl;
                return -1;
            }
        }
        else {
            out << "Message isn't receive successfully in READ mode" << endl;
            return -1;
        }
    }
    else if (dir == SET){
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],1, false);
        buff_send[6] = '>';

        // Before sending new configuration of BAUD RATE, remember
        // value of No. of Power Cycle
        int power_cycle = 0, power_cycle_old = 0;
        Number_of_Power_Cycles(READ, &power_cycle_old);

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);

        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }

        // Wait some time, because restart is a process and it
        // it can't finished immediately
        QThread::sleep(30);

        // Read No of Power Cycle again and compare it with
        // previous value. If it is different, it means that camera
        // is restarted and new UART configuration is set
        Number_of_Power_Cycles(READ, &power_cycle);

        if (power_cycle != power_cycle_old) {
            // Close serial port

            // Update UART protocol on a host
            switch (*value) {
                case 0 :
                        //serialPort.setBaudRate(QSerialPort::Baud9600);
                        BaudRate = QSerialPort::Baud9600;
                        break;
                case 1 : break;
                case 2 : break;
                case 3 : break;
                case 4 : break;
                default :
                        out << "Unknown Parity and Stop Bits" << endl;
                        break;

            }

        }

    }
    else {

        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],1, false);
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Update UART protocol on a host
        switch (*value) {
            case 0 : break;
            case 1 : break;
            case 2 : break;
            case 3 : break;
            case 4 : break;
            default :
                    out << "Unknown Parity and Stop Bits" << endl;
                    break;

        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'U';
        var_buff_send[3] = 'R';
        var_buff_send[4] = 'B';
        var_buff_send[5] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite_var != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);
        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }


    }

    return 0;

}

/* Configure RS422 Communications Parity / Stop Bits
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - 1 Stop Bit, No Parity
     *                  * 1 - 2 Stop Bits, No Parity
     *                  * 2 - 1 Stop Bit, Even Parity
     *                  * 3 - 2 Stop Bits, Even Parity
     *                  * 4 - 1 Stop Bit, Odd Parity
     *                  * 5 - 2 Stop Bits, Odd Parity
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Configure_Parity_and_Stop_Bits(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'U';
    buff_send[3] = 'R';
    buff_send[4] = 'P';
    if(dir == READ) {
        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);

        // Check do we receive 7 characters
        if (numRead == 7) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead), false) < 0){
                out << "Method isn't converted array of char into number!!!" << endl;
                return -1;
            }
        }
        else {
            out << "Message isn't receive successfully in READ mode" << endl;
            return -1;
        }
    }
    else if (dir == SET){
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],1, false);
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);

        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }

        // Update UART protocol on a host
        switch (*value) {
            case 0 : break;
            case 1 : break;
            case 2 : break;
            case 3 : break;
            case 4 : break;
            case 5 : break;
            default :
                    out << "Unknown Parity and Stop Bits" << endl;
                    break;

        }
    }
    else {

        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],1, false);
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Update UART protocol on a host
        switch (*value) {
            case 0 : break;
            case 1 : break;
            case 2 : break;
            case 3 : break;
            case 4 : break;
            case 5 : break;
            default :
                    out << "Unknown Parity and Stop Bits" << endl;
                    break;

        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'U';
        var_buff_send[3] = 'R';
        var_buff_send[4] = 'P';
        var_buff_send[5] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite_var != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7);
        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }


    }

    return 0;

}