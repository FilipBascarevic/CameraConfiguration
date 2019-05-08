/** engineering_group.cpp
 *
 * Implemented all messages in Engineering Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"

/* Use Peltier During Calibration
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * 0 - Normal Calibration
     *              * 1 - Engineering Calibration (external reference)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Use_Peltier_During_Calibration(DIRECTION dir, int *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'E';
    buff_send[3] = 'R';
    buff_send[4] = 'D';
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
        numRead = read(buff_receive, 7, timeOut);

        // Check do we receive 7 characters
        if (numRead == 7) {
            char *val_buff = new char [static_cast <unsigned int>(numRead-numWrite)];
            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numRead-numWrite), false) < 0){
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
        numRead = read(buff_receive, 7, timeOut);

        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
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

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'E';
        var_buff_send[3] = 'R';
        var_buff_send[4] = 'D';
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
        numRead = read(buff_receive, 7, timeOut);
        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            int value_var;
            char *val_buff = new char [static_cast <unsigned int>(numRead - numWrite_var)];
            if (check_responce_READ(var_buff_send, static_cast <int> (numWrite_var), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite_var))){
                return -1;
            }

            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, &value_var, static_cast <int> (numRead-numWrite_var), false) < 0){
                out << "Method isn't converted array of char into number!!!" << endl;
                return -1;
            }

            if (*value != value_var) {
                out << "Set value isn't equal with read value in ENG mode!!!" << endl;
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

/* TEC Stable (engineering calibration)
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::TEC_Stable(DIRECTION dir, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'E';
    buff_send[3] = 'R';
    buff_send[4] = 'S';
    if(dir == READ) {
        out << "READ mode of transfer isn't acceptible for TEC Stable!!!" << endl;
        return -1;
    }
    else if (dir == SET){
        buff_send[1] = 'S';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6, timeOut);

        // Check do we receive 6 characters
        if (numRead == 6) {
            // Check response
            if (check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {

        // Do Set operation
        buff_send[1] = 'S';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Because this message doen't accept READ, we can't check what we
        // SET. Only what we can do is to check does 6 caracters is send via UART


    }

    return 0;

}

/* Move Paddle
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be:
     *                  * I - In
     *                  * O - Out
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Move_Paddle(DIRECTION dir, char *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'E';
    buff_send[3] = 'R';
    buff_send[4] = 'P';
    if(dir == READ) {
        out << "READ mode of transfer isn't acceptible for Move Paddle!!!" << endl;
        return -1;
    }
    else if (dir == SET){
        buff_send[1] = 'S';
        buff_send[5] = *value;
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7, timeOut);

        // Check do we receive 7 characters
        if (numRead == 7) {
            // Check response
            if (check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {

        // Do Set operation
        buff_send[1] = 'S';
        buff_send[5] = *value;
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Because this message doen't accept READ, we can't check what we
        // SET. Only what we can do is to check does 6 caracters is send via UART


    }

    return 0;

}
