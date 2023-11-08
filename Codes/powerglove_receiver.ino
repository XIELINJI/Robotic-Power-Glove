/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* +
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include "ServoEasing.hpp"
#include <Arduino.h>
#define ENABLE_EASE_CUBIC


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

ServoEasing myServo1;
ServoEasing myServo2;
ServoEasing myServo3;
ServoEasing myServo4;
ServoEasing myServo5;

struct Data_Package{
  int angleV1 = 0;
  int angleV2 = 0;
  int angleV3 = 0;
  int angleV4 = 0;
  int angleV5 = 0;
};

Data_Package data;

void setup() {
  Serial.begin(9600);
  myServo1.attach(5);
  myServo2.attach(6);
  myServo3.attach(4);
  myServo4.attach(3);
  myServo5.attach(2);
  myServo1.setEasingType(EASE_CUBIC_IN_OUT);
  myServo2.setEasingType(EASE_CUBIC_IN_OUT);
  myServo3.setEasingType(EASE_CUBIC_IN_OUT);
  myServo4.setEasingType(EASE_CUBIC_IN_OUT);
  myServo5.setEasingType(EASE_CUBIC_IN_OUT);
  radio.begin();
  radio.openReadingPipe(0, address); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
//  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      radio.read(&data, sizeof(Data_Package));
      Serial.println(data.angleV1);  
      Serial.println(data.angleV2);
      myServo1.startEaseToD(data.angleV1, 100);
      myServo2.startEaseToD(data.angleV2, 100);
      myServo3.startEaseToD(data.angleV3, 100);
      myServo4.startEaseToD(data.angleV4, 100);
      myServo5.startEaseToD(data.angleV5, 100);
      delay(100);
    }
//    delay(5);

  }
}
