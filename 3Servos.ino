// In diesem ersten Pr0gramm steuern wir die Servomotoren


/////////Librarys///////////
#include <Arduino.h>            
#include <Servo.h>              
#include <Adafruit_NeoPixel.h>  
////////////////////////////    


//////VARIABELN////// 
int VoltagePin = A5;
float Voltage = 0;

#define LEDPIN 11      
#define LEDCOUNT 2     

int LichtSensorL = A1;
int LichtSensorR = A2;

int HelligkeitL;
int HelligkeitR;

int ServoPinL = 3;        //Servo Links hängt an Digital Pin3 Rechts an Pin 4
int ServoPinR = 4;  

int ServoLMitte = 1718 ; // Servos bekommen PWM Werte von 1000 bis 2000, da die hier verbastelt sind um dauerhaft zu drehen muss der Totpunkt per Hand bestimmt werden
int ServoLDrehrichtung = 1; // NUR 1 ODER -1 !!! tauschen wenn der Motor sich falschrum dreht

int ServoRMitte = 1499 ;
int ServoRDrehrichtung = -1; // NUR 1 ODER -1 !!!

int Geschwindigkeit = 40;   //wie schnell der R0boter fahren soll unter 20 ungenau über 100 keine Unterschiede mehr
/////////////////////


//////Initiierung//// 
Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_GRB + NEO_KHZ800);

Servo servoL; //Initiiert 2 servos genannt "servoL" und "servoR"
Servo servoR;
/////////////////////


//////Funktionsnamen/////
void CheckVoltage();

void Stop();                 
void VorwaertsFahrt();
void drehRechts();
void drehLinks();        
////////////////////////


/////SETUP///////////
void setup() {

  Serial.begin(9600);

  strip.begin();

  servoL.attach(ServoPinL);            //startet die beiden Servos
  servoR.attach(ServoPinR);

}
/////////////////////


//////LOOP///////////
void loop() {
            
                                        ///NICHT ANFASSEN!! AKKU SCHUTZ/////
  CheckVoltage();                       
  if(Voltage < 3.7){                    
    strip.setPixelColor(0, 100, 0, 0); 
    strip.setPixelColor(1, 100, 0, 0);  
    strip.show();
    delay(10);                    // ohne dieses Delay verschluckt sich die schleife und die Motoren zucken stark
    Stop();                       // hält die motoren an
  }
  else{
                                        ////AB HIER DARFST DU WIEDER////////
    VorwaertsFahrt();
    delay(2000);
    drehLinks();
    delay(500);
    VorwaertsFahrt();
    delay(2000);
    drehRechts();
    delay(1000);

  }
}
////////////////////


//////FUNKTIONEN//////              
void CheckVoltage(){                
  Voltage = analogRead(VoltagePin);
  Voltage = map(Voltage, 0, 1024, 0, 500);
  Voltage = Voltage/100;
}

void VorwaertsFahrt(){                                              // Funktion zum Vorwärtsfahren
  servoL.writeMicroseconds(ServoLMitte + ServoLDrehrichtung*Geschwindigkeit);    // gibt dem Servo einen Wert in dem auf den Mittelpunkt die Geschwindigkeit in der passenden Richtung addiert wird
  servoR.writeMicroseconds(ServoRMitte + ServoRDrehrichtung*Geschwindigkeit);
}

void drehRechts(){                                                  // Funktion zum rechtsrum drehen
  servoL.writeMicroseconds(ServoLMitte - ServoLDrehrichtung*Geschwindigkeit*0.8);
  servoR.writeMicroseconds(ServoRMitte + ServoRDrehrichtung*Geschwindigkeit);
}

void drehLinks(){                                                   // Funktion zum linksrum drehen
  servoL.writeMicroseconds(ServoLMitte + ServoLDrehrichtung*Geschwindigkeit);
  servoR.writeMicroseconds(ServoRMitte - ServoRDrehrichtung*Geschwindigkeit*0.8);
}

void Stop(){                                                        // Funktion um die Servos zu stoppen
  servoL.writeMicroseconds(ServoLMitte);
  servoR.writeMicroseconds(ServoRMitte);
}
//////////////////////
