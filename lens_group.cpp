#include "camera_config.h"

/* Change Zoom (Relative)
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * N - Zoom towards Narrow (at Zoom Speed below)
     *              * W - Zoom towards Wide (at Zoom Speed below)
     *              * S - Stop
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_Zoom(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'L';
    buff_send[3] = 'Z';
    buff_send[4] = 'R';
    buff_send[5] = *value;
    buff_send[6] = '>';

    if(dir == SET){

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
    }
    else if (dir == READ){
        out << "READ mode of transfer isn't acceptible for Change Zoom (Relative)!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change Zoom (Relative)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Zoom Position EFL in mm (values outside range for lens restricted)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Zoom_Position_EFL(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'Z';
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Zoom Speed Approximate rate of EFL change in mm/sec
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Zoom_Speed(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'Z';
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Change Focus (Relative)
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * F - Focus towards Far/Infinity (at Focus Speed below)
     *              * N - Focus towards Near (at Focus Speed below)
     *              * S - Stop
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_Focus(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'L';
    buff_send[3] = 'F';
    buff_send[4] = 'R';
    buff_send[5] = *value;
    buff_send[6] = '>';

    if(dir == SET){

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
    }
    else if (dir == READ){
        out << "READ mode of transfer isn't acceptible for Change Zoom (Relative)!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change Zoom (Relative)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus Position Focus distance in 0.1m (positive values) or Encoder steps beyond infinity position (negative values)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 262143
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Position(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[13], buff_receive[13];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'F';
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
        numRead = read(buff_receive, 13);

        // Check do we receive 13 characters
        if (numRead == 13) {
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],6, true);
        buff_send[12] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 13);
        // Check do we receive 13 characters
        if (numWrite != 13) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 13);

        // Check do we receive 13 characters
        if (numRead == 13) {
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus Speed Approximate rate of focus change as %/sec
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Speed(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus ramping beyond infinity (change relative)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Focus_ramping_beyond_infinity(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'F';
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
        var_buff_send[2] = 'L';
        var_buff_send[3] = 'F';
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

/* ----------------------------------------------------------------------------------------*/

/* Optimise Focus Distance (single sweep)
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Idle
     *                  * 1 - Optimise Initiate (Read Running)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Optimise_Focus_Distance(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'A';
    buff_send[4] = 'O';
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
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Optimise Focus Distance!!!" << endl;
        return -1;
    }

    return 0;

}

/* Autofocus Nearest Position (Max Encoder Posn)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 5130
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Autofocus_Nearest_Position(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'A';
    buff_send[4] = 'N';
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],4, true);
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
        out << "ENG mode of transfer isn't acceptible for Autofocus Nearest Position!!!" << endl;
        return -1;
    }

    return 0;

}

/* Autofocus Furthest Position (Max Encoder Posn)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 5130
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Autofocus_Furthest_Position(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'A';
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
        numRead = read(buff_receive, 11);

        // Check do we receive 11 characters
        if (numRead == 11) {
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],4, true);
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
        out << "ENG mode of transfer isn't acceptible for Autofocus Nearest Position!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Elapsed Time Indicator (ETI) Reading Lens Controller Operating Hours
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Elapsed_Time_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'S';
    buff_send[4] = 'E';
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
        out << "SET mode of transfer isn't acceptible for Elapsed Time Indicator!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Elapsed Time Indicator!!!" << endl;
        return -1;
    }

    return 0;

}

/* Elapsed Time Indicator (ETI) Reading Lens Controller Operating Hours
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Number_of_Power_Cycles(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'S';
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
        out << "SET mode of transfer isn't acceptible for Number of Power Cycles!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Number of Power Cycles!!!" << endl;
        return -1;
    }

    return 0;

}

/* Humidity Sensor Reading % RH (relative humidity)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

int SLX_III_class::Humidity_Sensor(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'S';
    buff_send[4] = 'H';
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
        out << "SET mode of transfer isn't acceptible for Humidity Sensor!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Humidity Sensor!!!" << endl;
        return -1;
    }

    return 0;

}

// ASK AHMED

/* ----------------------------------------------------------------------------------------*/

/* Zoom Narrow Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Zoom_Narrow_Hard_Stop_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
    buff_send[4] = 'N';
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

        // Check do we receive 11 characters
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
        out << "SET mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Zoom Wide Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Zoom_Wide_Hard_Stop_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
    buff_send[4] = 'W';
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

        // Check do we receive 11 characters
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
        out << "SET mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus Far (Infinity) Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Far_Hard_Stop_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
    buff_send[4] = 'F';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus Near (Close) Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Near_Hard_Stop_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus Optocouple Sensor Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Optocouple_Sensor_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
    buff_send[4] = 'S';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Zoom Optical Reference Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Zoom_Optical_Reference_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
    buff_send[4] = 'Z';
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

        // Check do we receive 11 characters
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
        out << "SET mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Zoom Narrow Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* Focus (Atherm) Optical Reference Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Focus_Optical_Reference_Datum(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'D';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Focus Far (Infinity) Hard Stop Datum!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Lens Local Board Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Local_Board_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 1 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_1(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 2 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_2(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 3 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_3(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 4 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_4(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 5 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_5(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 6 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_6(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 7 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_7(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Temperature Sensor 8 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Temperature_Sensor_8(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'T';
    buff_send[4] = '8';
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
        out << "SET mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Local Board Temperature!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Lens Calibration Temperature 1
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_1(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 1!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 1!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 2
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_2(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 2!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 2!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 3
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_3(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 3!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 3!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 4
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_4(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 4!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 4!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 5
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_5(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 5!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 5!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 6
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_6(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 6!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 6!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 7
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_7(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 7!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 7!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Calibration Temperature 8
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Calibration_Temperature_8(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'L';
    buff_send[3] = 'C';
    buff_send[4] = '8';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        out << "SET mode of transfer isn't acceptible for Lens Calibration Temperature 8!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Calibration Temperature 8!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Exercise Lens Period Time (in mins) between operations (0 = never)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Exercise_Lens_Period(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'E';
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
        out << "ENG mode of transfer isn't acceptible for Exercise Lens Period!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens Exercise Next Time (in mins) until next exercise operation
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Lens_Exercise_Next(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'E';
    buff_send[4] = 'N';
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
        out << "SET mode of transfer isn't acceptible for Lens Exercise Next!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Lens Exercise Next!!!" << endl;
        return -1;
    }

    return 0;

}

/* Perform Exercise Mechanism Function
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Perform_Exercise_Mechanism_Function(DIRECTION dir)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'L';
    buff_send[3] = 'E';
    buff_send[4] = 'G';
    if(dir == READ) {
        out << "READ mode of transfer isn't acceptible for Perform Exercise Mechanism Function!!!" << endl;
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
        out << "ENG mode of transfer isn't acceptible for Perform Exercise Mechanism Function!!!" << endl;
        return -1;
    }

    return 0;

}

