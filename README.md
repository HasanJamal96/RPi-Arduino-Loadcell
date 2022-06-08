# RPi-Arduino-Loadcell


Project aims to control Stepper motor and read weight using HX711.
Raspberry Pi send start command to Arduino, Arduino will measure weight
and send back to RPi. 
Then Arduino will turn 1/4 and RPi will capture image using Pi Camera.
Then Arduino will turn 2/4 and RPi will capture image.
Then Arduino will turn 3/4 and RPi will capture image.
Then Arduino will turn 4/4 and RPi will capture image.

then Arduino and RPi will send process complete command to eachother.
