/** camera_config.h
 *
 * This class contains all configuration messages for SLX III Thermal Camera.
 * For configuration of this camera, RS422 serial interface is used.
 *
 * @author Filip Bascarevic
 *
 * @version 0.1 -- 30 April 2019
 */

#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include <serial.h>

// This enum represents direction in methods
enum DIRECTION {SET, READ, ENG};

/* Derived class from class Serial. Here ios implemented all configuration methods
 * using Serial protocol. User should find which function he/she need and call it.
 */
class SLX_III_class : public Serial {

private :

    int check_responce_READ (char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len, char *value, int valLen);

    int check_responce_SET (char *buff_send, int buff_send_len, char *buff_receive, int buff_receive_len);

    void convert_number_to_char_array(int number, char *array, int arrayLen, bool sign);

    int convert_char_array_to_number(char *array, int *number, int arrayLen, bool sign);

public :

    /* UART Auto Detect Configuration
     *
     * @param serialPortName represent name of serial port for which we try to find configuration

     * @resuilt is true if action is successful, otherwise is false
     */
    bool UART_Auto_Detect_Configuration(QString serialPortName);



    /* DRE/AGO Message Group <A> */

    /* DRE Polarity
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * W - White Hot
     *              * B - Black Hot
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int DRE_Polarity(DIRECTION dir, char *value, int timeOut = -1);

     /* AGO Lock
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * 0 - Disable Lock
     *              * 1 - Enable Lock
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int AGO_Lock(DIRECTION dir, int *value, int timeOut = -1);

    /* DRE Display Out
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * G - Greyscale
     *              * C - Colourised (Edge enhanced / LACE only)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int DRE_Display_Out(DIRECTION dir, char *value, int timeOut = -1);

    /* AGO Gain Messages <AG> */

    /* Change AGO Gain Nudge (Auto Only) LSB = 1%
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int Change_AGO_Gain_Nudge(DIRECTION dir, int *value, int timeOut = -1);

    /* Set AGO Gain Nudge (Auto Only) LSB = 1% (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to +999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Gain_Nudge(DIRECTION dir, int *value, int timeOut = -1);

     /* Change AGO Gain (Semi-auto / Manual) LSB = 1% of Current Value
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to +99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
    int Change_AGO_Gain(DIRECTION dir, int *value, int timeOut = -1);

    /* Set AGO Gain (Semi-auto / Manual) / Read AGO Gain
     *
     * @param dir direction can be SET and READ. ENG mode aren't acceptable
     * @param/return value pointer can be in range 64 to 65535
     * @param timeOut time in msec for timeout read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* AGO Offset Messages <AO> */

     /* Change AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_AGO_Offset_Nudge(DIRECTION dir, int *value, int timeOut = -1);

     /* Set AGO Offset Nudge (Auto / Semi-auto) LSB = 1% of Black-White Range (0 = No Nudge)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -999 to 999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Offset_Nudge(DIRECTION dir, int *value, int timeOut = -1);

     /* Change AGO Offset (Manual Only)
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_AGO_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* Set AGO Offset (Manual Only) / Read AGO Offset
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 65535
     * @param timeOut time in msec for timeout read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Set_AGO_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* DRE Configuration Messages <AC> */

     /* AGO Mode
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * A - Auto (Auto Gain and Offset)
     *              * S - Semi-auto (Manual Gain, Auto Offset)
     *              * M - Manual (Manual Gain and Offset)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

    int AGO_Mode(DIRECTION dir, char *value, int timeOut = -1);

    /* DRE Speed
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int DRE_Speed(DIRECTION dir, int *value, int timeOut = -1);

     /* Local Contrast Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 15
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Local_Contrast_Enhancement_Level(DIRECTION dir, int *value, int timeOut = -1);

     /* Edge Enhancement Level
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 0 to 63
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Edge_Enhancement_Level(DIRECTION dir, int *value, int timeOut = -1);

     /* Maximum Auto Gain
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 64 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Maximum_Auto_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* High Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_Percentile_to_Find(DIRECTION dir, int *value, int timeOut = -1);

     /* Low Percentile to Find
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_Percentile_to_Find(DIRECTION dir, int *value, int timeOut = -1);

     /* High grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value, int timeOut = -1);

     /* Low grey level to match found percentile to
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be in range 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_grey_level_to_match_found_percentile_to(DIRECTION dir, int *value, int timeOut = -1);


     /* ----------------------------------------------------------------------------------------*/

     /* AGO Region of Interest Messages <AR> */

     /* Region of Interest Centre X Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Centre_X_Position(DIRECTION dir, int *value, int timeOut = -1);

     /* Region of Interest Centre Y Position n/256th From Image Centre
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -128 to 127
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Centre_Y_Position(DIRECTION dir, int *value, int timeOut = -1);

     /* Region of Interest Size X Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Size_X_Dimension(DIRECTION dir, int *value, int timeOut = -1);

     /* Region of Interest Size Y Dimension n/256th Image Width
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range 1 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Region_of_Interest_Size_Y_Dimension(DIRECTION dir, int *value, int timeOut = -1);

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
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Perform_Calibration(DIRECTION dir, int *value, int timeOut = -1);

     /* Automatic Calibration on Cooldown (3 point)
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Automatic_Calibration(DIRECTION dir, int *value, int timeOut = -1);

     /* Stare Time (Waveband 1) LSB = 1 us
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Stare_Time(DIRECTION dir, int *value, int timeOut = -1);

     /* Integration Capacitors (Waveband 1)
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Integration_Capacitors(DIRECTION dir, int *value, int timeOut = -1);

     /* Select Calibration Table
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Select_Calibration_Table(DIRECTION dir, int *value, int timeOut = -1);

     /* Enable Non-Uniformity Correction
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Enable_Non_Uniformity_Correction(DIRECTION dir, int *value, int timeOut = -1);

     /* Reject Last Calibration
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Reject_Last_Calibration(DIRECTION dir, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Dead Pixel Replacement Messages <CD> */

     /* Dead Pixel Replacement
     *
     * @param dir direction can be SET, READ or ENG
     * @param/return value pointer can be:
     *              * 0 - Disabled
     *              * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Dead_Pixel_Replacement(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Calibration Configuration Messages <CC> */

     /* Number of Samples 2^n Samples per Calibration Point
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 7
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Number_of_Samples(DIRECTION dir, int *value, int timeOut = -1);

     /* Low Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Low_Target_Well_Fill(DIRECTION dir, int *value, int timeOut = -1);

     /* Mid Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mid_Target_Well_Fill(DIRECTION dir, int *value, int timeOut = -1);

     /* High Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int High_Target_Well_Fill(DIRECTION dir, int *value, int timeOut = -1);

     /* Optimisation Method
     *
     * @param dir direction can be SET or READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * D - Optimisation Disabled
     *              * F - Frame Rate Limited
     *              * S - Stare Time Limited
     *              * W - Well Fills Optimised
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Method(DIRECTION dir, char *value, int timeOut = -1);

     /* Optimisation Target Well Fill LSB = 1%
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 10 to 90
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Target_Well_Fill(DIRECTION dir, int *value, int timeOut = -1);

     /* Optimisation Maximum Stare Time LSB = 1 us
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimisation_Maximum_Stare_Time(DIRECTION dir, int *value, int timeOut = -1);

     /* Store Calibration Table to NVRAM
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Store_Calibration_Table_to_NVRAM(DIRECTION dir, int *value, int timeOut = -1);

     /* Restore Calibration Table from NVRAM
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be 0 to 3
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Restore_Calibration_Table_to_NVRAM(DIRECTION dir, int *value, int timeOut = -1);

     /* Store / Restore NVRAM Progress
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be:
     *              * N - No Op (Idle)
     *              * S - Store In Progress
     *              * R - Restore In Progress
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Store_or_Restore_NVRAM_Progress(DIRECTION dir, char *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Detector Message Group <D> */

     /* Detector Array Type
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * 0 - Unknown
     *              * 1 - Hawk (640 x 512 @ 16um)
     *              * 2 - Falcon (1280 x 720 @ 12um)
     *              * 3 - Swallow
     *              * 4 - Osprey (384 x 288 @ 20um)
     *              * 5 - Merlin (1024 x 768 @ 16um)
     *              * 6 - Harrier (640 x 512 @ 24um)
     *              * 7 - Condor II (DWB 640 x 512 @ 24um)
     *              * 8 - Condor III (DWB 640 x 512 @ 20um)
     *              * 9 - Condor IV (DWB 640 x 512 @ 20um)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Detector_Array_Type(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Test Pattern Messages <DP> */
     /* Test Pattern Enable
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * 0 - Disable
     *              * 1 - Enable
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Test_Pattern_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Test Pattern Type
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * F - Fixed Test Pattern
     *              * M - Moving Test Pattern
     *              * 1 - Proxy Test Pattern 1
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Test_Pattern_Type(DIRECTION dir, char *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Readout Control Messages <DR> */

     /* Readout Direction
     *
     * @param dir direction can be READ and SET.ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * N - Normal
     *              * H - Reversed Horizontally
     *              * V - Reversed Vertically
     *              * B - Reversed Both
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Readout_Direction(DIRECTION dir, char *value, int timeOut = -1);

     /* Readout Mode
     *
     * @param dir direction can be READ and SET.ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * B - ITR (Blinking)
     *              * R - IWR (Rolling)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Readout_Mode(DIRECTION dir, char *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Triggering Messages <DT> */

     /* Trigger Method
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * D - Display Locked
     *              * F - Free Running
     *              * E - External Trigger (Edge)
     *              * L - External Trigger (Level)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Trigger_Method(DIRECTION dir, char *value, int timeOut = -1);

     /* Frame Rate (display locked only) Number of Display Frames (or Fields) per Stare
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 4
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Frame_Rate(DIRECTION dir, int *value, int timeOut = -1);

     /* Frame Period (free running only) LSB = 1 us
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Frame_Period(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Referencer <ER> */
     /* Use Peltier During Calibration
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *              * 0 - Normal Calibration
     *              * 1 - Engineering Calibration (external reference)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Use_Peltier_During_Calibration(DIRECTION dir, int *value, int timeOut = -1);

     /* TEC Stable (engineering calibration)
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int TEC_Stable(DIRECTION dir, int timeOut = -1);

     /* Move Paddle
     *
     * @param dir direction can be SET and ENG. READ mode isn't acceptable
     * @param/return value pointer can be:
     *                  * I - In
     *                  * O - Out
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Move_Paddle(DIRECTION dir, char *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Spatial Filter Messages <FS> */

     /* Spatial Filter Sharpening Level
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 00 = Off, 31 = Maximum Sharpening
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Spatial_Filter_Sharpening_Level(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Image Stabilisation Messages <FI> */

     /* Image Stabilisation Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Stabilisation Image Trim (each side)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 1 to 64
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Image_Trim(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Stabilisation Damping
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 0 to 63
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Damping(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Stabilisation Threshold
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be 0 to 15
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Threshold(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Stabilisation Current Position X
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be -99 to +99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Current_Position_X(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Stabilisation Current Position Y
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be -99 to +99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Stabilisation_Current_Position_Y(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Turbulence Mitigation Messages <FT> */

     /* Turbulence Mitigation Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Turbulence_Mitigation_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Turbulence Mitigation Level
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 00 = Dynamic (Min), 16 = Static (Max),
     *                              17 = Automatic (not yet implemented)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Turbulence_Mitigation_Level(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Graphics Overlay Mode Messages <GO> */

     /* DRE Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int DRE_Overlay_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* DRE Overlay Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int DRE_Overlay_Colour(DIRECTION dir, int *value, int timeOut = -1);

     /* Autofocus Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Autofocus_Overlay_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Autofocus Overlay Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Autofocus_Overlay_Colour(DIRECTION dir, int *value, int timeOut = -1);

     /* Tracker Overlay Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Tracker_Overlay_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : DRE Mode <GPA> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_DRE_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_DRE_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_DRE_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_DRE_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Camera Temperature <GPC> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Camera_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Camera_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Camera_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Camera_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Detector Temperature <GPD> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Detector_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Detector_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Detector_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Detector_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Electronic Zoom <GPE> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Electronic_Zoom(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Electronic_Zoom(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Electronic_Zoom(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Electronic_Zoom(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Focus <GPF> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Focus(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Focus(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Focus(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Focus(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : DRE Gain <GPG> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_DRE_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_DRE_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_DRE_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_DRE_Gain(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Mode <GPM> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : DRE Offset <GPO> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_DRE_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_DRE_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_DRE_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_DRE_Offset(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Pitch (Elevation) Indicator <GPP> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Pitch_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Pitch_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Pitch_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Pitch_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Value (LSB = 0.1)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -900 to 900
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Value_Pitch_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Status <GPS> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Yaw (Azimuth) Indicator <GPY> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Yaw_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Yaw_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Yaw_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Yaw_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Value (LSB = 0.1)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 3600
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Value_Yaw_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Pre-defined Text : Optical Field of View (EFL) <GPZ> */

     /* Text Item Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Enable_Optical_Field_of_View(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_column_Optical_Field_of_View(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_start_row_Optical_Field_of_View(DIRECTION dir, int *value, int timeOut = -1);

     /* Text Item Colour
     *      (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Text_Item_Colour_Optical_Field_of_View(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Mimic : DRE (Gain / Offset) <GMD> */

     /* DRE Mimic Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int DRE_Mimic_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_start_column_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_start_row_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Colour (Foreground)
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Foreground_Colour_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Background Colour
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Background_Colour_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Width_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Height_DRE(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Mimic : Target Size */

     /* Target Size Mimic Enable
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Target_Size_Mimic_Enable(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic start column
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_start_column_Target_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic start row
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_start_row_Target_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Colour (Foreground)
     *          (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Foreground_Colour_Target_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Width_Target_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Mimic Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2047
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Mimic_Height_Target_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Boresight Marker <GB> */

     /* Boresight Marker Type
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Cross
     *                  * 2 - Cross (Split)
     *                  * 3 - Box
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Type(DIRECTION dir, int *value, int timeOut = -1);

     /* Boresight Marker Column (relative to array centre)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Column(DIRECTION dir, int *value, int timeOut = -1);

     /* Boresight Marker Row (relative to array centre)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -512 to 512
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Row(DIRECTION dir, int *value, int timeOut = -1);

     /* Boresight Marker Colour
                (b8:b6) = Red, (b5:b3) = Green, (b2:b0) = Blue
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 511
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Colour(DIRECTION dir, int *value, int timeOut = -1);

     /* Boresight Marker Width (columns)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2043
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Width(DIRECTION dir, int *value, int timeOut = -1);

     /* Boresight Marker Height (rows)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 2043
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Boresight_Marker_Height(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Imager Configuration Message Group <I> */

     /* Imager Identity (part 1)
     *              ‘X’ part of identity : AP5???XXXX-YY-ZZ
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Imager_Identity_Part_1(DIRECTION dir, int *value, int timeOut = -1);

     /* Imager Identity (part 2)
     *              ‘Y’ and ‘Z’ parts of identity : AP5???XXXX-YY-ZZ
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Imager_Identity_Part_2(DIRECTION dir, int *value, int timeOut = -1);

     /* Firmware Version (processor module)
     *              +ve values = Formal Builds
     *              -ve values = Engineering Builds
     *
     * @param dir direction can be READ. ENG and SET mode aren't acceptable
     * @param/return value pointer can be -9999 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Firmware_Version(DIRECTION dir, int *value, int timeOut = -1);

     /* Imager Serial Number
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Imager_Serial_Number(DIRECTION dir, int *value, int timeOut = -1);

     /* Processing Board Serial Number
     *
     * @param dir direction can be READ and ENG. SET mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Processing_Board_Serial_Number(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Board Serial Number
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Board_Serial_Number(DIRECTION dir, int *value, int timeOut = -1);

     /* Turbulence Mitigation Available
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * 0 - No
     *                  * 1 - Yes
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Turbulence_Mitigation_Available(DIRECTION dir, int *value, int timeOut = -1);

     /* Detector Waveband 1
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * M - Midwave (3-5um)
     *                  * L - Longwave (8-12um)
     *                  * B - BIL
     *                  * 3 - 3D BIL
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Detector_Waveband_1(DIRECTION dir, char *value, int timeOut = -1);

     /* Default Configuration
     *
     * @param dir direction can be ENG. READ and SET modes aren't acceptable
     * @param/return value pointer can be:
     *                  * S - Store to FLASH
     *                  * R - Reload from FLASH
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Default_Configuration(DIRECTION dir, char *value);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Fitted to Imager Messages <IL> */

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
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Type_Fitted(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens EFL Widest FoV     LSB = 1 mm
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_EFL_Widest_FoV(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens EFL Narrowest FoV     LSB = 1 mm
     *
     * @param dir direction can be READ. ENG and SET modes aren't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_EFL_Narrowest_FoV(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Zoom Messages <LZ> */

     /* Change Zoom (Relative)
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * N - Zoom towards Narrow (at Zoom Speed below)
     *              * W - Zoom towards Wide (at Zoom Speed below)
     *              * S - Stop
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_Zoom(DIRECTION dir, char *value, int timeOut = -1);

     /* Zoom Position EFL in mm (values outside range for lens restricted)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Zoom_Position_EFL(DIRECTION dir, int *value, int timeOut = -1);

     /* Zoom Speed Approximate rate of EFL change in mm/sec
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Zoom_Speed(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Focus Messages <LF> */

     /* Change Focus (Relative)
     *
     * @param dir direction can be SET. READ and ENG mode aren't acceptable
     * @param/return value pointer can be:
     *              * F - Focus towards Far/Infinity (at Focus Speed below)
     *              * N - Focus towards Near (at Focus Speed below)
     *              * S - Stop
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Change_Focus(DIRECTION dir, char *value, int timeOut = -1);

     /* Focus Position Focus distance in 0.1m (positive values) or Encoder steps beyond infinity position (negative values)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 262143
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Position(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus Speed Approximate rate of focus change as %/sec
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Speed(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus ramping beyond infinity (change relative)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_ramping_beyond_infinity(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Autofocus Messages <LA> */

     /* Optimise Focus Distance (single sweep)
     *                  value 0 can be SET, check protocol
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Idle
     *                  * 1 - Optimise Initiate (Read Running)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Optimise_Focus_Distance(DIRECTION dir, int *value, int timeOut = -1);

     /* Autofocus Nearest Position (Max Encoder Posn)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 5130
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Autofocus_Nearest_Position(DIRECTION dir, int *value, int timeOut = -1);

     /* Autofocus Furthest Position (Max Encoder Posn)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be -2000 to 5130
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Autofocus_Furthest_Position(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Status Messages <LS> */

     /* Elapsed Time Indicator (ETI) Reading Lens Controller Operating Hours
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Elapsed_Time_Indicator(DIRECTION dir, int *value, int timeOut = -1);

     /* Number of Power Cycles
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Number_of_Power_Cycles(DIRECTION dir, int *value, int timeOut = -1);

     /* Humidity Sensor Reading % RH (relative humidity)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Humidity_Sensor(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens BITE
     *              D0 : 0 = Ok, 1= Initialising (warning only)
     *              D1 : 0 = Ok, 1 = Communications Error
     *              D2 : 0 = Ok, 1 = NVRAM Datum Error
     *              D3 : 0 = Ok, 1 = NVRAM Calibration Temp Error
     *              D4 : 0 = Ok, 1 = Zoom Position Sensor Error
     *              D5 : 0 = Ok, 1 = Focus Position Sensor Error
     *              D6 : 0 = Ok, 1 = Focus Optocouple Error
     *              D7 : 0 = Ok, 1 = Exercise Function Timeout
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_BITE(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Datums Messages <LD> */

     /* Zoom Narrow Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Zoom_Narrow_Hard_Stop_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Zoom Wide Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Zoom_Wide_Hard_Stop_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus Far (Infinity) Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Far_Hard_Stop_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus Near (Close) Hard Stop Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Near_Hard_Stop_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus Optocouple Sensor Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Optocouple_Sensor_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Zoom Optical Reference Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 4095
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Zoom_Optical_Reference_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* Focus (Atherm) Optical Reference Datum
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Focus_Optical_Reference_Datum(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Temperature Messages <LT> */

     /* Lens Local Board Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -50 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Local_Board_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 1 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_1(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 2 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_2(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 3 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_3(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 4 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_4(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 5 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_5(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 6 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_6(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 7 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_7(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Temperature Sensor 8 LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Temperature_Sensor_8(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Calibration Temperature Messages <LC> */

     /* Lens Calibration Temperature 1
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_1(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 2
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_2(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 3
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_3(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 4
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_4(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 5
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_5(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 6
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_6(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 7
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_7(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Calibration Temperature 8
     *              LSB of offset is 199/16384 C (~0.012°C)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Calibration_Temperature_8(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Lens Exercise Mechanism Messages <LE> */

     /* Exercise Lens Period Time (in mins) between operations (0 = never)
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Exercise_Lens_Period(DIRECTION dir, int *value, int timeOut = -1);

     /* Lens Exercise Next Time (in mins) until next exercise operation
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Lens_Exercise_Next(DIRECTION dir, int *value, int timeOut = -1);

     /* Perform Exercise Mechanism Function
     *
     * @param dir direction can be SET.READ and ENG mode aren't acceptable
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Perform_Exercise_Mechanism_Function(DIRECTION dir, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Camera Mode <SM> */

     /* Camera Mode
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * C - Cooldown (read only)
     *              * O - Operate
     *              * E - Engineering
     *              * N - Calibration (NUC) (read only)
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Camera_Mode(DIRECTION dir, char *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Imager Usage History Messages <SU> */

     /* Elapsed Time Indicator (ETI) Reading
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Elapsed_Time_Indicator_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* Number of Power Cycles
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 9999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Number_of_Power_Cycles_Status(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Temperature Messages <ST> */

     /* Local Board Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Local_Board_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Detector Array Temperature LSB = 0.01 K
     *
     * @param dir direction can be READ.SET and ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Detector_Array_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* Referencer Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Referencer_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* FPGA Core Temperature LSB = 1C
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be -99 to 99
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int FPGA_Core_Temperature(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Supply Voltage Messages <SS> */

     /* 12V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_12V(DIRECTION dir, int *value, int timeOut = -1);

     /* 3.3V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_3_3V(DIRECTION dir, int *value, int timeOut = -1);

     /* 2.5V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_2_5V(DIRECTION dir, int *value, int timeOut = -1);

     /* 1.5V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_1_5V(DIRECTION dir, int *value, int timeOut = -1);

     /* 1.2V Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_1_2V(DIRECTION dir, int *value, int timeOut = -1);

     /* VCCINT (1.0V) Supply Monitor LSB = 0.01V
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_1_0V(DIRECTION dir, int *value, int timeOut = -1);

     /* VCCAUX (1.8V) Supply Monitor
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 1999
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Supply_Monitor_1_8V(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Fault Log Messages <SF> */

     /* Active Fault Log Session Number
     *              Fault log wraps back to 0 (i.e. contains last 1023 sessions).
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 1 to 1023
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */

     int Active_Fault_Log_Session_Number(DIRECTION dir, int *value, int timeOut = -1);

     /* Read Session Pointer
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 1 to 1023
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Session_Pointer(DIRECTION dir, int *value, int timeOut = -1);

     /* Read Word Pointer
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 31
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Word_Pointer(DIRECTION dir, int *value, int timeOut = -1);

     /* Read Fault Log Word
     *              (returns fault log word specified by Session Pointer and Word Pointer above)
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Fault_Log_Word(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Detector Messages <SD> */

     /* Read Detector Frame Period LSB = 1 us
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Detector_Frame_Period(DIRECTION dir, int *value, int timeOut = -1);

     /* Read Image Mean
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Image_Mean(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Video Messages <SV> */

     /* Read Video Frame/Field Period
     *
     * @param dir direction can be READ. SET or ENG mode aren't acceptable
     * @param/return value pointer can be 0 to 65535
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Read_Video_Frame(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Tracker Message Group <T> */

     /* Tracker Mode
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * I - Idle
     *              * A - Acquire
     *              * T - Track
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Tracker_Mode(DIRECTION dir, char *value, int timeOut = -1);

     /* Tracker Type
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be:
     *              * 0 - Automatic (not yet implemented)
     *              * 1 - Centroid
     *              * 2 - Correlator
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Tracker_Type(DIRECTION dir, int *value, int timeOut = -1);

     /* Centroid Target Window Size
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Centroid_Target_Window_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Correlator Target Window Size*
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 64
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Correlator_Target_Window_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Correlator Scan Area Size (excluding target size)*
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 4 to 64
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Correlator_Scan_Area_Size(DIRECTION dir, int *value, int timeOut = -1);

     /* Correlator Auto-acquire Rate (1 in N frames)
     *              0 = Auto-acquire off
     *
     * @param dir direction can be SET and READ. ENG mode isn't acceptable
     * @param/return value pointer can be 0 to 255
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Correlator_Auto_acquire_Rate(DIRECTION dir, int *value, int timeOut = -1);

     /* Target Position (relative to centre of display)
     *              LSB = 15.3 urad
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Target_Position_X(DIRECTION dir, int *value, int timeOut = -1);

     /* Target Position (relative to centre of display)
     *              LSB = 15.3 urad
     *
     * @param dir direction can be SET and READ.ENG mode isn't acceptable
     * @param/return value pointer can be in range -32768 to 32767
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Target_Position_Y(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* User Interface Message Group <U> */

     /* Configure RS422 Communications Baud Rate
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - 9600 baud
     *                  * 1 - 19200 baud
     *                  * 2 - 38400 baud
     *                  * 3 - 57600 baud
     *                  * 4 - 115200 baud
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Configure_Baud_Rate(DIRECTION dir, int *value, int timeOut = -1);

     /* Configure RS422 Communications Parity / Stop Bits
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - 1 Stop Bit, No Parity
     *                  * 1 - 2 Stop Bits, No Parity
     *                  * 2 - 1 Stop Bit, Even Parity
     *                  * 3 - 2 Stop Bits, Even Parity
     *                  * 4 - 1 Stop Bit, Odd Parity
     *                  * 5 - 2 Stop Bits, Odd Parity
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Configure_Parity_and_Stop_Bits(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Video Message Group <V> */

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
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Display_Mode(DIRECTION dir, int *value, int timeOut = -1);

     /* Image Size
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * C - Centred (best integer scaling)
     *                  * H - Fit Horizontally
     *                  * V - Fit Vertically
     *                  * 1 - 1:1 Detector to Display Mapping
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Image_Size(DIRECTION dir, char *value, int timeOut = -1);

     /* Display Orientation
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Top Left
     *                  * 1 - Top Right
     *                  * 2 - Bottom Left
     *                  * 3 - Bottom Right
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Display_Orientation(DIRECTION dir, int *value, int timeOut = -1);

     /* Freeze Frame
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Freeze_Frame(DIRECTION dir, int *value, int timeOut = -1);

     /* HD-SDI Video Output (can only be enabled in 720p)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int HD_SDI_Video_Output(DIRECTION dir, int *value, int timeOut = -1);

     /* Analogue Video Output
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Analogue_Video_Output(DIRECTION dir, int *value, int timeOut = -1);

     /* Composite Sync on Green (574i, 484i & 720p only)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Composite_Sync_on_Green(DIRECTION dir, int *value, int timeOut = -1);

     /* ONVIF Video Output (can only be enabled in 720p)
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int ONVIF_Video_Output(DIRECTION dir, int *value, int timeOut = -1);

     /* ----------------------------------------------------------------------------------------*/

     /* Electronic Zoom Messages <VZ> */

     /* Electronic Zoom Ratio LSB = 0.01
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be 100 to 800
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Electronic_Zoom_Ratio(DIRECTION dir, int *value, int timeOut = -1);

     /* Electronic Zoom Pan X LSB = 1 column
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Electronic_Zoom_Pan_X(DIRECTION dir, int *value, int timeOut = -1);

     /* Electronic Zoom Pan Y LSB = 1 row
     *
     * @param dir direction can be READ and SET.ENG mode isn't acceptable
     * @param/return value pointer can be -640 to 640
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Electronic_Zoom_Pan_Y(DIRECTION dir, int *value, int timeOut = -1);

     /* Electronic Zoom Type
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Replicated
     *                  * 1 - Bi-linear Interpolated
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Electronic_Zoom_Type(DIRECTION dir, int *value, int timeOut = -1);

     /* Fill Display on Electronic Zoom
     *
     * @param dir direction can be READ,SET or ENG
     * @param/return value pointer can be:
     *                  * 0 - Disabled
     *                  * 1 - Enabled
     * @param timeOut time in msec for timeout UART-read operation. Default is -1, means blocking reading
     *
     * @resuilt is 0 if action is successful, otherwise is faliure
     */
     int Fill_Display_on_Electronic_Zoom(DIRECTION dir, int *value, int timeOut = -1);




};

#endif // CAMERA_CONFIG_H
