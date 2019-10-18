/************************************************************************
** File:
**    mqtt_events.h 
**
** Purpose: 
**  Define MQTT app Event IDs
**
** Notes:
**
**
*************************************************************************/
#ifndef _mqtt_events_h_
#define _mqtt_events_h_


#define MQTT_RESERVED_EID              0
#define MQTT_STARTUP_INF_EID           1 
#define MQTT_COMMAND_ERR_EID           2
#define MQTT_COMMANDNOP_INF_EID        3 
#define MQTT_COMMANDRST_INF_EID        4
#define MQTT_INVALID_MSGID_ERR_EID     5 
#define MQTT_LEN_ERR_EID               6 
#define MQTT_CR_CHILD_TASK_ERR_EID     7
#define MQTT_INIT_ERR_EID              8
#define MQTT_CMD_INF_EID               9

#endif /* _mqtt_events_h_ */

/************************/
/*  End of File Comment */
/************************/
