# Busy-button
MQTT button to show if busy or not, python for pi to display status as full screen, red for busy, green not busy.
The button LED will display green whilst the device is connecting to Wifi, which will go out once connected.
Once connected the LED will mirror the pi display, and show red when busy and green when not busy, this status is changed by pressing the button.

This has been created for element #badass woman makers video competition.

MQTT_button.pdf         - Circuit diagram
case_t2.scad            - Case design files for 3D printing
Button-HUZZAH_1.ino     - Code for Adafruit HUZZAH Feather ESP8266
mqtt-status.py          - Python for RaspberryPi, screen red when busy, green not busy

Button:
Adafruit HUZZAH Feather ESP8266
8mm THT Neopixel
Push Button
470 Ohm resistor
10K resistor
0.1uF Capacitor

Raspberry Pi:
Raspberry Pi4 2GB
Raspberry Pi 7" touchscreen display
Pimoroni pibow touchscreen frame and pibow Pi4 case
Fan shim - used, but optional

Case:
Printed with 3mm Red PLA on a Reprap Mendel
