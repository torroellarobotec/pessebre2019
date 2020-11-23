
//#include "SevenSegmentTM1637.h"
#include <RTClib.h>
#include <DMXSerial.h>
//#include <SoftwareSerial.h>
#include <Wire.h>

//#include <RedMP3.h>
//#include "SevenSegmentTM1637.h"

//-----------------------------------------
//    ULL, línia  #define DMX_USE_PORT1 //treue per arduino uno
//    a DMXserial.cpp de la llibreria dmx
//
//---------------------------------------------

// RTC_DS1307 rtc;
RTC_DS3231 rtc;

//MP3 mp3_1(48,50);

const int canals = 30;

const int estats = 20;
const int estatsMusica = 20;

const int u = 250; //valor màxim llum
const int d = 0; //valor apagat
const int b = 75;
const int m = 120; //4
const int o = 200; //5
const int x = 1000 ;//No fer res en el llum
int tempsCanvi=0;
int estatActual = 1000;
int estatActualMusica = -1;
int intervalMinuts = 10;

int MatriuEstats[estats][canals] = {
  // 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
  
  //Inicia
  { u, d, d, d, d, d, d, d, d, u, d, d, d, d, d, d, d, u, u, d, d, u, d, u, d, d, d, d, d, d, //de l'1 al 3o
  },
  { x, x, m, u, x, x, x, x, x, x, x, m, u, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  }, 
  { x, x, x, x, x, x, x, x, x, x, x, x, x, m, x, x, b, x, x, x, u, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { m, x, x, x, x, x, u, x, x, m, x, x, x, d, x, x, x, x, x, x, d, x, u, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, d, x, x, x, x, x, m, x, x, x, d, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { d, m, d, u, u, u, x, u, u, d, m, u, u, u, u, u, u, u, u, u, u, u, u, u, d, d, d, d, d, d, //de l'1 al 3o NITTTTTTTTTTTTTT
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, x, d, m, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, d, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, d, u, x, x, x, x, x, x, x, x, u, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, u, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, u, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, d, u, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, u, x, x, x, x, x, x, m, x, x, x, x, x, x, x, x, m, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, x, x, d, x, x, x, x, x, x, x, d, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, x, x, x, x, x, x, u, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, d, x, x, x, x, x, x, x, x, x, x, x, x, x, u, d, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, m, x, x, x, x, x, x, x, x, m, x, x, x, x, x, x, x, x, x, x, u, u, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, u, u, x, x, x, x, x, x, x, u, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  },
  { x, x, x, x, x, x, d, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, //de l'1 al 3o
  }
  
};
int MatriuTemps[estats] = {
  0,
  100,  //
  200, 238, //
  256, 420, //nit
  440, 480, //
  500, 515, //
  520, 525, //
  530, 535, //
  537, 539, //
  540, 541, //
  543, 561
};
int MatriuTempsMusica[estatsMusica] = {
  0,
  300,  //Nit
  314, 328, //Medes
  342, 356, //Sta. Caterina
  370, 384, //Naixement
  398, 412, //Angel
  426, 440, //Creu
  454, 468, //Musics
  482, 496, //Ovelles
  510, 524, //cascada
  543, 561
};


void setup() {

  if (intervalMinuts == 3)
  {
    MatriuTemps[0] = 0;
    MatriuTemps[1] = 40;
    MatriuTemps[2] = 70;
    MatriuTemps[3] = 90;
    MatriuTemps[4] = 110;
    MatriuTemps[5] = 120; 
    MatriuTemps[6] = 124;
    MatriuTemps[7] = 130;
    MatriuTemps[8] = 135;
    MatriuTemps[9] = 140;
    MatriuTemps[10] = 145;
    MatriuTemps[11] = 150;
    MatriuTemps[12] = 152;
    MatriuTemps[13] = 155;
    MatriuTemps[14] = 158;
    MatriuTemps[15] = 160;
    MatriuTemps[16] = 164;
    MatriuTemps[17] = 167;
    MatriuTemps[18] = 172;
    MatriuTemps[19] = 176;
   
   


  }
  //Serial.begin(9600);
  DMXSerial.init(DMXController);
 
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26,OUTPUT); //rele dimmer dia/nit
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32,OUTPUT);

 rtc.begin();
  delay(300);

digitalWrite(24 ,HIGH);  //dia
  
  
  
  // Si se ha perdido la corriente, fijar fecha y hora
//  if (rtc.lostPower()) {
//    // Fijar a fecha y hora de compilacion
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//
//    // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
//    // rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));
//  }
//
//  
    resetDmx();
    delay(2000);
   
    estatActual = 0;
   // Serial.print("Arrancant...");
    executaEstat();

  

}

void resetDmx()
{
  for (int y = 1; y < (canals + 1); y++)
  {
    DMXSerial.write(y, 0);
    delay(10);
  }
 // Serial.println("Reset DMX fet");
}


void automatic()
{
   int tempus = 0;
   DateTime now = rtc.now();
   printDate(now);
  int hora =  now.hour();
  //Serial.println(hora,DEC);
  int minut = now.minute();
  //Serial.println(minut,DEC);
  int segon = now.second();
  //Serial.println(segon, DEC);
 
  
  if (minut >= intervalMinuts)
  {
    int factor = minut / intervalMinuts;
    minut = minut - factor * intervalMinuts;
  }
  tempus = minut * 60 + segon;
 // Serial.print("Seqúència: ");
 // Serial.println(tempus, DEC);
  if ((tempus==0)|| (tempus==1))
  {
    if(tempsCanvi==700)

    {
      //tormar a 0
    estatActual=0;
   // Serial.println("Estat Actual: " + String(estatActual,DEC));
    executaEstat();
    }
    
  }
  if (tempus>=tempsCanvi)
  {
    executaEstat();
  }
}
void printDate(DateTime date)
{
  
}
void executaEstat()
{
  for (int i = 0; i < canals; i++)
  {
        int v = MatriuEstats[estatActual] [i];
    
        if (v != 1000)
        {
          if ((v >= 0) && (v < 256))
          {
            DMXSerial.write(i + 1, v);
            delay(25);
          }
    
        }
  }
  if (estatActual==5) digitalWrite(24 ,LOW);  //nit
  
  if (estatActual==0) digitalWrite(24 ,HIGH);  //dia
   
 // Serial.println("Estat actual: " + String(estatActual, DEC));
if (estatActual==20) digitalWrite(24 ,HIGH);  //dia
  
  if (estatActual==0)
  {
   // Serial.println("Arrancar musica");
    //mp3_1.playWithVolume(01,20);
  }
  estatActual++;

  
   //Serial.println("EStat Aif (estatActual < estats
  
  if (estatActual >= estats) 
  {
    tempsCanvi= 700;
  }
  else{
    tempsCanvi=MatriuTemps[estatActual];
  }
}



void loop() {
 
   //DateTime now = rtc.now();
   //printDate(now);
  automatic();
  delay(900);

}
