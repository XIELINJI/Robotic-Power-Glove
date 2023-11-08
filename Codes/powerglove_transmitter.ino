/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

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
  radio.begin();
  radio.openWritingPipe(address); // 00001 
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.stopListening();
  int potValue1 = analogRead(A0);
  int potValue2 = analogRead(A1);
  int potValue3 = analogRead(A2);
  int potValue4 = analogRead(A3);
  int potValue5 = analogRead(A4);
  data.angleV1 = map(potValue1, 100, 270, 180, 0);
  data.angleV2 = map(potValue2, 100, 270, 180, 10);
  data.angleV3 = map(potValue3, 100, 270, 180, 10);
  data.angleV4 = map(potValue4, 100, 270, 180, 0);
  data.angleV5 = map(potValue5, 100, 270, 180, 0);
  Serial.print(data.angleV1);  Serial.print(" ");
  Serial.print(data.angleV2);  Serial.print(" ");
  Serial.print(data.angleV3);  Serial.print(" ");
  Serial.print(data.angleV4);  Serial.print(" ");
  Serial.println(data.angleV5);
  radio.write(&data, sizeof(Data_Package));

  delay(5);

}
