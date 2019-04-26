#include "camera_config.h"


/* DRE Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::DRE_Overlay_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'O';
    buff_send[4] = 'D';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* DRE Overlay Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::DRE_Overlay_Colour(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'O';
    buff_send[4] = 'D';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Autofocus Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Autofocus_Overlay_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'O';
    buff_send[4] = 'A';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Autofocus Overlay Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Autofocus_Overlay_Colour(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'O';
    buff_send[4] = 'A';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Tracker Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Tracker_Overlay_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'O';
    buff_send[4] = 'T';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_DRE_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'A';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_DRE_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'A';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_DRE_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'A';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_DRE_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'A';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Camera_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'C';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Camera_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'C';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Camera_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'C';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Camera_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'C';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Detector_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'D';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Detector_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'D';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Detector_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'D';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Detector_Temperature(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'D';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Electronic_Zoom(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'E';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Electronic_Zoom(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'E';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Electronic_Zoom(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'E';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Electronic_Zoom(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'E';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Focus(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'F';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Focus(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'F';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Focus(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'F';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Focus(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'F';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_DRE_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'G';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_DRE_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'G';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_DRE_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'G';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_DRE_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'G';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'M';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'M';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'M';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Mode(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'M';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_DRE_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'O';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_DRE_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'O';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_DRE_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'O';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_DRE_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'O';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Pitch_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'P';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Pitch_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'P';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Pitch_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'P';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Pitch_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'P';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'S';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'S';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'S';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Status(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'S';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Yaw_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Yaw_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Yaw_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Yaw_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Text Item Value (LSB = 0.1)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3600
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Value_Yaw_Indicator(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Y';
    buff_send[5] = 'V';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Text_Item_Enable_Optical_Field_of_View(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Z';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_column_Optical_Field_of_View(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Z';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_start_row_Optical_Field_of_View(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Z';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Text_Item_Colour_Optical_Field_of_View(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'P';
    buff_send[4] = 'Z';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::DRE_Mimic_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_start_column_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_start_row_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic Colour (Foreground)
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Foreground_Colour_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Mimic Background Colour
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Background_Colour_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'B';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Mimic Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Width_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'W';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Height_DRE(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'D';
    buff_send[5] = 'H';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
int SLX_III_class::Target_Size_Mimic_Enable(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'E';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_start_column_Target_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'X';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_start_row_Target_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'Y';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic Colour (Foreground)
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Foreground_Colour_Target_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'C';
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
        convert_number_to_char_array(*value, &buff_send[6],1, false);
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

/* Mimic Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Width_Target_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'W';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Mimic Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Mimic_Height_Target_Size(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'M';
    buff_send[4] = 'T';
    buff_send[5] = 'H';
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
        convert_number_to_char_array(*value, &buff_send[6],4, false);
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

        // Check do we receive 10 characters
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Boresight Marker Type
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Cross
     *                  * 2 - Cross (Split)
     *                  * 3 - Box
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Type(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
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
        out << "ENG mode of transfer isn't acceptible for Readout Direction!!!" << endl;
        return -1;
    }

    return 0;

}

/* Boresight Marker Column (relative to array centre)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Column(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
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

/* Boresight Marker Row (relative to array centre)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -512 to 512
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Row(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
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

/* Boresight Marker Colour
                (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 512
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Colour(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
    buff_send[4] = 'C';
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

/* Boresight Marker Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2043
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Width(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
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

/* Boresight Marker Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2043
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::Boresight_Marker_Height(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'G';
    buff_send[3] = 'B';
    buff_send[4] = 'H';
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

