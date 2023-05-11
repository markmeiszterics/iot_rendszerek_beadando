
# Alert System - Arduino - Raspberry Pi

The "application" uses server-client architecture.
The server side application is written in .cpp for Arduino, the Client side is written in .py for Raspberry Pi.

The project use a LED, a Buzzer and a Light Sensor.

The "house" is secured when the Light Sensor is not triggered.
If light Sensor is triggered, you have to enter a 4-digit PIN code on the Python terminal, unless you really like the music of the buzzer.
If the code is correct, the LED and Buzzer turns off.

Used components: Arduino Sensor Kit, Arduino UNO R3, VSCode with cpp and python extensions.

