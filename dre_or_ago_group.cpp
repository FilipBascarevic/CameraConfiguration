/** dre_or_ago_group.cpp
 *
 * Implemented all messages in DRE/AGO Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#include <camera_config.h>
#include <QtMath>

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

/* DRE Polarity
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * W - White Hot
     *              * B - Black Hot
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::DRE_Polarity(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'P';
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
        // Check do we receive 5 characters
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
        out << "ENG mode of transfer isn't acceptible for DRE Polarity!!!" << endl;
        return -1;
    }

    return 0;

}

/* AGO Lock
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * 0 - Disable Lock
     *              * 1 - Enable Lock
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::AGO_Lock(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'L';
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
        // Check do we receive 5 characters
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
        out << "ENG mode of transfer isn't acceptible for DRE Polarity!!!" << endl;
        return -1;
    }

    return 0;

}

/* DRE Display Out
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * G - Greyscale
     *              * C - Colourised (Edge enhanced / LACE only)
     * @resuilt is 0 if action is successful, otherwise is faliure
*/

int SLX_III_class::DRE_Display_Out(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'P';
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
        // Check do we receive 5 characters
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
        out << "ENG mode of transfer isn't acceptible for DRE Polarity!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------------------------------------- */

/* Change AGO Gain Nudge (Auto Only) LSB = 1%
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_AGO_Gain_Nudge(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'G';
    buff_send[4] = 'N';
    buff_send[5] = 'C';
    convert_number_to_char_array(*value, &buff_send[6],2, true);
    buff_send[9] = '>';

    if (dir == SET){

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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Change AGO Gain Nudge!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change AGO Gain Nudge!!!" << endl;
        return -1;
    }

    return 0;
}

/* Set AGO Gain Nudge (Auto Only) LSB = 1% (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to +999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Set_AGO_Gain_Nudge(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'G';
    buff_send[4] = 'N';
    buff_send[5] = 'A';
    convert_number_to_char_array(*value, &buff_send[6],3, true);
    buff_send[10] = '>';

    if (dir == SET){

        // Send it via Serial port
        numWrite = write(buff_send, 11);
        // Check do we receive 10 characters
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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Set AGO Gain Nudge!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Set AGO Gain Nudge!!!" << endl;
        return -1;
    }

    return 0;
}

/* Change AGO Gain (Semi-auto / Manual) LSB = 1% of Current Value
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_AGO_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'G';
    buff_send[4] = 'M';
    buff_send[5] = 'C';
    convert_number_to_char_array(*value, &buff_send[6],2, true);
    buff_send[9] = '>';

    if (dir == SET){

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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Change AGO Gain!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change AGO Gain!!!" << endl;
        return -1;
    }

    return 0;
}

/* Set AGO Gain (Semi-auto / Manual) / Read AGO Gain
     *
     * @param dir direction can be SET and READ. ENG mode aren't acceptable
     * @param/return value pointer can be in range 64 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Set_AGO_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'G';
    buff_send[4] = 'M';
    buff_send[5] = 'A';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        convert_number_to_char_array(*value, &buff_send[6],5, false);
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

        // Check do we receive 6 characters
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
        out << "ENG mode of transfer isn't acceptible for Set AGO Gain!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------------------------------------- */

/* Change AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_AGO_Offset_Nudge(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'O';
    buff_send[4] = 'N';
    buff_send[5] = 'C';
    convert_number_to_char_array(*value, &buff_send[6],2, true);
    buff_send[9] = '>';

    if (dir == SET){

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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Change AGO Offset Nudge!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change AGO Offset Nudge!!!" << endl;
        return -1;
    }

    return 0;
}

/* Set AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to 999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Set_AGO_Offset_Nudge(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'O';
    buff_send[4] = 'N';
    buff_send[5] = 'A';
    convert_number_to_char_array(*value, &buff_send[6],3, true);
    buff_send[10] = '>';

    if (dir == SET){

        // Send it via Serial port
        numWrite = write(buff_send, 11);
        // Check do we receive 10 characters
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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Set AGO Offset Nudge!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Set AGO Offset Nudge!!!" << endl;
        return -1;
    }

    return 0;
}

/* Change AGO Offset (Manual Only)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Change_AGO_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[1] = 'S';
    buff_send[2] = 'A';
    buff_send[3] = 'O';
    buff_send[4] = 'M';
    buff_send[5] = 'C';
    convert_number_to_char_array(*value, &buff_send[6],5, true);
    buff_send[9] = '>';

    if (dir == SET){

        // Send it via Serial port
        numWrite = write(buff_send, 12);
        // Check do we receive 12 characters
        if (numWrite != 12) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }
        // Wait response
        numRead = read(buff_receive, 12);

        // Check do we receive 10 characters
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
    else if (dir == READ) {
        out << "READ mode of transfer isn't acceptible for Change AGO Offset!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Change AGO Offset!!!" << endl;
        return -1;
    }

    return 0;
}

/* Set AGO Offset (Manual Only) / Read AGO Offset
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Set_AGO_Offset(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[12], buff_receive[12];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'O';
    buff_send[4] = 'M';
    buff_send[5] = 'A';
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
        numRead = read(buff_receive, 12);

        // Check do we receive 12 characters
        if (numRead == 12) {
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
        convert_number_to_char_array(*value, &buff_send[6],5, false);
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
        out << "ENG mode of transfer isn't acceptible for Set AGO Offset!!!" << endl;
        return -1;
    }

    return 0;

}

/* ----------------------------------------------------------------------------------------------------------------------- */

/* AGO Mode
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * A - Auto (Auto Gain and Offset)
     *              * S - Semi-auto (Manual Gain, Auto Offset)
     *              * Manual (Manual Gain and Offset)
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::AGO_Mode(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
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
        numRead = read(buff_receive, 7);

        // Check do we receive 7 characters
        if (numRead == 7) {
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
        out << "ENG mode of transfer isn't acceptible for AGO Mode!!!" << endl;
        return -1;
    }

    return 0;

}

/* DRE Speed
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::DRE_Speed(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[9], buff_receive[9];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
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
        out << "ENG mode of transfer isn't acceptible for Set AGO Offset!!!" << endl;
        return -1;
    }

    return 0;

}

/* Local Contrast Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 15
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Local_Contrast_Enhancement_Level(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
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
        out << "ENG mode of transfer isn't acceptible for Local Contrast Enhancement Level!!!" << endl;
        return -1;
    }

    return 0;

}

/* Edge Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 63
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Edge_Enhancement_Level(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
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
        out << "ENG mode of transfer isn't acceptible for Edge Enhancement Level!!!" << endl;
        return -1;
    }

    return 0;

}

/* Maximum Auto Gain
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 64 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Maximum_Auto_Gain(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[11], buff_receive[11];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
    buff_send[4] = 'G';
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
        out << "ENG mode of transfer isn't acceptible for Maximum Auto Gain!!!" << endl;
        return -1;
    }

    return 0;

}

/* High Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::High_Percentile_to_Find(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
    buff_send[4] = 'P';
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
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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
        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[7];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'A';
        var_buff_send[3] = 'C';
        var_buff_send[4] = 'P';
        var_buff_send[5] = 'H';
        var_buff_send[6] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite_var != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
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

    return 0;

}

/* Low Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Low_Percentile_to_Find(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
    buff_send[4] = 'P';
    buff_send[5] = 'L';
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
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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
        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[7];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'A';
        var_buff_send[3] = 'C';
        var_buff_send[4] = 'P';
        var_buff_send[5] = 'L';
        var_buff_send[6] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite_var != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
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

    return 0;

}

/* High grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::High_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
    buff_send[4] = 'O';
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
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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
        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[7];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'A';
        var_buff_send[3] = 'C';
        var_buff_send[4] = 'O';
        var_buff_send[5] = 'H';
        var_buff_send[6] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite_var != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
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

    return 0;

}

/* Low grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Low_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'C';
    buff_send[4] = 'O';
    buff_send[5] = 'L';
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
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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

        // Do Set operation
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
        buff_send[9] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 10);
        // Check do we receive 10 characters
        if (numWrite != 10) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }

        // Do not wait response. Instead do READ to check does value
        // SET correctly
        char var_buff_send[7];
        var_buff_send[0] = '<';
        var_buff_send[1] = 'R';
        var_buff_send[2] = 'A';
        var_buff_send[3] = 'C';
        var_buff_send[4] = 'O';
        var_buff_send[5] = 'L';
        var_buff_send[6] = '>';

        // Do READ to check SET operation
        // Send it via Serial port
        qint64 numWrite_var = write(var_buff_send, 7);
        // Check do we receive 7 characters
        if (numWrite_var != 7) {
            out << "Message isn't send successfully in READ mode" << endl;
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

    return 0;

}

/* ----------------------------------------------------------------------------------------------------------------------- */

/* AGO Region of Interest Messages <AR> */

     /* Region of Interest Centre X Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Region_of_Interest_Centre_X_Position(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'R';
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
        numRead = read(buff_receive, 10);

        // Check do we receive 11 characters
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
        convert_number_to_char_array(*value, &buff_send[6],3, true);
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
        out << "ENG mode of transfer isn't acceptible for Region of Interest Centre X Position!!!" << endl;
        return -1;
    }

    return 0;

}

/* Region of Interest Centre Y Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Region_of_Interest_Centre_Y_Position(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'R';
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
        numRead = read(buff_receive, 10);

        // Check do we receive 11 characters
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
        convert_number_to_char_array(*value, &buff_send[6],3, true);
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
        out << "ENG mode of transfer isn't acceptible for Region of Interest Centre X Position!!!" << endl;
        return -1;
    }

    return 0;

}

/* Region of Interest Size X Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Region_of_Interest_Size_X_Dimension(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'R';
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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
        out << "ENG mode of transfer isn't acceptible for Region of Interest Size X Dimension!!!" << endl;
        return -1;
    }

    return 0;

}

/* Region of Interest Size X Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Region_of_Interest_Size_Y_Dimension(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'A';
    buff_send[3] = 'R';
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
        buff_send[1] = 'S';
        convert_number_to_char_array(*value, &buff_send[6],3, false);
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
        out << "ENG mode of transfer isn't acceptible for Region of Interest Size X Dimension!!!" << endl;
        return -1;
    }

    return 0;

}