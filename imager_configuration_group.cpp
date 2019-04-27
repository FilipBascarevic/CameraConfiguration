#include "camera_config.h"

/* Imager Identity (part 1)
     *              ‘X’ part of identity : AP5???XXXX-YY-ZZ
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Imager_Identity_Part_1(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'I';
    buff_send[4] = '1';
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
        out << "Set mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }
    else {

        // Because SET is not acceptable, in ENG we can implement only READ
        // ASK AHMED IN MONDAY!!!
    }

    return 0;

}

// SKIP ALL OTER METHODS FROM THIS GROUP BECAUSE ALL IS SIMILLAR THEN IT!!!