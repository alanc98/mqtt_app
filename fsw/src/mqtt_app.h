/*******************************************************************************
** File: mqtt_app.h
**
** Purpose:
**   This file is main hdr file for the MQTT application.
**
** Copyright 2018-2019 Alan Cudmore
** Note: This code was not developed at or sponsored by NASA.
**
*******************************************************************************/

#ifndef _mqtt_h_
#define _mqtt_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"
#include "cfe.h"

#include "mqtt_platform_cfg.h"
#include "mqtt_msg.h"
#include "mqtt_tbldefs.h"
#include "mqtt_msgids.h"
#include "mqtt_perfids.h"
#include "mqtt_events.h"
#include "mqtt_version.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>

/***********************************************************************/

#define MQTT_PIPE_DEPTH     32

#define MQTT_QOS0            0
#define MQTT_QOS1            1
#define MQTT_QOS2            2

#define MQTT_UNUSED          0
#define MQTT_TLM_PKT         1
#define MQTT_CMD_PKT         2

#define MQTT_INT8             8 
#define MQTT_UINT8            9 
#define MQTT_UINT16          15
#define MQTT_INT16           16
#define MQTT_UINT32          31
#define MQTT_INT32           32
#define MQTT_FLOAT           33
#define MQTT_DOUBLE          64
#define MQTT_STRING16        116
#define MQTT_STRING32        132
#define MQTT_STRING64        164
#define MQTT_STRING128       200

/*
** Incoming MQTT Messages have 3 potential types
** 1. A single data item with a primitive type 
** 2. A CCSDS packet in JSON format
** 3. A data payload in JSON format ( no CCSDS header info )
**   Note: may not need to distinguish between 2 and 3
*/
#define MQTT_PRIMITIVE       300
#define MQTT_JSON_PACKET     400
#define MQTT_JSON_PAYLOAD    500

/************************************************************************
** Type Definitions
*************************************************************************/
/*
** Local Structure Declarations
*/


/************************************************************************
** Global Data 
*************************************************************************/
extern int32                      MQTT_ChildTaskRunStatus;
extern uint32                     MQTT_ChildTaskId;
extern int32                      MQTT_Mqtt2SbTableIsValid;
extern mqtt_hk_tlm_t              MQTT_HkTelemetryPkt;
extern MQTT_Mqtt2SbTableEntry_t  *MQTT_Mqtt2SbTablePtr;         /* Pointer to the MQTT to SB table */
extern CFE_TBL_Handle_t           MQTT_Mqtt2SbTableHandle;      /* MQTT to SB Table handle         */
extern int32                      MQTT_Mqtt2SbTableIsValid;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (MQTT_AppMain), these
**       functions are not called from any other source module.
*/
void    MQTT_AppMain(void);
void    MQTT_AppInit(void);
void    MQTT_ProcessCommandPacket(void);
void    MQTT_ProcessGroundCommand(void);
void    MQTT_ReportHousekeeping(void);
void    MQTT_ResetCounters(void);
boolean MQTT_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

/*
** Table Functions
*/
int32  MQTT_InitTables(void);
int32  MQTT_ValidateMqtt2SbTable(void* table);

/* 
** Child task function(s)
*/
int32  MQTT_CreateChildTask(void);
void   MQTT_ChildIdleLoop(void);

/*
** MQTT Client functions
** These will probably migrate to the mqtt_lib to serve as the 
** abstraction to the Paho embedded C mqtt lib. 
*/
int32  MQTT_ClientInitialize(char *hostname, int port,
                             char *clientname,
                             char *username, char *password);
int32  MQTT_ClientSubscribe(char *topic, int qos);
void   MQTT_ClientYeild(unsigned int timeout);
void   MQTT_ClientDisconnect(void);

#endif /* _mqtt_h_ */
