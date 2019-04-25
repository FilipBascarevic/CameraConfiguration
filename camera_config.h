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

    void convert_number_to_char_array(int number, char *array, int arrayLen, bool sign);

    int convert_char_array_to_number(char *array, int *number, int arrayLen, bool sign);

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

    /* AGO Gain Messages <AG> */

    /* Change AGO Gain Nudge (Auto Only) LSB = 1%
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int Change_AGO_Gain_Nudge(DIRECTION dir, int *value);

    /* Set AGO Gain Nudge (Auto Only) LSB = 1% (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to +999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Gain_Nudge(DIRECTION dir, int *value);

     /* Change AGO Gain (Semi-auto / Manual) LSB = 1% of Current Value
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int Change_AGO_Gain(DIRECTION dir, int *value);

    /* Set AGO Gain (Semi-auto / Manual) / Read AGO Gain
     *
     * @param dir direction can be SET and READ. ENG mode aren't acceptable
     * @param/return value pointer can be in range 64 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Gain(DIRECTION dir, int *value);

     /* AGO Offset Messages <AO> */

     /* Change AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to 99
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_AGO_Offset_Nudge(DIRECTION dir, int *value);

     /* Set AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to 999
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Offset_Nudge(DIRECTION dir, int *value);

     /* Change AGO Offset (Manual Only)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_AGO_Offset(DIRECTION dir, int *value);

     /* Set AGO Offset (Manual Only) / Read AGO Offset
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Offset(DIRECTION dir, int *value);

     /* ----------------------------------------------------------------------------------------*/

     /* DRE Configuration Messages <AC> */

     /* AGO Mode
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * A - Auto (Auto Gain and Offset)
     *              * S - Semi-auto (Manual Gain, Auto Offset)
     *              * Manual (Manual Gain and Offset)
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int AGO_Mode(DIRECTION dir, char *value);

    /* DRE Speed
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int DRE_Speed(DIRECTION dir, int *value);

     /* Local Contrast Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 15
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Local_Contrast_Enhancement_Level(DIRECTION dir, int *value);

     /* Edge Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 63
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Edge_Enhancement_Level(DIRECTION dir, int *value);

     /* Maximum Auto Gain
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 64 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Maximum_Auto_Gain(DIRECTION dir, int *value);

     /* High Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_Percentile_to_Find(DIRECTION dir, int *value);

     /* Low Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_Percentile_to_Find(DIRECTION dir, int *value);

     /* High grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value);

     /* Low grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value);


     /* ----------------------------------------------------------------------------------------*/

     /* AGO Region of Interest Messages <AR> */

     /* Region of Interest Centre X Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Centre_X_Position(DIRECTION dir, int *value);

     /* Region of Interest Centre Y Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Centre_Y_Position(DIRECTION dir, int *value);

     /* Region of Interest Size X Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Size_X_Dimension(DIRECTION dir, int *value);

     /* Region of Interest Size Y Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Size_Y_Dimension(DIRECTION dir, int *value);

     /* ----------------------------------------------------------------------------------------*/

     /* Calibration Message Group <C> */

     /* Perform Calibration
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * 1 - 1 Point Internal Calibration
     *              * 2 - 2 Point Internal Calibration
     *              * 3 - 3 Point Internal Calibration
     *              * 0 - External Calibration (Offset Update Only)
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Perform_Calibration(DIRECTION dir, int *value);

     /* Automatic Calibration on Cooldown (3 point)
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Automatic_Calibration(DIRECTION dir, int *value);

     /* Stare Time (Waveband 1) LSB = 1 us
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Stare_Time(DIRECTION dir, int *value);

     /* Integration Capacitors (Waveband 1)
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Integration_Capacitors(DIRECTION dir, int *value);

     /* Select Calibration Table
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Select_Calibration_Table(DIRECTION dir, int *value);

     /* Enable Non-Uniformity Correction
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Enable_Non_Uniformity_Correction(DIRECTION dir, int *value);

     /* Reject Last Calibration
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Reject_Last_Calibration(DIRECTION dir);

     /* ----------------------------------------------------------------------------------------*/

     /* Dead Pixel Replacement Messages <CD> */

     /* Dead Pixel Replacement
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Dead_Pixel_Replacement(DIRECTION dir, int *value);

     /* ----------------------------------------------------------------------------------------*/

     /* Calibration Configuration Messages <CC> */

     /* Number of Samples 2^n Samples per Calibration Point
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 7
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Number_of_Samples(DIRECTION dir, int *value);

     /* Low Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_Target_Well_Fill(DIRECTION dir, int *value);

     /* Mid Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mid_Target_Well_Fill(DIRECTION dir, int *value);

     /* High Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_Target_Well_Fill(DIRECTION dir, int *value);

     /* Optimisation Method
     *
     * @param dir direction can be SET or READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * D - Optimisation Disabled
     *              * F - Frame Rate Limited
     *              * S - Stare Time Limited
     *              * W - Well Fills Optimised
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Method(DIRECTION dir, char *value);

     /* Optimisation Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Target_Well_Fill(DIRECTION dir, int *value);

     /* Optimisation Maximum Stare Time LSB = 1 us
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Maximum_Stare_Time(DIRECTION dir, int *value);

     /* Store Calibration Table to NVRAM
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Store_Calibration_Table_to_NVRAM(DIRECTION dir, int *value);

     /* Restore Calibration Table from NVRAM
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Restore_Calibration_Table_to_NVRAM(DIRECTION dir, int *value);

     /* Store / Restore NVRAM Progress
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be:
     *              * N - Optimisation Disabled
     *              * S - Frame Rate Limited
     *              * R - Stare Time Limited
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Store_or_Restore_NVRAM_Progress(DIRECTION dir, char *value);

};

#endif // CAMERA_CONFIG_H
