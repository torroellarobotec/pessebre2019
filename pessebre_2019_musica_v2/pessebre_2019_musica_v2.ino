#include <SoftwareSerial.h>
#include <RedMP3.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;


//MP3 mp3_1(2, 3);
MP3 mp3_2(6, 7);
//MP3 mp3_3(6, 7);

int8_t track8 = 0;
int8_t volume8 = 0;
int identificador = 0;
int intervalMinuts = 10;


int up1 = 4;//fonta
int up2 = 4;
int up3 = 4;
int maxmusic = 2;

boolean newData = false;
const byte numChars = 32;
char receivedChars[numChars];
void setup()
{

  Serial.begin(9600);
rtc.begin();
  // digitalWrite(EnTxPin, HIGH); //RS485 como Transmisor
  // digitalWrite(EnTxPin2, HIGH); //RS485 como Transmisor
  Serial.println("Musica...");
  delay(7000);
  mp3_2.stopPlay();
  delay(500);
mp3_2.playWithVolume(1, 30);
}

void loop()
{

   int tempus = 0;
   DateTime now = rtc.now();
  int minut = now.minute();
  //Serial.println(minut,DEC);
  int segon = now.second();
  //Serial.println(segon, DEC);
 
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
;
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  if (minut >= intervalMinuts)
  {
    int factor = minut / intervalMinuts;
    minut = minut - factor * intervalMinuts;
  }
  tempus = minut * 60 + segon;
  
  if (tempus==0)

  {
    Serial.print("Inici musica");
    mp3_2.stopPlay();
    delay(100);
    mp3_2.playWithVolume(1, 30);
  }
  delay( 1000);
  //delay(10000);
}
void recvWithStartEndMarkers() {

}

void musica()
{
  

  
    
    mp3_2.playWithVolume(1, 20);
    delay(30000);
    mp3_2.stopPlay();

}
void test()
{
  
}
void musica (String cad)
{
  
}
void showNewData() {

}
