/*=======================================================================================
** File Name:  mqtt_msgids.h
**
** Title:  Message ID Header File for MQTT Application
**
** $Author:    Alan Cudmore
** $Revision: 1.1 $
** $Date:      2018-07-21
**
** Purpose:  This header file contains declartions and definitions of all MQTT's 
**           Message IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-07-21 | Alan Cudmore | Build #: Code Started
**
**=====================================================================================*/
#ifndef _MQTT_MSGIDS_H_
#define _MQTT_MSGIDS_H_

#define MQTT_CMD_MID            	0x18F0
#define MQTT_SEND_HK_MID        	0x18F1

#define MQTT_HK_TLM_MID		        0x08F0


/* Until I have a better idea, need to define the message IDs of packets that will be sent out */

/*
** EnviroPhat messages
*/
#define MQTT_ENVIROPHAT_LED_CMD_MID          0x1900
#define MQTT_ENVIROPHAT_TEMP_TLM_MID         0x0900
#define MQTT_ENVIROPHAT_LIGHT_TLM_MID        0x0901
#define MQTT_ENVIROPHAT_RED_TLM_MID          0x0902
#define MQTT_ENVIROPHAT_GREEN_TLM_MID        0x0903
#define MQTT_ENVIROPHAT_BLUE_TLM_MID         0x0904
#define MQTT_ENVIROPHAT_HEADING_TLM_MID      0x0905

/*
** Misc hello message
*/
#define MQTT_HELLOWORLD_TLM_MID              0x0906

/*
** Sensehat messages
*/

/* This MID is for a cFS command that publishes
 */
#define MQTT_SENSEHAT_MESSAGE_CMD_MID        0x1910 

/*
** These are for MQTT messages that 
** get published on the SB
*/ 
#define MQTT_SENSEHAT_TEMP_TLM_MID           0x0910
#define MQTT_SENSEHAT_HUMIDITY_TLM_MID       0x0911     
#define MQTT_SENSEHAT_PRESSURE_TLM_MID       0x0912     
#define MQTT_SENSEHAT_PITCH_TLM_MID          0x0913     
#define MQTT_SENSEHAT_ROLL_TLM_MID           0x0914     
#define MQTT_SENSEHAT_YAW_TLM_MID            0x0915     

/*
** ESP8266/BNO055 Messages
*/
#define MQTT_ESP8266_BNO055_TEMP_TLM_MID     0x0A00
#define MQTT_ESP8266_BNO055_PITCH_TLM_MID    0x0A01
#define MQTT_ESP8266_BNO055_ROLL_TLM_MID     0x0A02
#define MQTT_ESP8266_BNO055_YAW_TLM_MID      0x0A03

#endif /* _MQTT_MSGIDS_H_ */

/*=======================================================================================
** End of file mqtt_msgids.h
**=====================================================================================*/
    
