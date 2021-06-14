/*******************************************************************************
** File:
**   mqtt_msg.h 
**
** Purpose: 
**  Define MQTT App Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _mqtt_msg_h_
#define _mqtt_msg_h_

/*
** MQTT App command codes
*/
#define MQTT_NOOP_CC                 0
#define MQTT_RESET_COUNTERS_CC       1
#define MQTT_MANAGE_TABLE_CC         2


#define MQTT_GENERIC_TLM_DATA_SIZE  128
#define MQTT_GENERIC_CMD_DATA_SIZE  128

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];

} MQTT_NoArgsCmd_t;

/*************************************************************************/
/*
** Type definition (MQTT App housekeeping)
*/
typedef struct 
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              mqtt_command_error_count;
    uint8              mqtt_command_count;
    uint16             mqtt_child_task_counter;

}   mqtt_hk_tlm_t  ;
#define MQTT_HK_TLM_LNGTH   sizeof ( mqtt_hk_tlm_t )

/******************************************************************************/
/* Generic types used for building command and telemetry packets */
/* sizeof cannot be used for the length */  
typedef struct
{
    uint8    TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8    data[MQTT_GENERIC_TLM_DATA_SIZE];
}  MQTT_GENERIC_TLM_PKT_t;

typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];
   uint8    data[MQTT_GENERIC_CMD_DATA_SIZE];
}  MQTT_GENERIC_CMD_PKT_t;
/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    int32              int32_value;
}  MQTT_INT32_TLM_PKT_t;
#define MQTT_INT32_TLM_LNGTH      sizeof(MQTT_INT32_TLM_PKT_t)

/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    float              float_value;
}  MQTT_FLOAT_TLM_PKT_t;
#define MQTT_FLOAT_TLM_LNGTH      sizeof(MQTT_FLOAT_TLM_PKT_t)

/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    double             double_value;
}  MQTT_DOUBLE_TLM_PKT_t;
#define MQTT_DOUBLE_TLM_LNGTH      sizeof(MQTT_DOUBLE_TLM_PKT_t)

/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    char               string32[32];
}  MQTT_STRING32_TLM_PKT_t;
#define MQTT_STRING32_TLM_LNGTH      sizeof(MQTT_STRING32_TLM_PKT_t)

/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    char               string64[64];
}  MQTT_STRING64_TLM_PKT_t;
#define MQTT_STRING64_TLM_LNGTH      sizeof(MQTT_STRING64_TLM_PKT_t)

/******************************************************************************/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    char               string100[100];
}  MQTT_STRING100_TLM_PKT_t;
#define MQTT_STRING100_TLM_LNGTH      sizeof(MQTT_STRING100_TLM_PKT_t)

#endif /* _mqtt_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
