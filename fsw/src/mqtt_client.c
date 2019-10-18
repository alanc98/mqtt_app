/*************************************************************************
** File:
**   mqtt_client.c
**
**   This code serves as the abstraction between the cFS/mqtt app 
**   and the Paho Embedded C MQTT Client library that is included
**   with the mqtt_lib cFS library.  
**
**   As I get more experience implementing this code, it might
**   make more sense to migrate these functions to the mqtt_lib to
**   serve as the abstract interface to multiple MQTT client libraries.
**   
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "mqtt_app.h"

/* 
** mqtt_lib
**  Current version uses the Paho Embedded C MQTT Client
*/ 
#include "mqtt_lib.h"

/*
** Prototype for callback 
*/
void MQTT_ClientMessageCallback(MessageData* md);

/*
** Global MQTT Client Data
*/
Network                MQTT_NetworkStruct;
MQTTClient             MQTT_ClientStruct;
MQTTPacket_connectData MQTT_ConnectData = MQTTPacket_connectData_initializer;    
unsigned char          MQTT_buf[1000];
unsigned char          MQTT_readbuf[1000];

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT Client Mqtt Initialize                                     */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MQTT_ClientInitialize(char *hostname, int port, 
                            char *clientname, 
                            char *username, char *password) 
{
    int rc;

    /*
    ** Init and connect to network
    */
    NetworkInit(&MQTT_NetworkStruct);
    NetworkConnect(&MQTT_NetworkStruct, hostname, port);

    /*
    ** Init MQTT client
    */
    MQTTClientInit(&MQTT_ClientStruct, 
                   &MQTT_NetworkStruct, 
                   1000, MQTT_buf, 1000, MQTT_readbuf, 1000); 

    MQTT_ConnectData.willFlag = 0;
    MQTT_ConnectData.MQTTVersion = 3;
    MQTT_ConnectData.clientID.cstring = clientname;
    MQTT_ConnectData.username.cstring = username;
    MQTT_ConnectData.password.cstring = password;

    MQTT_ConnectData.keepAliveInterval = 10;
    MQTT_ConnectData.cleansession = 1;

    /*
    ** Connect to MQTT server
    */
    printf("Connecting to %s %d\n", hostname, port);

    rc = MQTTConnect(&MQTT_ClientStruct, &MQTT_ConnectData);
    printf("Connected %d\n", rc);

    return(CFE_SUCCESS);

} /* End of MQTT_ClientInitialize() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT Client Subscribe                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MQTT_ClientSubscribe(char *topic, int qos)
{
    int rc;
    int translated_qos;

    /* 
    ** Translate QoS 
    */
    if (qos == MQTT_QOS0) {
       translated_qos = QOS0;
    } else if (qos == MQTT_QOS1) {
       translated_qos = QOS1;
    } else {
       translated_qos = QOS2;
    }

    /*
    ** Need to check params
    */
    rc = MQTTSubscribe(&MQTT_ClientStruct, topic, translated_qos, MQTT_ClientMessageCallback);

    if (rc == SUCCESS) {
         return(CFE_SUCCESS);
    } else {
         return(rc);
    }
   
} /* End of MQTT_ClientSubscribe() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT Client Yield Code                                          */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ClientYeild(unsigned int timeout)
{
    MQTTYield(&MQTT_ClientStruct, timeout);

} /* End of MQTT_ClientYield() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT Client Disconnect                                          */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ClientDisconnect(void)
{
    MQTTDisconnect(&MQTT_ClientStruct);
    NetworkDisconnect(&MQTT_NetworkStruct);

} /* End of MQTT_ClientDisconnect() */

/************************/
/*  End of File Comment */
/************************/
