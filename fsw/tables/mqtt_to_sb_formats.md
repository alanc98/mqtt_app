# cFS MQTT App Input formats

The following formats are for MQTT subscriptions that are passed on to the cFS Software Bus

## MQTT Payload Types

These are the data types being sent as MQTT payloads to the mqtt cFS app. There are two types of payloads that the cFS MQTT app recognizes

### 1) MQTT_PRIMITIVE

This is a define in the cFS mqtt2sb table. It represents a primitive data type such as integer, float, or string. The paload is assumed to be a single string without JSON formatting.

#### Primitive Datatypes:

The following primititive data types are supported:
- MQTT_INT8 - an 8 bit signed integer
- MQTT_UINT8 - an 8 bit unsigned integer
- MQTT_INT16 - a 16 bit signed integer
- MQTT_UINT16 - a 16 bit unsigned integer
- MQTT_INT32  - a 32 bit signed integer
- MQTT_UINT32 - a 32 bit unsigned integer
- MQTT_FLOAT - a 4 byte floating point number
- MQTT_DOUBLE - an 8 byte floating point number
- MQTT_STRING16 - a 16 byte string (extra characters beyond 16 bytes are ignored)
- MQTT_STRING32 - a 32 byte string (extra characters beyond 32 bytes are ignored)
- MQTT_STRING64 - a 64 byte string (extra characters beyond 64 bytes are ignored)
- MQTT_STRING128 - a 128 byte string (extra characters beyond 128 bytes are ignored)

When the MQTT_PRIMITIVE topics are used, it results in one data point per CCSDS packet going to the cFS Software Bus. This is not efficient for a number of reasons, but it is simple to implement. The cFS HK app can be used to create combined packets.

#### Examples:

Here are some examples of the MQTT_PRIMITIVE payloads that are sent to the cFS MQTT app:

- MQTT_INT8 - "127" or "-44"
- MQTT_INT32 - "32768"
- MQTT_FLOAT - "127.0304"
- MQTT_DOUBLE - "1239.9292"
- MQTT_STRING16 - "Hello World!"

### 2) MQTT_JSON_PAYLOAD

This define in the cFS mqtt2sb table indicates that the MQTT payload being received is in JSON format. With this MQTT payload type, a single MQTT JSON formatted payload can be translated to a single cFS Software Bus packet. This should work for an arbitrary number of parameters. It should work for either command or telemetry packets as well.

This is an example of the JSON payload format:

```
{
   "description" : "EnviroPhat Gyro Data",
   "params" : [
      {
         "name" : "gyro_x",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 1.34
      },
      {
         "name" : "gyro_y",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 3.45
      },
      {
         "name" : "gyro_z",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 5.66
      },
      {
         "name" : "accel_x",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 0.23
      },
      {
         "name" : "accel_y",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 0.032
      },
      {
         "name" : "accel_z",
         "type" : "MQTT_FLOAT",
         "length" : 4,
         "value" : 9.33
      }
   ]
}
```

Note: The MQTT_JSON_PAYLOAD is not supported in the cFS MQTT App yet!

