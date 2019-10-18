/******************************************************************************/
/** \file  mqtt_tbldefs.h
*  
*   \author Alan Cudmore 
*
*   \brief Define the configuration tables for the MQTT cFS App
*
*   \par Limitations, Assumptions, External Events, and Notes:
*       Each table entry defines: 

*       A Valid Table:
*
*   \par Modification History:
*     - 2018-12-23 | Alan Cudmore | Code Started
*******************************************************************************/
#ifndef _MQTT_TBLDEFS_
#define _MQTT_TBLDEFS_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** Includes
*******************************************************************************/
#include "cfe.h"
#include "mqtt_platform_cfg.h"

/*******************************************************************************
** Macro Definitions
*******************************************************************************/

/** \name Default Table Size */
/** \{ */
#ifndef MQTT_MQTT2SB_MAX_TBL_ENTRIES    
#define MQTT_MQTT2SB_MAX_TBL_ENTRIES      50 
#endif


/*
** Not used yet
*/
#ifndef MQTT_SB2MQTT_MAX_TBL_ENTRIES    
#define MQTT_SB2MQTT_MAX_TBL_ENTRIES      50
#endif
/** \} */

/*******************************************************************************
** Type Definitions
*******************************************************************************/
/** 
**  \brief MQTT Table Entry for SB to MQTT bridge 
*/

/** 
**  \brief MQTT Table Entry for MQTT to SB bridge 
*/
typedef struct
{
      uint32              MsgType;       /* MQTT_UNUSED, MQTT_PRIMITIVE, MQTT_JSON_PACKET, MQTT_JSON_PAYLOAD */
      CFE_SB_MsgId_t      MsgId;         /* Message ID (must be unique)  */
      char                MqttTopic[MQTT_TOPIC_LEN]; /* MQTT Topic */ 
      uint32              PktType;       /* MQTT_TLM_PKT, MQTT_CMD_PKT */
      uint32              DataType;      /* MQTT Message Data Type  */
      uint32              DataLength;    /* MQTT Message Data Length */
} MQTT_Mqtt2SbTableEntry_t;

/*
** not used yet
*/
typedef struct
{
      CFE_SB_MsgId_t      MsgId;      /**< Message ID (must be unique)      */
      CFE_SB_Qos_t        qos;          /**< Quality of Service flag          */
      uint16              MsgLimit;   /**< Max Num. of this Msgs in pipe    */
      uint16              RouteMask;  /**< Bitwize Route Mask               */
      uint32              GroupData;  /**< Group data Mask                  */
      uint16              Flag;       /**< Custom defined flag              */
      uint16              State;      /**< Message ID is enabled = 1        */
} MQTT_Sb2MqttTableEntry_t;


#ifdef __cplusplus
}
#endif

#endif

/*==============================================================================
** End of file mqtt_tbldefs.h
**============================================================================*/
