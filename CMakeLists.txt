cmake_minimum_required(VERSION 2.6.4)
project(CFS_MQTT C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(${mqtt_lib_MISSION_DIR}/fsw/public_inc)

aux_source_directory(fsw/src APP_SRC_FILES)

# Create the app module
add_cfe_app(mqtt ${APP_SRC_FILES})

add_definitions(-DMQTTCLIENT_PLATFORM_HEADER=MQTTLinux.h)

include_directories(fsw/src)
include_directories(fsw/tables)
aux_source_directory(fsw/tables APP_TBL_FILES)
add_cfe_tables(MQTT_Mqtt2SbTable fsw/tables/mqtt2sb.c)

