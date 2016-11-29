MeArm - Deluxe Default
======================

This is the Arduino code that ships on the MeArm Deluxe Kit Pro Micro.

Download version 1.6.5 of the Arduino IDE. There are problems with the later versions and the chip that we use.
Install the Arduino IDE file following the onscreen prompts. 
Once installed start the Arduino IDE and go to File > Preferences

and under

Additional Boards Manager URLs:

paste the following:

https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.jsonClick OK

Then go to

Tools > Board: > Boards Manager

Type Sparkfun and click to install Sparkfun AVR Boards

Close then go to

Tools > Board:

and select Pro Micro.

Go to Tools > Processor

and select “ATMega32u4 (3.3V, 8MHz)” or “ATMega32u4 (5.0V, 16MHz)” depending on your board.

Plugging in your Pro Micro Clone via USB should now install the correct driver. If it fails, please use this driver file (right click and save file as).

You are now ready to start programming your Pro Micro Clone (MeArm Brains Board)

There are two dependent libraries required: 
* [Arduino with Adafruit PWM driver board](https://github.com/RorschachUK/meArm_Adafruit)
* [Nokia Screen Driver from Adafruit](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library)

Things to note are that you can adjust the screen contrast with the variable CON (line 26) and the set up of the servos between lines 98 and 121.
