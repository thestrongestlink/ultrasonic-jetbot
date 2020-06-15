/*
Ultrasonic sensor for Jetbot
----------------------------
Trigger on port 11
Respons on port 12
5V to 3.3V response conversion with 2.2K and 4.7K resistors
I2C slave sender on port 8
----------------------------
This sketch is based on the Ping))) Sensor sketch created by David A. Mellis on 3 Nov 2008, modified by Tom Igoe on 30 Aug 2011 and modified by Ron in 2020 to 
include I2C communications.
----------------------------
The original source of Ping))) can be found on:
  http://www.arduino.cc/en/Tutorial/Ping
This example code is in the public domain.
*/

#include <Wire.h>

// this constant won't change. 
// It's the pin number of the sensor's output:
const int pingPin = 11;
const int distPin = 12;
long cm;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(distPin, INPUT);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop() {
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches;
  // The PING))) is triggered by a HIGH pulse of 2 
  // or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean 
  // HIGH pulse:
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  // A HIGH pulse whose duration is the time (in 
  // microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(distPin, HIGH);
  // convert the time into a distance
  // inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  // Print distance to serial monitor for testing
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}

// I2C function that executes whenever data is requested 
// by master. This function is registered as an event, 
// see setup()
void requestEvent() {
  byte buf[4];
  buf[0] = (byte) cm;
  buf[1] = (byte) cm>>8;
  buf[2] = (byte) cm>>16;
  buf[3] = (byte) cm>>24;
  Wire.write(buf, 4); // respond with message of 4 bytes 
                      // (cm is long type)
  Serial.println("I2C request");
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), 
  // there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 
  // feet per second).
  // This gives the distance travelled by the ping, 
  // outbound and return,
  // so we divide by 2 to get the distance of the 
  // obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds 
  // per centimeter.
  // The ping travels out and back, so to find the 
  // distance of the object we take half of the distance 
  // travelled.
  return microseconds / 29 / 2;
}
When uploading is completed, open the Arduino Monitor. Hold your hand in front of the sensor and the distance between the sensor and your hand should be displayed in the monitor. Move your hand closer and further away from the ultrasonic sensor and note the changing readout on the monitor. Once you have this functioning, we’re ready for the next step; interfacing with the Jetson Nano using I2C.

Switch off power on both Jetson Nano and the Feather M0. Now temporarily disconnect the I2C connection to the motor driver from pins 3 and 5 of the Jetson Nano (remember their positions!) and make an I2C connection between the Jetson Nano and the Feather M0. You do this by connecting the SCL pin of the Feather M0 with the SCL pin of the Jetson Nano (pin 5) and connecting the SDA pin of the Feather M0 with the SDA pin of the Jetson Nano (pin 3). Now power up again and once the Jetbot software has loaded, connect to the JupyterLab interface on your computer and create a new python session. Copy and paste the following short Python test script to JupyterLab:

import smbus
import time

bus = smbus.SMBus(1)
address = 8 # I2C address for Ultrasonic bus

def distance():
    """Returns distance measured by ultrasonics in cm"""
    return bus.read_byte_data(address, 0)

while True:
    print(distance(), " cm")
    time.sleep(1.0)
