/*=======================================================================================
** File Name:  mqtt_tbl.c
**
** Title:  Table management functions for the MQTT Application
**
** $Author:    Alan Cudmore
** $Date:      2018-12-22
**
** Purpose:  This source file contains all necessary function definitions to run MQTT
**           application.
**
** Functions Defined:
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-12-22 | Alan Cudmore | Build #: Code Started
**
** Copyright 2018-2019 Alan Cudmore
** Note: This code was not developed at or sponsored by NASA.
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include "mqtt_app.h"
#include "cfe_tbl_msg.h"


/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/******************************************************************************/
/**  Initialize MQTT Tables
*******************************************************************************/
int32  MQTT_InitTables(void)
{
    int32  Status = CFE_SUCCESS;
    void  *pTable;

    /* Register the table with cFE Table services. */
    Status = CFE_TBL_Register(&MQTT_Mqtt2SbTableHandle, MQTT_MQTT2SB_TABLENAME,
                               (sizeof(MQTT_Mqtt2SbTableEntry_t) * MQTT_MQTT2SB_MAX_TBL_ENTRIES),
                               CFE_TBL_OPT_DEFAULT, 
                               (CFE_TBL_CallbackFuncPtr_t) MQTT_ValidateMqtt2SbTable);

    if (Status != CFE_SUCCESS)
    {
    	CFE_EVS_SendEvent(MQTT_INIT_ERR_EID, CFE_EVS_ERROR,
    			"CFE_TBL_Register() returned error 0x%08x.  Aborting table init.",
    			Status);

        goto end_of_function;
    }

    /* Load the MQTT 2 SB table file */
    Status = CFE_TBL_Load(MQTT_Mqtt2SbTableHandle, CFE_TBL_SRC_FILE,
                  		   MQTT_MQTT2SB_FILENAME);

    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(MQTT_INIT_ERR_EID, CFE_EVS_ERROR,
                  "CFE_TBL_Load() returned error 0x%08x.  Aborting table init.",
                  Status);

        goto end_of_function;
    }

    /* Manage the MQTT 2 SB table */
    Status = CFE_TBL_Manage(MQTT_Mqtt2SbTableHandle);
    if (Status != CFE_SUCCESS)
    {
    	CFE_EVS_SendEvent(MQTT_INIT_ERR_EID, CFE_EVS_ERROR,
           "CFE_TBL_Manage() returned error 0x%08x.  Aborting table init.",
           Status);

        goto end_of_function;
    }

    /* Make sure the MQTT 2 SB Table is accessible */
    Status = CFE_TBL_GetAddress (&pTable, MQTT_Mqtt2SbTableHandle);
    
    /* Status should be CFE_TBL_INFO_UPDATED because we loaded it above */
    if (Status != CFE_TBL_INFO_UPDATED)
    {
    	CFE_EVS_SendEvent(MQTT_INIT_ERR_EID, CFE_EVS_ERROR,
    			"CFE_TBL_GetAddress() returned error 0x%08x. "
                "Aborting table init.",
    			Status);

    	goto end_of_function;
    }

    /* Store the pointer */
    MQTT_Mqtt2SbTablePtr = (MQTT_Mqtt2SbTableEntry_t *) pTable;

    /* Register to receive TBL manage request commands for table updates. */
    Status = CFE_TBL_NotifyByMessage(MQTT_Mqtt2SbTableHandle, 
                                      MQTT_CMD_MID,
                                      MQTT_MANAGE_TABLE_CC, 0);
    if (Status != CFE_SUCCESS)
    {
    	CFE_EVS_SendEvent(MQTT_INIT_ERR_EID, CFE_EVS_ERROR,
    			"CFE_TBL_NotifyByMessage() returned error 0x%08x. "
                "Aborting table init.", Status);
    }
   
end_of_function:
    return Status;
}

/******************************************************************************/
/** \brief Validate MQTT 2 SB Table Load
*******************************************************************************/
int32 MQTT_ValidateMqtt2SbTable(void* table)
{
    int32 Status = CFE_SUCCESS;
    int32 ii;

    MQTT_Mqtt2SbTableEntry_t * pTable = (MQTT_Mqtt2SbTableEntry_t *) table;


    /* TODO: Need to actually validate the table */


    /* Loop over all entries, looking for gaps and duplicate MID */
    for (ii = 0; ii < MQTT_MQTT2SB_MAX_TBL_ENTRIES; ii++)
    {
       if (pTable[ii].MsgType == MQTT_UNUSED)
       {
          OS_printf("Table Entry %d, UNUSED Entry\n", ii); 
       }
       else if (pTable[ii].MsgType == MQTT_PRIMITIVE)
       { 
          OS_printf("Table Entry %d, TLM_PRIMITIVE Entry\n", ii); 
       }
       else if (pTable[ii].MsgType == MQTT_JSON_PACKET)
       { 
          OS_printf("Table Entry %d, TLM_JSON_PACKET Entry\n", ii); 
       }
       else if (pTable[ii].MsgType == MQTT_JSON_PAYLOAD)
       { 
          OS_printf("Table Entry %d, TLM_JSON_PAYLOAD Entry\n", ii); 
       }
       else
       {
          OS_printf("Table Entry %d, Unknown\n", ii); 
       }
    }
    Status = CFE_SUCCESS;
    MQTT_Mqtt2SbTableIsValid = TRUE;

    return Status;
}

/******************************************************************************/
/** \brief Manage the Table - Hook for TBL Services (MQTT_MANAGE_TABLE_CC)
*******************************************************************************/
void MQTT_ManageTableCmd(CFE_SB_MsgPtr_t pCmdMsg)
{
#if 0
    int32 Status = CFE_SUCCESS;
#endif

    if (MQTT_VerifyCmdLength(pCmdMsg, sizeof(CFE_TBL_NotifyCmd_t)))
    {
        MQTT_HkTelemetryPkt.mqtt_command_count++;
        CFE_EVS_SendEvent(MQTT_CMD_INF_EID, CFE_EVS_INFORMATION,
                          "MQTT - Recvd Manage Table Command (%d)", MQTT_MANAGE_TABLE_CC);

#if 0
        /* Temporarily save the previous table */
        memcpy((void *) &oldTable, (void *) g_TO_AppData.pConfigTable, 
               sizeof(TO_ConfigTable_t));

        /* Release the table pointer so that CFE can update it. */
        Status = CFE_TBL_ReleaseAddress(g_TO_AppData.tableHandle); 
        if (Status != CFE_SUCCESS)
        {
            g_TO_AppData.HkTlm.usCmdErrCnt++;
            g_TO_AppData.HkTlm.usTblErrCnt++;
            CFE_EVS_SendEvent(TO_TBL_ERR_EID, CFE_EVS_ERROR,
               "CFE_TBL_ReleaseAddress() returned error 0x%08x. "
               "TO_ManageTable failed.",
               Status);
            goto end_of_command;
        }

        /* This is where the table gets updated. */
        Status = CFE_TBL_Manage(g_TO_AppData.tableHandle);
        if (Status != CFE_SUCCESS && Status != CFE_TBL_INFO_UPDATED)
        {
            g_TO_AppData.HkTlm.usCmdErrCnt++;
            g_TO_AppData.HkTlm.usTblErrCnt++;
            CFE_EVS_SendEvent(TO_TBL_ERR_EID, CFE_EVS_ERROR,
              "CFE_TBL_Manage() returned error 0x%08x.  TO_ManageTable failed.",
              Status);
        
            /* Re-acquire table address. */
            CFE_TBL_GetAddress ((void **) &pTable, g_TO_AppData.tableHandle);
            g_TO_AppData.pConfigTable = pTable;

            goto end_of_command;
        }

        Status = CFE_TBL_GetAddress ((void **) &pTable, 
                                      g_TO_AppData.tableHandle);
        /* Status should be CFE_TBL_INFO_UPDATED because we loaded it above */
        if (Status == CFE_TBL_INFO_UPDATED)
        {
            /* Store the new table pointer */
            g_TO_AppData.pConfigTable = pTable;
            
            /* Unsubscribe all messages from old table */
            Status = TO_UnsubscribeAllMsgs(&oldTable);
            if (Status != CFE_SUCCESS)
            {
                g_TO_AppData.HkTlm.usCmdErrCnt++;
                g_TO_AppData.HkTlm.usTblErrCnt++;
                CFE_EVS_SendEvent(TO_PIPE_ERR_EID, CFE_EVS_ERROR,
                    "Unsubscription of messages failed. "
                    "Reverting back table. TO_ManageTable failed.");
                memcpy((void *) pTable, (void *) &oldTable, 
                       sizeof(TO_ConfigTable_t));
                Status = TO_SubscribeAllMsgs();
                goto end_of_command;
            }
            
            /* Subscribe to all messages in new table */
            Status = TO_SubscribeAllMsgs();
            if (Status != CFE_SUCCESS)
            {
                g_TO_AppData.HkTlm.usCmdErrCnt++;
                g_TO_AppData.HkTlm.usTblErrCnt++;
                CFE_EVS_SendEvent(TO_PIPE_ERR_EID, CFE_EVS_ERROR,
                    "Subscription of messages failed. "
                    "Reverting back table. TO_ManageTable failed.");
                memcpy((void *) pTable, (void *) &oldTable, 
                       sizeof(TO_ConfigTable_t));
                Status = TO_SubscribeAllMsgs();
                goto end_of_command;
            }
            
            g_TO_AppData.HkTlm.usTblUpdateCnt++;
            CFE_EVS_SendEvent(TO_TBL_INF_EID, CFE_EVS_INFORMATION,
                              "ConfigTable updated succesfully. ");
        }
        else if (Status == CFE_SUCCESS)
        {
            /* Store the pointer */
            g_TO_AppData.pConfigTable = pTable;
            
            CFE_EVS_SendEvent(TO_TBL_INF_EID, CFE_EVS_INFORMATION,
                              "ConfigTable did not change.");
        }
        else 
        {
            g_TO_AppData.HkTlm.usCmdErrCnt++;
            g_TO_AppData.HkTlm.usTblErrCnt++;
            CFE_EVS_SendEvent(TO_TBL_ERR_EID, CFE_EVS_ERROR,
                    "CFE_TBL_GetAddress() returned error 0x%08x. "  
                    "TO_ManageTable failed.",
                    Status);
        }
    }

end_of_command:

#else
    }
#endif
    return;
}
