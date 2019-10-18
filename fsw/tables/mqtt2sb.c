/*************************************************************************
** File:
**   $Id: mqtt2sb_table.c $
**
** Copyright 2018-2019 - Alan Cudmore
**
** Purpose: 
**   MQTT to Software Bus routing table 
**
** Notes:
** 
** 
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "mqtt_app.h"
#include "cfe_tbl_filedef.h"

/*************************************************************************
** Exported Data
*************************************************************************/
/*
** Table file header
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef __attribute__((__used__)) =
{
    "MQTT_Mqtt2SbTable", MQTT_APP_NAME "." MQTT_MQTT2SB_TABLENAME,
    "MQTT MQTT to SB table", "mqtt2sb.tbl",
    (sizeof(MQTT_Mqtt2SbTableEntry_t) * MQTT_MQTT2SB_MAX_TBL_ENTRIES)
};

/*
** This is the MQTT to Software Bus table (mqtt2sb) 
** 
** Each table entry has the following:
**  Type: MQTT_UNUSED, MQTT_TLM_PKT, MQTT_CMD_PACKET
**  Message ID:
**  Data Type:
**  Data Length: (may not be needed)
*/
MQTT_Mqtt2SbTableEntry_t MQTT_Mqtt2SbTable[MQTT_MQTT2SB_MAX_TBL_ENTRIES] =
{
    /*
    ** RPI-0 with Pimoroni Enviro-phat 
    */
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_TEMP_TLM_MID,
        .MqttTopic         = "rpi0-1/envirophat/temperature",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_LIGHT_TLM_MID,
        .MqttTopic          = "rpi0-1/envirophat/light",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_RED_TLM_MID,
        .MqttTopic          = "rpi0-1/envirophat/red",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_GREEN_TLM_MID,
        .MqttTopic          = "rpi0-1/envirophat/green",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_BLUE_TLM_MID,
        .MqttTopic          = "rpi0-1/envirophat/blue",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ENVIROPHAT_HEADING_TLM_MID,
        .MqttTopic          = "rpi0-1/envirophat/heading",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_DOUBLE,
        .DataLength        = 8
    },

    /*
    ** RPI-3 with Sense Hat 
    */

    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_TEMP_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/temperature",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_HUMIDITY_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/humidity",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_PRESSURE_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/pressure",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_PITCH_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/orientation/pitch",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_ROLL_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/orientation/roll",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SENSEHAT_YAW_TLM_MID,
        .MqttTopic          = "rpi3-1/sensehat/orientation/yaw",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },

    /*
    ** ESP8266 Arduino device with BNO055 IMU 
    */

    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ESP8266_BNO055_TEMP_TLM_MID,
        .MqttTopic          = "esp8266/bno55/temp",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ESP8266_BNO055_PITCH_TLM_MID,
        .MqttTopic          = "esp8266/bno55/orientation/x",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ESP8266_BNO055_ROLL_TLM_MID,
        .MqttTopic          = "esp8266/bno55/orientation/y",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_ESP8266_BNO055_YAW_TLM_MID,
        .MqttTopic          = "esp8266/bno55/orientation/z",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    /* 
    ** Miscellaneous MQTT messages 
    */
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_HELLOWORLD_TLM_MID,
        .MqttTopic          = "rpi0-1/helloworld/message",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_STRING32,
        .DataLength        = 32 
    },

    /* ------------------ Unused ----------------------- */

    {   
        .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   
        .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   
        .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    /* 20 */

    {   
        .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    /* 30 */

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    /* 40 */

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    }
}; 

/************************/
/*  End of File Comment */
/************************/
