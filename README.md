# esp8266_lasko_ir
Control a Lasko Fan, via IR, with an ESP8266 Microcontroller

## Requirements
Requires version 2+ ot the ESP8266 IR fork:
https://github.com/markszabo/IRremoteESP8266

Original idea borrowed from here: https://www.hackster.io/BuddyC/wifi-ir-blaster-af6bca

## Usage
Connect an IR Transmitter to GPIO4, provide power to the transmitter.

Upload the sketch, verify the IP in your serial monitor, and trigger the commands with curl:

Example:
curl http://192.168.1.127/power


##Commands
/power
/rotate
/speed
/timer


