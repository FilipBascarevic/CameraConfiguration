/** detector_group.cpp
 *
 * Implemented all messages in Detector Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"


/* Detector Message Group <D> */

/* Detector Array Type
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * 0 - Unknown
     *              * 1 - Hawk (640 x 512 @ 16um)
     *              * 2 - Falcon (1280 x 720 @ 12um)
     *              * 3 - Swallow
     *              * 4 - Osprey (384 x 288 @ 20um)
     *              * 5 - Merlin (1024 x 768 @ 16um)
     *              * 6 - Harrier (640 x 512 @ 24um)
     *              * 7 - Condor II (DWB 640 x 512 @ 24um)
     *              * 8 - Condor III (DWB 640 x 512 @ 20um)
     *              * 9 - Condor IV (DWB 640 x 512 @ 20um)
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Detector_Array_Type(DIRECTION dir, int *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'D';
    buff_send[3] = 'A';
    buff_send[4] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite != 5) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 7, timeOut);

        // Check do we receive 7 characters
        if (numRead == 7) {
            char *val_buff = new char [static_cast <unsigned int>(numRead - numWrite)];
            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numRead - numWrite), false) < 0){
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
        out << "SET mode of transfer isn't acceptible for Detector Array Type!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Detector Array Type!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Test Pattern Messages <DP> */
     /* Test Pattern Enable
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * 0 - Disable
     *              * 1 - Enable
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Test_Pattern_Enable(DIRECTION dir, int *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'P';
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
        var_buff_send[2] = 'D';
        var_buff_send[3] = 'P';
        var_buff_send[4] = 'E';
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

/* Test Pattern Messages <DP> */

/* Test Pattern Type
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * F - Fixed Test Pattern
     *              * M - Moving Test Pattern
     *              * 1 - Proxy Test Pattern 1
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Test_Pattern_Type(DIRECTION dir, char *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'P';
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
        numRead = read(buff_receive, 7, timeOut);

        // Check do we receive 7 characters
        if (numRead == 7) {

            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), value, static_cast <int> (numRead-numWrite))){
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

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'D';
        var_buff_send[3] = 'P';
        var_buff_send[4] = 'T';
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
            char *val_buff = new char [static_cast <unsigned int>(numRead - numWrite_var)];
            if (check_responce_READ(var_buff_send, static_cast <int> (numWrite_var), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite_var))){
                return -1;
            }

            for (int i = 0; i < static_cast <int> (numRead-numWrite_var); i++){
                if (*(value+i) != *(val_buff+i)) {
                    out << "Set value isn't equal with read value in ENG mode!!!" << endl;
                    return -1;
                }
            }


        }
        else {
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }


    }

    return 0;

}

/* -----------------------------------------------------------------------------------------*/

/* Readout Direction
     *
     * @param dir direction can be READ and SET.ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * N - Normal
     *              * H - Reversed Horizontally
     *              * V - Reversed Vertically
     *              * B - Reversed Both
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Readout_Direction(DIRECTION dir, char *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
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

            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), value, static_cast <int> (numRead-numWrite))){
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Readout Mode
     *
     * @param dir direction can be READ and SET.ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * B - ITR (Blinking)
     *              * R - IWR (Rolling)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Readout_Mode(DIRECTION dir, char *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'R';
    buff_send[4] = 'M';
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

            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), value, static_cast <int> (numRead-numWrite))){
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
        out << "ENG mode of transfer isn't acceptible for Readout Mode!!!" << endl;
        return -1;
    }

    return 0;

}

/* -----------------------------------------------------------------------------------------*/

/* Trigger Method
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * D - Display Locked
     *              * F - Free Running
     *              * E - External Trigger (Edge)
     *              * L - External Trigger (Level)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Trigger_Method(DIRECTION dir, char *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'T';
    buff_send[4] = 'M';
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

            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), value, static_cast <int> (numRead-numWrite))){
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
        out << "ENG mode of transfer isn't acceptible for Trigger Method!!!" << endl;
        return -1;
    }

    return 0;

}

/* Frame Rate (display locked only) Number of Display Frames (or Fields) per Stare
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 4
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Frame_Rate(DIRECTION dir, int *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'T';
    buff_send[4] = 'F';
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
        out << "ENG mode of transfer isn't acceptible for Frame Rate!!!" << endl;
        return -1;
    }

    return 0;

}

/* Frame Period (free running only) LSB = 1 us
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Frame_Period(DIRECTION dir, int *value, int timeOut)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'D';
    buff_send[3] = 'T';
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
        numRead = read(buff_receive, 11, timeOut);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        numRead = read(buff_receive, 11, timeOut);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        out << "ENG mode of transfer isn't acceptible for Frame Period!!!" << endl;
        return -1;
    }

    return 0;

}

