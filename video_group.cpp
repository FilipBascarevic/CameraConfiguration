/** video_group.cpp
 *
 * Implemented all messages in Video Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include "camera_config.h"

/* Display Mode
     *
     * @param dir direction can be READ,SET. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - 768 x 574 @ 25Hz Interlaced (CCIR 574i)
     *                  * 1 - 640 x 484 @ 30Hz Interlaced (NTSC 484i)
     *                  * 2 - 1280 x 720 @ 50Hz (HDTV 720p/50)
     *                  * 3 - 1280 x 720 @ 60Hz (HDTV 720p/60)
     *                  * 4 - 1024 x 768 @ 60Hz
     *                  * 5 - 1280 x 1024 @ 60Hz
     *                  * 6 - 1360 x 768 @ 60Hz
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Display_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
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
        convert_number_to_char_array(*value, &buff_send[4],2, false);
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
        out << "ENG mode of transfer isn't acceptible for Display Mode!!!" << endl;
        return -1;
    }

    return 0;

}

/* Image Size
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * C - Centred (best integer scaling)
     *                  * H - Fit Horizontally
     *                  * V - Fit Vertically
     *                  * 1 - 1:1 Detector to Display Mapping
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Image_Size(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'S';
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
        buff_send[4] = *value;
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'S';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
            // Check response
            char value_var;
            //char *val_buff = new char [static_cast <unsigned int>(numRead - numWrite_var)];
            if (check_responce_READ(var_buff_send, static_cast <int> (numWrite_var), buff_receive, static_cast <int> (numRead), &value_var, static_cast <int> (numRead-numWrite_var))){
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

/* Display Orientation
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Top Left
     *                  * 1 - Top Right
     *                  * 2 - Bottom Left
     *                  * 3 - Bottom Right
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Display_Orientation(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'O';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'O';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
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

/* Freeze Frame
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Freeze_Frame(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'F';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Freeze Frame" << endl;
        return -1;
    }

    return 0;

}

/* HD-SDI Video Output (can only be enabled in 720p)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::HD_SDI_Video_Output(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'H';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'H';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
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

/* Analogue Video Output
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Analogue_Video_Output(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'A';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'A';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
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

/* Composite Sync on Green (574i, 484i & 720p only)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Composite_Sync_on_Green(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'G';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'G';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
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

/* ONVIF Video Output (can only be enabled in 720p)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::ONVIF_Video_Output(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
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
        convert_number_to_char_array(*value, &buff_send[4],1, false);
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[5];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'E';
        var_buff_send[4] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 5);
        // Check do we receive 5 characters
        if (numWrite_var != 5) {
            out << "Message isn't send successfully in ENG mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 6);
        // Check do we receive 6 characters
        if (numRead == 6) {
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

/* ----------------------------------------------------------------------------------------*/

/* Electronic Zoom Ratio LSB = 0.01
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 100 to 800
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Electronic_Zoom_Ratio(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'Z';
    buff_send[4] = 'R';
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
        out << "ENG mode of transfer isn't acceptible for Electronic Zoom Ratio" << endl;
        return -1;
    }

    return 0;

}

/* Electronic Zoom Pan X LSB = 1 column
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Electronic_Zoom_Pan_X(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'Z';
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],3, true);
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
        out << "ENG mode of transfer isn't acceptible for Electronic Zoom Pan X" << endl;
        return -1;
    }

    return 0;

}

/* Electronic Zoom Pan Y LSB = 1 row
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Electronic_Zoom_Pan_Y(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'Z';
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[5],3, true);
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
        out << "ENG mode of transfer isn't acceptible for Electronic Zoom Pan Y" << endl;
        return -1;
    }

    return 0;

}

/* Electronic Zoom Type
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Replicated
     *                  * 1 - Bi-linear Interpolated
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Electronic_Zoom_Type(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'Z';
    buff_send[4] = 'I';
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
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'Z';
        var_buff_send[4] = 'I';
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

/* Fill Display on Electronic Zoom
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Fill_Display_on_Electronic_Zoom(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'V';
    buff_send[3] = 'Z';
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
        var_buff_send[2] = 'V';
        var_buff_send[3] = 'Z';
        var_buff_send[4] = 'F';
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

