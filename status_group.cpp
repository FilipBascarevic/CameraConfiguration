/** status_group.cpp
 *
 * Implemented all messages in Status Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"

/* Camera Mode
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * C - Cooldown (read only)
     *              * O - Operate
     *              * E - Engineering
     *              * N - Calibration (NUC) (read only)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Camera_Mode(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'M';
    if(dir == READ) {
        buff_send[1] = 'R';
        buff_send[4] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite != 5) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);

        // Check do we receive 6 characters
        if (numRead == 6) {

            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), value, static_cast <int> (numRead-numWrite))){
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
        buff_send[4] = *value;
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);

        // Check do we receive 6 characters
        if (numRead == 6) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Camera Mode!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Elapsed Time Indicator (ETI) Reading
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Elapsed_Time_Indicator_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'U';
    buff_send[4] = 'E';
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
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        convert_number_to_char_array(*value, &buff_send[5],5, false);
        buff_send[10] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 11);
        // Check do we receive 11 characters
        if (numWrite != 11) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Elapsed Time Indicator!!!" << endl;
        return -1;
    }

    return 0;

}

/* Number of Power Cycles
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Number_of_Power_Cycles_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'U';
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
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        convert_number_to_char_array(*value, &buff_send[5],4, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Number of Power Cycles!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Local Board Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Local_Board_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'T';
    buff_send[4] = 'B';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead), true) < 0){
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
        out << "SET mode of transfer isn't acceptible for Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Detector Array Temperature LSB = 0.01 K
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Detector_Array_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'T';
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
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "SET mode of transfer isn't acceptible for Detector Array Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Detector Array Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Referencer Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Referencer_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'T';
    buff_send[4] = 'R';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead), true) < 0){
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
        out << "SET mode of transfer isn't acceptible for Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* FPGA Core Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

int SLX_III_class::FPGA_Core_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'T';
    buff_send[4] = 'C';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead), true) < 0){
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
        out << "SET mode of transfer isn't acceptible for FPGA Core Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for FPGA Core Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* 12V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_12V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '1';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 12V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 12V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* 3.3V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_3_3V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '2';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 3.3V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 3.3V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* 2.5V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_2_5V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '3';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 2.5V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 2.5V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* 1.5V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_1_5V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '4';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 1.5V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 1.5V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* 1.2V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_1_2V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '5';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 1.2V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 1.2V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* VCCINT (1.0V) Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_1_0V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '6';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 1.0V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 1.0V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* VCCAUX (1.8V) Supply Monitor
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Supply_Monitor_1_8V(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'S';
    buff_send[4] = '7';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for 1.8V Supply Monitor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for 1.8V Supply Monitor!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Active Fault Log Session Number
     *              Fault log wraps back to 0 (i.e. contains last 1023 sessions).
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1023
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Active_Fault_Log_Session_Number(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'F';
    buff_send[4] = 'A';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        out << "SET mode of transfer isn't acceptible for Active Fault Log Session Number!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Active Fault Log Session Number!!!" << endl;
        return -1;
    }

    return 0;

}

/* Read Session Pointer
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 1023
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Session_Pointer(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'F';
    buff_send[4] = 'S';
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
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
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
        convert_number_to_char_array(*value, &buff_send[5],4, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Session Pointer!!!" << endl;
        return -1;
    }

    return 0;

}

/* Read Word Pointer
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 31
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Word_Pointer(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'S';
    buff_send[3] = 'F';
    buff_send[4] = 'W';
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
        numRead = read(buff_receive, 8);

        // Check do we receive 8 characters
        if (numRead == 8) {
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
        convert_number_to_char_array(*value, &buff_send[5],2, false);
        buff_send[7] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 8);
        // Check do we receive 8 characters
        if (numWrite != 8) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 8);

        // Check do we receive 8 characters
        if (numRead == 8) {
            // Check response
            if (!check_responce_SET(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead))){
                return -1;
            }

        }
        else {
            out << "Message isn't receive successfully in SET mode" << endl;
            return -1;
        }
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Word Pointer!!!" << endl;
        return -1;
    }

    return 0;

}

/* Read Fault Log Word
     *              (returns fault log word specified by Session Pointer and Word Pointer above)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Fault_Log_Word(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'F';
    buff_send[4] = 'D';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "SET mode of transfer isn't acceptible for Read Fault Log Word!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Fault Log Word!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Read Detector Frame Period LSB = 1 us
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Detector_Frame_Period(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'D';
    buff_send[4] = 'P';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "SET mode of transfer isn't acceptible for Read Detector Frame Period!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Detector Frame Period!!!" << endl;
        return -1;
    }

    return 0;

}

/* Read Image Mean
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Image_Mean(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'D';
    buff_send[4] = 'M';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "SET mode of transfer isn't acceptible for Read Image Mean!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Image Mean!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Read Video Frame/Field Period
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Read_Video_Frame(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'S';
    buff_send[3] = 'V';
    buff_send[4] = 'P';
    buff_send[5] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "SET mode of transfer isn't acceptible for Read Video Frame/Field Period!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Read Video Frame/Field Period!!!" << endl;
        return -1;
    }

    return 0;

}

