#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include <serial.h>

/* Derived class from class Serial. Here ios implemented all configuration methods
 * using Serial protocol. User should find which function he/she need and call it.
 */
class SLX_III_class : Serial {

private :

    int check_responce_READ (char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len, char *value, int valLen);

    int check_responce_SET (char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len);

public :
    // This enum represents direction in methods
    enum DIRECTION {SET, READ, ENG};

    /* DRE/AGO Message Group <A> */

    /* DRE Polarity
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * W - White Hot
     *              * B - Black Hot
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int DRE_Polarity(DIRECTION dir, char *value);

     /* AGO Lock
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * 0 - Disable Lock
     *              * 1 - Enable Lock
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int AGO_Lock(DIRECTION dir, int *value);

    /* DRE Display Out
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * G - Greyscale
     *              * C - Colourised (Edge enhanced / LACE only)
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int DRE_Display_Out(DIRECTION dir, char *value);


};

#endif // CAMERA_CONFIG_H
