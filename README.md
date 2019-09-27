# Data Logger (and using cool sensors!)

*A lab report by Ryan Curtis.*

## In The Report

Include your responses to the bold questions on your own fork of [this lab report template](https://github.com/FAR-Lab/IDD-Fa18-Lab2). Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

For this lab, we will be experimenting with a variety of sensors, sending the data to the Arduino serial monitor, writing data to the EEPROM of the Arduino, and then playing the data back.

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**
The values range between 0-1023.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**
There are 10 bits of resolution.

## Part B. RGB LED

**How might you use this with only the parts in your kit? Show us your solution.**
I created a button to toggle the color of the RGB LED:
[video](https://youtu.be/3NKDuqv9GDM)

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**
It outputs values 0-255 and reads values 0 to ~990.

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**
It would spike when force was applied sinusoidally and then drop back down when the force is removed.

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**
Divide the value being read by the fsr by 4 to scale the value into the range of 0-255 so the LED will output its full range.

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**
A resistance of about 30k provides a range of resistances between 100-1000.

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**
Like voltages, resistances are almost a sinusoidal relationship to the stimulus. When stimulus is applied, it increases dramatically and then when its removed it drops dramatically. It is like a sigmoidal activation function.

### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**
```int redPin =11;
int greenPin = 10;
int bluePin = 9;
 
// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH(A4,A5);

void setup() {
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  

}

void loop() {
  // put your main code here, to run repeatedly:
  lis.read();
  red = (lis.x)(lis.x)*255/4;
  green = (lis.y)(lis.y)*255/4;
  blue = (lis.z)(lis.z)*255/4;
  
  setColor(red, green, blue);  // green
  delay(500);
  
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
```


## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**
No. The states are arbirtarily assigned between the different sensor values and can be in any order.

**b. Why is the code here all in the setup() functions and not in the loop() functions?**
Because upon entering the states it runs the code to execute on eeprom once and then it is done and is in the state.

**c. How many byte-sized data samples can you store on the Atmega328?**
1024 bytes can be stored

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**
Read the analog data from the pins and encode it as 8 bits representing values 0-255 using binary.

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**
use multiple bytes that are adjacent to each other and increment your location in EEPROM by the size of what you store to avoid interfering with the data.

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**
```#include <EEPROM.h>

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {   
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  int eeAddress = 0;   //Location we want the data to be put.

  //One simple call, with the address first and the object second.
  EEPROM.put(eeAddress, sensorValue);

  Serial.println("Written int data type!");

  eeAddress += sizeof(int); //Move address to the next byte after float 'f'.

  EEPROM.get(eeAddress, f);
  Serial.print(f);
 }
 ```

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**
[image](https://github.com/rec285/IDD-Fa19-Lab3/blob/master/Data%20Logger.pdf);

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
The speaker acts like a microphone and when the button is not pressed and then when the button is pressed it plays back the audio through the speaker.
[code1](https://github.com/rec285/IDD-Fa19-Lab3/blob/master/SwitchState2.ino)
[code2](https://github.com/rec285/IDD-Fa19-Lab3/blob/master/state1.ino)
[code3](https://github.com/rec285/IDD-Fa19-Lab3/blob/master/state2.ino)
[video](https://youtu.be/czTRxe9ly3A)
