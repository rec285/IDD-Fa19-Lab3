/*
  basic state machine 2
 
  Modified to switch between states to write, read and clear EEPROM
 
 Demonstrates how to use a case statement to create a simple state machine.
 This code uses a potentiometer knob to select between 3 states.
 
 The circuit:
 * pot from analog in 0 to +5V
 * 10K resistor from analog in 0 to ground
 
 created 13 Apr 2010
 by Wendy Ju 
 modified from switchCase by Tom Igoe
 
 12 Sep 2018
 Modified to switch between states to write, read and clear EEPROM
 */

#include <EEPROM.h>

const int numStates = 3;
const int sensorMin =0;
const int sensorMax = 1024;
const int EEPROMSIZE=1024;

int sensorPin = 0;    // select the input pin for the potentiometer
int ledPin = LED_BUILTIN;    
int state,lastState = -1;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // map the pot range to number of states :
  if (digitalRead(0) == LOW){
    state = 2;
  }else{
    state = 1;
  }
  // do something different depending on the 
  // range value:
  switch (state) {
  case 2:    
    doState2();
    break;
  case 1:    
    doState1();
    break;
  } 
  lastState = state;
}
