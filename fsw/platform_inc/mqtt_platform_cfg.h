/*=======================================================================================
** File Name:  mqtt_platform_cfg.h
**
** Title:  Platform Configuration Header File for MQTT Application
**
** $Author:    Alan Cudmore
** $Revision: 1.1 $
** $Date:      2018-12-22
**
** Purpose:  This header file contains declartions and definitions of all MQTT's 
**           platform-specific configurations.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-12-22 | Alan Cudmore | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _MQTT_PLATFORM_CFG_H_
#define _MQTT_PLATFORM_CFG_H_

#ifndef MQTT_APP_NAME
#define MQTT_APP_NAME     "MQTT"
#endif

/*
** mqtt Platform Configuration Parameter Definitions
*/
#define MQTT_SCH_PIPE_DEPTH  2
#define MQTT_CMD_PIPE_DEPTH  10
#define MQTT_TLM_PIPE_DEPTH  20

/*
** mqtt topic string length
*/
#define MQTT_TOPIC_LEN       100

/*
** Default MQTT server port 
*/
#define MQTT_DEFAULT_SERVER_PORT          1883

/*
** Default MQTT server address 
*/
#define MQTT_DEFAULT_SERVER_ADDRESS  "localhost"

/*
** Default MQTT client name 
*/
#define MQTT_DEFAULT_CLIENT_NAME  "cFS-MQTT-client"

/*
** Default MQTT server username 
*/
#define MQTT_DEFAULT_SERVER_USERNAME NULL 

/*
** Default MQTT server password 
*/
#define MQTT_DEFAULT_SERVER_PASSWORD NULL 

/*
** Tables
*/
#ifndef MQTT_MQTT2SB_TABLENAME
#define MQTT_MQTT2SB_TABLENAME     "mqtt2sb"
#endif
#ifndef MQTT_MQTT2SB_FILENAME
#define MQTT_MQTT2SB_FILENAME      "/cf/mqtt2sb.tbl"
#endif

/* Not used yet */
#ifndef MQTT_SB2MQTT_TABLENAME
#define MQTT_SB2MQTT_TABLENAME     "sb2mqtt"
#endif
#ifndef MQTT_SB2MQTT_FILENAME
#define MQTT_SB2MQTT_FILENAME      "/cf/sb2mqtt.tbl"
#endif

#ifndef MQTT_CHILD_TASK_NAME
#define MQTT_CHILD_TASK_NAME       "MQTT_CHILD"
#endif

#ifndef MQTT_CHILD_TASK_STACK_SIZE
#define MQTT_CHILD_TASK_STACK_SIZE 32768
#endif

#ifndef MQTT_CHILD_TASK_PRIORITY
#define MQTT_CHILD_TASK_PRIORITY   120 
#endif

#ifndef MQTT_CHILD_TASK_FLAGS
#define MQTT_CHILD_TASK_FLAGS      0
#endif


#endif /* _MQTT_PLATFORM_CFG_H_ */

/*=======================================================================================
** End of file mqtt_platform_cfg.h
**=====================================================================================*/
    
