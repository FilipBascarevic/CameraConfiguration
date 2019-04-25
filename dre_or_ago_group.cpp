#include <camera_config.h>



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