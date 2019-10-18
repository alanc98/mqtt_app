#!/bin/bash
# 
# MQTT Test publish loop
#
while true
do
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/temperature" -m "$((28+RANDOM%(5))).$((RANDOM%999))"
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/light" -m "$((100+RANDOM%(50)))"
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/red" -m "$((80+RANDOM%(30)))"
   sleep 0.2
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/green" -m "$((80+RANDOM%(30)))"
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/blue" -m "$((80+RANDOM%(30)))"
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/envirophat/heading" -m "$((180+RANDOM%(180))).$((RANDOM%999))"
   sleep 0.2
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/temperature" -m "$((28+RANDOM%(30))).$((RANDOM%999))"
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/humidity" -m "$((50+RANDOM%(50))).$((RANDOM%999))"
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/pressure" -m "$((30+RANDOM%(10))).$((RANDOM%999))"
   sleep 0.2
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/orientation/pitch" -m "$((120+RANDOM%(32))).$((RANDOM%999))"
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/orientation/roll" -m "$((120+RANDOM%(32))).$((RANDOM%999))"
   mosquitto_pub -h 127.0.0.1 -t "rpi3-1/sensehat/orientation/yaw" -m "$((120+RANDOM%(32))).$((RANDOM%999))"
   sleep 0.2
   mosquitto_pub -h 127.0.0.1 -t "esp8266/bno55/temp" -m "$((50+RANDOM%(30)))"
   mosquitto_pub -h 127.0.0.1 -t "esp8266/bno55/orientation/x" -m "$((100+RANDOM%(50)))"
   mosquitto_pub -h 127.0.0.1 -t "esp8266/bno55/orientation/y" -m "$((100+RANDOM%(50)))"
   mosquitto_pub -h 127.0.0.1 -t "esp8266/bno55/orientation/z" -m "$((100+RANDOM%(50)))"
   sleep 0.2
   mosquitto_pub -h 127.0.0.1 -t "rpi0-1/helloworld/message" -m "Hello, this is a test."
done
