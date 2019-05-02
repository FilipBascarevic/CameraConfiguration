/** tracker_group.cpp
 *
 * Implemented all messages in Tracker Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"

/* Tracker Mode
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * I - Idle
     *              * A - Acquire
     *              * T - Track
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Tracker_Mode(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
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
        out << "ENG mode of transfer isn't acceptible for Tracker Mode!!!" << endl;
        return -1;
    }

    return 0;

}

/* Tracker Type
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * 0 - Automatic (not yet implemented)
     *              * 1 - Centroid
     *              * 2 - Correlator
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Tracker_Type(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'T';
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
            char returned_char;
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), &returned_char, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // result in int
            *value = returned_char - '0';
        }
        else {
            out << "Message isn't receive successfully in READ mode" << endl;
            return -1;
        }
    }
    else if (dir == SET){
        buff_send[1] = 'S';
        // add caracter '0' to value
        buff_send[4] = static_cast <char> (*value + '0');
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
        out << "ENG mode of transfer isn't acceptible for Tracker Type!!!" << endl;
        return -1;
    }

    return 0;

}

/* Centroid Target Window Size
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 255
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Centroid_Target_Window_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'H';
    buff_send[4] = 'T';
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
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
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
        convert_number_to_char_array(*value, &buff_send[5],3, false);
        buff_send[8] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 9);
        // Check do we receive 9 characters
        if (numWrite != 9) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
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
        out << "ENG mode of transfer isn't acceptible for Centroid Target Window Size!!!" << endl;
        return -1;
    }

    return 0;

}

/* Correlator Target Window Size*
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 64
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Correlator_Target_Window_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'C';
    buff_send[4] = 'T';
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
        out << "ENG mode of transfer isn't acceptible for Correlator Target Window Size!!!" << endl;
        return -1;
    }

    return 0;

}

/* Correlator Scan Area Size (excluding target size)*
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 64
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Correlator_Scan_Area_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'C';
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
        out << "ENG mode of transfer isn't acceptible for Correlator Scan Area Size!!!" << endl;
        return -1;
    }

    return 0;

}

/* Correlator Auto-acquire Rate (1 in N frames)
     *              0 = Auto-acquire off
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 255
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Correlator_Auto_acquire_Rate(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'C';
    buff_send[4] = 'A';
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
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
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
        convert_number_to_char_array(*value, &buff_send[5],3, false);
        buff_send[8] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 9);
        // Check do we receive 9 characters
        if (numWrite != 9) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
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
        out << "ENG mode of transfer isn't acceptible for Correlator Auto-acquire Rate!!!" << endl;
        return -1;
    }

    return 0;

}

/* Target Position (relative to centre of display)
     *              LSB = 15.3 urad
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Target_Position_X(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'P';
    buff_send[4] = 'X';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead)-1, true) < 0){
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
        convert_number_to_char_array(*value, &buff_send[5],5, true);
        buff_send[11] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 12);
        // Check do we receive 12 characters
        if (numWrite != 12) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "ENG mode of transfer isn't acceptible for Target Position X!!!" << endl;
        return -1;
    }

    return 0;

}

/* Target Position (relative to centre of display)
     *              LSB = 15.3 urad
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Target_Position_Y(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'T';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead)-1, true) < 0){
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
        convert_number_to_char_array(*value, &buff_send[5],5, true);
        buff_send[11] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 12);
        // Check do we receive 12 characters
        if (numWrite != 12) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "ENG mode of transfer isn't acceptible for Target Position Y!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

