/** imager_configuration_group.cpp
 *
 * Implemented all messages in Imager Configuration Message Group.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

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

        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
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
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }
    }

    return 0;

}

/* Imager Identity (part 2)
     *              ‘Y’ and ‘Z’ parts of identity : AP5???XXXX-YY-ZZ
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Imager_Identity_Part_2(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'I';
    buff_send[4] = '2';
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

        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
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
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }
    }

    return 0;

}

/* Imager Identity (part 2)
     *              ‘Y’ and ‘Z’ parts of identity : AP5???XXXX-YY-ZZ
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Firmware_Version(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
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
        numRead = read(buff_receive, 10);

        // Check do we receive 10 characters
        if (numRead == 10) {
            char *val_buff = new char [numWrite - numRead];
            // Check response
            if (!check_responce_READ(buff_send, static_cast <int> (numWrite), buff_receive, static_cast <int> (numRead), val_buff, static_cast <int> (numRead-numWrite))){
                return -1;
            }
            // method for conversion from array of char to number
            if (convert_char_array_to_number(val_buff, value, static_cast <int> (numWrite-numRead) - 1, true) < 0){
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
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Imager Serial Number
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Imager_Serial_Number(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'S';
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

        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
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
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }
    }

    return 0;

}

/* Processing Board Serial Number
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Processing_Board_Serial_Number(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'S';
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
        out << "Set mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }
    else {

        buff_send[1] = 'R';
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in ENG mode" << endl;
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
            out << "Message isn't receive successfully in ENG mode" << endl;
            return -1;
        }
    }

    return 0;

}

/* Lens Board Serial Number
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Lens_Board_Serial_Number(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
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
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Turbulence Mitigation Available
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * 0 - No
     *                  * 1 - Yes
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Turbulence_Mitigation_Available(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[6], buff_receive[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
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
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Detector Waveband 1
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * M - Midwave (3-5um)
     *                  * L - Longwave (8-12um)
     *                  * B - BIL
     *                  * 3 - 3D BIL
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Detector_Waveband_1(DIRECTION dir, char *value)
{
    qint64 numRead, numWrite;
    char buff_send[7], buff_receive[7];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'B';
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
        out << "SET mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Default Configuration
     *
     * @param dir direction can be ENG. READ and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * S - Store to FLASH
     *                  * R - Reload from FLASH
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Default_Configuration(DIRECTION dir, char *value)
{
    qint64 numWrite;
    char buff_send[6];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'C';
    if(dir == READ) {
        out << "READ mode of transfer isn't acceptible for Default Configuration!!!" << endl;
        return -1;
    }
    else if (dir == SET){
        out << "SET mode of transfer isn't acceptible for Default Configuration!!!" << endl;
        return -1;
    }
    else {
        // Do Set operation
        buff_send[1] = 'E';
        buff_send[4] = *value;
        buff_send[5] = '>';

        // Send it via Serial port
        numWrite = write(buff_send, 6);
        // Check do we receive 6 characters
        if (numWrite != 6) {
            out << "Message isn't send successfully in SET mode" << endl;
            return -1;
        }

        // Because this message doen't accept READ, we can't check what we
        // SET. Only what we can do is to check does 6 caracters is send via UART

    }

    return 0;

}

/* ----------------------------------------------------------------------------------------*/

/* Lens Type Fitted
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * 0 - No Lens
     *                  * 1 - MW f/2, Manual Focus 35mm (Merlin 27°)
     *                  * 2 - MW f/2, Manual Focus 100mm (Merlin 9°)
     *                  * 3 - LW f/2, Manual Focus 35mm (Harrier 27°)
     *                  * 4 - LW f/2, Manual Focus 100mm (Harrier 9°)
     *                  * 5 - DualBand f/2, Manual Focus 100mm (CondorII 9°)
     *                  * 6 - DualBand f/3, Manual Focus ???mm (CondorII 2°)
     *                  * 10 - MW f/4, Fixed Focus 150mm (Hawk 4°)
     *                  * 11 - MW f/4, Fixed Focus 50mm (Hawk 12°)
     *                  * 20 - MW f/4, CZ 24mm – 326mm (Hawk 24° – 1.8°)
     *                  * 21 - MW f/5.7, CZ (Merlin 24° – 2.0°)
     *                  * 22 - MW f/4, CZ 80mm - 960mm
     *                  * 30 - LW f/3.5, DFoV Harrier 3.3°/9.9°)
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Lens_Type_Fitted(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[8], buff_receive[8];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'L';
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
        out << "Set mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens EFL Widest FoV     LSB = 1 mm
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Lens_EFL_Widest_FoV(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'L';
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
        out << "Set mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }
    else {
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

/* Lens EFL Narrowest FoV     LSB = 1 mm
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
*/
int SLX_III_class::Lens_EFL_Narrowest_FoV(DIRECTION dir, int *value)
{
    qint64 numRead, numWrite;
    char buff_send[10], buff_receive[10];
    QTextStream out(stdout);


    // Make valid message
    buff_send[0] = '<';
    buff_send[2] = 'I';
    buff_send[3] = 'L';
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
        out << "ENG mode of transfer isn't acceptible for Imager Identity (part 1)!!!" << endl;
        return -1;
    }

    return 0;

}

