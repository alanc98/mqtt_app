/*******************************************************************************
** File: MQTT_app.c
**
** Purpose:
**   This file contains the source code for the Sample App.
**
** Copyright 2018-2019 Alan Cudmore
** Note: This code was not developed at or sponsored by NASA.
**
*******************************************************************************/

/*
**   Include Files:
*/
#include "mqtt_app.h"

/*
** global data
*/

mqtt_hk_tlm_t              MQTT_HkTelemetryPkt;
CFE_SB_PipeId_t            MQTT_CommandPipe;
CFE_SB_MsgPtr_t            MQTT_MsgPtr;
uint32                     MQTT_ChildTaskId;
int32                      MQTT_ChildTaskRunStatus;

MQTT_Mqtt2SbTableEntry_t  *MQTT_Mqtt2SbTablePtr;         /* Pointer to the MQTT to SB table */
CFE_TBL_Handle_t           MQTT_Mqtt2SbTableHandle;      /* MQTT to SB Table handle         */
int32                      MQTT_Mqtt2SbTableIsValid;

/* Not implemented yet */
MQTT_Sb2MqttTableEntry_t  *MQTT_Sb2MqttTablePtr;         /* Pointer to the SB to MQTT table */
CFE_TBL_Handle_t           MQTT_Sb2MqttTableHandle;      /* SB to MQTT Table handle         */
uint32                     MQTT_Sb2MqttTableIsValid;     /* Status of the Table Load */


static CFE_EVS_BinFilter_t  MQTT_EventFilters[] =
       {  /* Event ID    mask */
          {MQTT_STARTUP_INF_EID,       0x0000},
          {MQTT_COMMAND_ERR_EID,       0x0000},
          {MQTT_COMMANDNOP_INF_EID,    0x0000},
          {MQTT_COMMANDRST_INF_EID,    0x0000},
          {MQTT_INVALID_MSGID_ERR_EID, 0x0000},
          {MQTT_LEN_ERR_EID,           0x0000},
          {MQTT_CR_CHILD_TASK_ERR_EID, 0x0000}
       };

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT_AppMain() -- Application entry point and main process loop          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void MQTT_AppMain( void )
{
    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(MQTT_PERF_ID);

    MQTT_AppInit();

    /*
    ** App Main Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(MQTT_PERF_ID);

        status = CFE_SB_RcvMsg(&MQTT_MsgPtr, MQTT_CommandPipe, 1000); /* Should be pend */
        
        CFE_ES_PerfLogEntry(MQTT_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            MQTT_ProcessCommandPacket();
        }

    }

    CFE_ES_ExitApp(RunStatus);

} /* End of MQTT_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* MQTT_AppInit() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void MQTT_AppInit(void)
{
    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp() ;

    /*
    ** Register the events
    */ 
    CFE_EVS_Register(MQTT_EventFilters,
                     sizeof(MQTT_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    CFE_SB_CreatePipe(&MQTT_CommandPipe, MQTT_PIPE_DEPTH,"MQTT_CMD_PIPE");
    CFE_SB_Subscribe(MQTT_CMD_MID, MQTT_CommandPipe);
    CFE_SB_Subscribe(MQTT_SEND_HK_MID, MQTT_CommandPipe);

    MQTT_ResetCounters();

    CFE_SB_InitMsg(&MQTT_HkTelemetryPkt,
                   MQTT_HK_TLM_MID,
                   MQTT_HK_TLM_LNGTH, TRUE);

    /*
    ** Init tables
    */
    if (MQTT_InitTables() != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("MQTT - Failed to init tables.\n");
    }

    /*
    ** Start Child task 
    */
    if (MQTT_CreateChildTask() != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("MQTT - Failed to Create the MQTT Child Task.\n");
    }

    CFE_EVS_SendEvent (MQTT_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "MQTT App Initialized. Version %d.%d.%d.%d",
                MQTT_MAJOR_VERSION,
                MQTT_MINOR_VERSION, 
                MQTT_REVISION, 
                MQTT_MISSION_REV);
				
} /* End of MQTT_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  MQTT_ProcessCommandPacket                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the MQTT      */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void MQTT_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t  MsgId;

    MsgId = CFE_SB_GetMsgId(MQTT_MsgPtr);

    switch (MsgId)
    {
        case MQTT_CMD_MID:
            MQTT_ProcessGroundCommand();
            break;

        case MQTT_SEND_HK_MID:
            MQTT_ReportHousekeeping();
            break;

        default:
            MQTT_HkTelemetryPkt.mqtt_command_error_count++;
            CFE_EVS_SendEvent(MQTT_COMMAND_ERR_EID,CFE_EVS_ERROR,
			"MQTT: invalid command packet,MID = 0x%x", MsgId);
            break;
    }

    return;

} /* End MQTT_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* MQTT_ProcessGroundCommand() -- MQTT ground commands                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void MQTT_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(MQTT_MsgPtr);

    /* Process "known" MQTT app ground commands */
    switch (CommandCode)
    {
        case MQTT_NOOP_CC:
            MQTT_HkTelemetryPkt.mqtt_command_count++;
            CFE_EVS_SendEvent(MQTT_COMMANDNOP_INF_EID,CFE_EVS_INFORMATION,
			"MQTT: NOOP command");
            break;

        case MQTT_RESET_COUNTERS_CC:
            MQTT_ResetCounters();
            break;

        /* default case already found during FC vs length test */
        default:
            break;
    }
    return;

} /* End of MQTT_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  MQTT_ReportHousekeeping                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void MQTT_ReportHousekeeping(void)
{
    OS_printf("MQTT -- HK - child task counter = %d\n", MQTT_HkTelemetryPkt.mqtt_child_task_counter);
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &MQTT_HkTelemetryPkt);
    return;

} /* End of MQTT_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  MQTT_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void MQTT_ResetCounters(void)
{
    /* Status of commands processed by the MQTT App */
    MQTT_HkTelemetryPkt.mqtt_command_count       = 0;
    MQTT_HkTelemetryPkt.mqtt_command_error_count = 0;

    CFE_EVS_SendEvent(MQTT_COMMANDRST_INF_EID, CFE_EVS_INFORMATION,
		"MQTT: RESET command");
    return;

} /* End of MQTT_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* MQTT_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
boolean MQTT_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{     
    boolean result = TRUE;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(MQTT_LEN_ERR_EID, CFE_EVS_ERROR,
           "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
              MessageID, CommandCode, ActualLength, ExpectedLength);
        result = FALSE;
        MQTT_HkTelemetryPkt.mqtt_command_error_count++;
    }

    return(result);

} /* End of MQTT_VerifyCmdLength() */

