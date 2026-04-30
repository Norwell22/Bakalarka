# File purpose
This file contains description of how to set up source code stored in this folder in order to run application using **Raspberry Pi Pico** development board.

# Project setup
1. Use official **Raspberry Pi Pico Project** extension for Visual Studio Code
2. Click on raspberry pi pico icon on left side of IDE and choose *New C/C++ Project*
3. In *Board type*, select Raspberry Pi Pico 2W. *(although project should also work with RPi Pico 2)*
4. In *Stdio support*, choose *Console over USB* option.
5. Click *Create*
6. In generated `CMakeLists.txt` file, locate or add `target_link_libraries` command and extend it to at least cover following libraries
```
target_link_libraries(context_lib_app 
        hardware_i2c
        hardware_pio
        hardware_timer
        hardware_powman
        
        )
```

# Connections
Five buttons, one four pin RGB module (three color channels and ground), four leds and 24LC015 EEPROM were used as components for this application.

Connect on-board pins as follows:
- *3v3(OUT)* <-> *Plus line on breadboard*
- *GND* <-> *Minus line on breadboard*
- *GND* <-> *- pin on RGB module*
- *GP0, GP1, GP2, GP3, GP4* <-> *connect to buttons in way described below*
- *GP17* <-> *SCL pin of EEPROM memory*
- *GP16* <-> *SDA pin of EEPROM memory*
- *GP11, GP12, GP13, GP18, GP19, GP20, GP21* <-> *connect with leds in way described below*

Connect EEPROM pins as follows:
- *A0,A1,A2* <-> *GND*
- *Vss* <-> *GND*
- *Vcc* <-> *3v3*
- *WP* <-> *GND*
- *SCL* <-> *GP17 pin of Pico*
- *SDA* <-> *GP16 pin of Pico*

Connect *GP0, GP1, GP2, GP3, GP4* pins as follows(reading input from button using pull-up resistor):
```
                PTx pin
        ____     ^      __
Vcc ---|____|----|-----(__)-----Gnd
        10KΩ          Button

```

Connect *GP11 - 13 and GP 18-21* pins as follows (leds powered up by GPIO pins with usage of external resistors)
```
          ____                        (no need to use Gnd for RGB module) 
GPxx --- |____|---|>-------------------------Gnd
          100Ω    LED(module or external)
```

## 24LC015 EEPROM Pinout
```
     ___________
A0 -|    |_|    |- Vcc
    |           |
A1 -|           |- WP
    |           |    
A2 -|           |-SCL
    |           |
Vss-|___________|-SDA

```
# Sources
- Pico 2W datasheet
- RP2350 datasheet
- Getting started with Pico