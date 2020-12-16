Das Pr0gramm ist fertig um einer Linie zu folgen und eventuell ein ziemlicher Brecher für den Anfang, aber bis du hier bist hast du vielleicht schon einen Überblick :D

/////LIBRARYS////////
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
/////////////////////


//////VARIABELN//////
int ServoLMitte = 1718 ; // Servos bekommen PWM Werte von 1000 bis 2000, da die hier verbastelt sind um dauerhaft zu drehen muss der Totpunkt bestimmt werden
int ServoLDrehrichtung = 1; // NUR 1 ODER -1 !!! tauschen wenn der Motor sich falschrum dreht

int ServoRMitte = 1499 ;
int ServoRDrehrichtung = -1; // NUR 1 ODER -1 !!!

int Geschwindigkeit = 40;   //wie schnell der R0boter fahren soll unter 20 ungenau über 100 keine Unterschiede mehr


int VoltagePin = A5;      // Spannungsmessung vom Akku hängt an Analog5
double Voltage;           // in der Variable wird die AkkuSpannung gespeichert

int LichtSensorL = A1;    //Lichtsensor Links hängt an Analog1 Rechts an Analog2
int LichtSensorR = A2;

int ServoPinL = 3;        //Servo Links hängt an Digital Pin3 Rechts an Pin 4
int ServoPinR = 4;  

int DunkelheitGrenzWertLinks = 0;
int DunkelheitGrenzWertRechts = 0;

#define LEDPIN 11   // LEDs hängen an DigitalPin 11
#define LEDCOUNT 2    // es gibt 2 LEDs
/////////////////////


////INITIIERUNG//////
Servo servoL; //sagt dem pr0gramm das es zwei Servos gibt links und rechts
Servo servoR;

Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_GRB + NEO_KHZ800); //sagt dem Pr0gramm das es die zwei LEDs gibt
/////////////////////


//////FUNKTIONSNAMEN/////     // müssen hier oben alle einmal benannt werden
void Stop();                  // damit das Pr0gramm weis das die Funktionen existieren
void VorwaertsFahrt();
void drehRechts();
void drehLinks();
void CheckVoltage();
void LEDS();
void Linienverfolgen();
int GetLichtSensorL();
int GetLichtSensorR();
void LichtSensorInit();
/////////////////////////


/////////SETUP////////////
void setup() {                 // Setup läuft einmal am start durch und sagt dem Arduino zB was an welchem Pin hängt

  servoL.attach(ServoPinL);            //sagt dem Arduino das die zwei Servos exisitieren
  servoR.attach(ServoPinR);

  strip.begin();               // initiiert LEDs
  Serial.begin(9600);          //kommunikation über USB

  Stop();                      //sorgt dafür das die Motoren am anfang still stehen
  LEDS();                      // Macht untere LED Weiß
  LichtSensorInit();           // Kalibriert Helligkeitssensoren
}
//////////////////////////


///////LOOP///////////////
void loop() {           // loop läuft nach dem Setup immer wieder durch, hier passiert das eigentlich spannende
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
  Linienverfolgen();    //funktion zum Linien verfolgen
  }
}
///////////////////////////


//////////FUNKTIONEN///////
void LEDS(){                             // Funktion um LEDs am Anfang einzufärben
  strip.setPixelColor(0, 200, 200, 200); // erste LED (0) auf weiß
  strip.setPixelColor(1, 255, 0, 0);     // zweite LED (1) auf rot
  strip.show();                          //updated die LEDs
}

void CheckVoltage(){                        //Funktion um die AkkuSpannung zu überprüfen
  Voltage = analogRead(VoltagePin);         //speichert den gelesenen Wert in der Variable
  Voltage = map(Voltage, 0, 1024, 0, 500);  // mapt den Analogen Wert (0 bis 1024) auf die mögliche Spannung am Pin (0 bis 5V)*100 da map nur ganze Zahlen ausspuckt
  Voltage = Voltage/100;                    // teilt den Wert durch 100 um die richtige Spannung zu lesen
}

void VorwaertsFahrt(){                                              // Funktion zum Vorwärtsfahren
  servoL.writeMicroseconds(ServoLMitte + ServoLDrehrichtung*Geschwindigkeit);    
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

int GetLichtSensorL(){                          //Funktion um den linken Lichtsensor auszulesen
  int value;
  value = analogRead(LichtSensorL);
  for(int i = 0; i <20; i++){                     // Da der Lichtsensor wegen den LEDs viel schwankt nehme ich hier einen Durchschnitt von 20 Werten
    value = value + analogRead(LichtSensorL);
  }
  value = value / 20;
  return(value);
}

int GetLichtSensorR(){                          //Funktion um den rechten Lichtsensor auszulesen
  int value = 0;
  value = analogRead(LichtSensorR);
  for(int i = 0; i <20; i++){
    value = value + analogRead(LichtSensorR);
  }
  value = value / 20;
  return(value);
}

void LichtSensorInit(){                       //Funktion um die Dunkelheitsgrenzwerte einzustellen

  delay(10000);                               // gibt dir 10sek Zeit den roboter auf eine helle Umgebung zu stellen
  strip.setPixelColor(1, 100, 0, 50);         // färbt dann die vordere LED pink
  strip.show();

  DunkelheitGrenzWertLinks = 0;                                               // setzt den Grenzwert auf 0
  for(int i = 0; i <20; i++){                                                 
    DunkelheitGrenzWertLinks = DunkelheitGrenzWertLinks + GetLichtSensorL();  // liest 20 mal den Sensor aus und addiert die werte
    delay(20);
  }
  DunkelheitGrenzWertLinks = DunkelheitGrenzWertLinks/20 - 140;               // Teilt die Addition durch 20 um einen Durchschnitt zu bekommen zieht danach 140 ab um eine Toleranz einzuberechnen
  
  DunkelheitGrenzWertRechts = 0;                                              // das gleiche für rechts
  for(int i = 0; i <20; i++){
    DunkelheitGrenzWertRechts = DunkelheitGrenzWertRechts + GetLichtSensorR();
    delay(20);
  }
  DunkelheitGrenzWertRechts = DunkelheitGrenzWertRechts/20 - 140;

  strip.setPixelColor(1, 100, 100, 100);                                      // blinkt für eine halbe Sek weiß auf um zu zeigen das er fertig ist
  strip.show();
  delay(500);
  strip.setPixelColor(1, 0, 0, 0);                                            // LED geht dann aus
  strip.show();
}

void Linienverfolgen(){                                                                               //Funktion um Linien zu verfolgen
  if(GetLichtSensorL() > DunkelheitGrenzWertLinks && GetLichtSensorR() > DunkelheitGrenzWertRechts){  
    VorwaertsFahrt();                                                                                 // wenn beide Sensoren Helle Werte lesen, fahre Vorwärts
    strip.setPixelColor(1, 100, 100, 0);                                                              // und leuchte Gelb
    strip.show();
    delay(50);
  }
  else if (GetLichtSensorL() > DunkelheitGrenzWertLinks && GetLichtSensorR() < DunkelheitGrenzWertRechts){
    drehLinks();                                                                                     // wenn Links dunkel und rechts hell drehe links
    strip.setPixelColor(1, 0, 100, 0);                                                               // leuchte dabei grün
    strip.show();
    delay(50); 
  }
  else if (GetLichtSensorL() < DunkelheitGrenzWertLinks && GetLichtSensorR() > DunkelheitGrenzWertRechts){
    drehRechts();                                                                                     // rechts dunkel links hell, drehe rechts
    strip.setPixelColor(1, 100, 0, 0);                                                                // leuchte dabei rot
    strip.show();
    delay(50);
  }
  else{                                                                                               // wenn nichts davon eintrifft(alles dunkel)
    Stop();                                                                                           // bleibe stehen
    strip.setPixelColor(1, 0, 0, 0);                                                                  // licht aus
    strip.show();
    delay(50);
  }
}
/////////////////////////////
