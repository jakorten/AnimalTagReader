/*
    This sketch shows how to read 134.2K tags used for chipping animals.

    Tested with https://allinbest.com/blog/1342k-animal-tag-fdxb-iso11784-reader-module/
    WL-134 long-range reader module 134.2 K that supports ISO11784/85 protocols, (EM4305, HITAG256, EM1001).

    Johan Korten
    July, 2021

    We used a SAMD21 microcontroller (in this case the Arduino Nano 33 IoT board)
    - TX Pin of the reader module was connected to RX (D5), see SerialHelper (connect GND of the module and the board as well)
    - 9V battery was connected to VCC and GND of the module 
    
    Note: a 9V battery gets depleted very soon by the board so better use e.d. a normal power supply or use e.g. a transistor to only power
    the module when needed.
*/

#include <Arduino.h>
#include <stdlib.h>
#include "wiring_private.h"
#include "settings.h"


#define tagExpectedSize 30

int incomingByte = 0; // for incoming serial data
unsigned char tagbuffer[35]; // tagExpectedSize + 5 (margin)
 
void setup() {
  initSerial();
}
 
void loop() {
  processSerial();
}

