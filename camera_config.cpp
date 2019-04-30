#include "camera_config.h"
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