/** filters_group.cpp
 *
 * Implemented all messages in Filters Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"

/* Spatial Filter Sharpening Level
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 00 = Off to 31 = Maximum Sharpening
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Spatial_Filter_Sharpening_Level(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'S';
    buff_send[4] = 'L';
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
        out << "ENG mode of transfer isn't acceptible for Spatial Filter Sharpening Level!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Image Stabilisation Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
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
        numRead = read(buff_receive, 7);

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
        numRead = read(buff_receive, 7);

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
        out << "ENG mode of transfer isn't acceptible for Image Stabilisation Enable!!!" << endl;
        return -1;
    }

    return 0;

}

/* Image Stabilisation Image Trim (each side)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 1 to 64
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Image_Trim(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
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
        numRead = read(buff_receive, 8);

        // Check do we receive 8 characters
        if (numRead == 8) {
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
        convert_number_to_char_array(*value, &buff_send[5],2, false);
        buff_send[7] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 8);
        // Check do we receive 8 characters
        if (numWrite != 8) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'F';
        var_buff_send[3] = 'I';
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
        numRead = read(buff_receive, 8);
        // Check do we receive 8 characters
        if (numRead == 8) {
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

/* Image Stabilisation Damping
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 0 to 63
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Damping(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
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
        numRead = read(buff_receive, 8);

        // Check do we receive 8 characters
        if (numRead == 8) {
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
        convert_number_to_char_array(*value, &buff_send[5],2, false);
        buff_send[7] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 8);
        // Check do we receive 8 characters
        if (numWrite != 8) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[6];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'F';
        var_buff_send[3] = 'I';
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
        numRead = read(buff_receive, 8);
        // Check do we receive 8 characters
        if (numRead == 8) {
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

/* Image Stabilisation Threshold
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 0 to 15
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Threshold(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
    buff_send[4] = 'T';
    buff_send[5] = 'T';
    if(dir == READ) {
        buff_send[1] = 'R';
        buff_send[6] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);

        // Check do we receive 9 characters
        if (numRead == 9) {
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
        convert_number_to_char_array(*value, &buff_send[6],2, false);
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
        convert_number_to_char_array(*value, &buff_send[6],2, false);
        buff_send[8] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 9);
        // Check do we receive 9 characters
        if (numWrite != 9) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[7];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'F';
        var_buff_send[3] = 'I';
        var_buff_send[4] = 'T';
        var_buff_send[5] = 'T';
        var_buff_send[6] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite_var != 7) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 9);
        // Check do we receive 9 characters
        if (numRead == 9) {
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

/* Image Stabilisation Current Position X
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Current_Position_X(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
    buff_send[4] = 'P';
    buff_send[5] = 'X';
    buff_send[6] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
            char *val_buff = new char [static_cast <unsigned int>(numRead-numWrite)];
            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numRead-numWrite)-1, true) < 0){
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
        out << "SET mode of transfer isn't acceptible for Image Stabilisation Current Position X!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Image Stabilisation Current Position X!!!" << endl;
        return -1;
    }

    return 0;

}

/* Image Stabilisation Current Position Y
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Stabilisation_Current_Position_Y(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'R';
    buff_send[2] = 'F';
    buff_send[3] = 'I';
    buff_send[4] = 'P';
    buff_send[5] = 'Y';
    buff_send[6] = '>';
    if(dir == READ) {

        // Send it via Serial port
        numWrite = write(buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
            char *val_buff = new char [static_cast <unsigned int>(numRead-numWrite)];
            // Check response
            if (check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numRead-numWrite)-1, true) < 0){
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
        out << "SET mode of transfer isn't acceptible for Image Stabilisation Current Position Y!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Image Stabilisation Current Position Y!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Turbulence Mitigation Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Turbulence_Mitigation_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'T';
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
        numRead = read(buff_receive, 7);

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
        numRead = read(buff_receive, 7);

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
        out << "ENG mode of transfer isn't acceptible for Turbulence Mitigation Enable!!!" << endl;
        return -1;
    }

    return 0;

}

/* Turbulence Mitigation Level
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 00 = Dynamic (Min) to 16 = Static (Max),
     *                              17 = Automatic (not yet implemented)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Turbulence_Mitigation_Level(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'F';
    buff_send[3] = 'T';
    buff_send[4] = 'L';
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
        out << "ENG mode of transfer isn't acceptible for Turbulence Mitigation Level!!!" << endl;
        return -1;
    }

    return 0;

}
