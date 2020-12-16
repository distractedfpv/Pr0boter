// In diesem ersten Pr0gramm wollen wir mit den beiden bunten LEDs spielen


/////////Librarys///////////    // Hier tut sich nichts
#include <Arduino.h>            
#include <Servo.h>              
#include <Adafruit_NeoPixel.h>  
////////////////////////////    


//////VARIABELN////// 
int VoltagePin = A5;
float Voltage = 0;

#define LEDPIN 11      // define ist quasi auch eine Variable die sich aber im Verlauf des Pr0gramms nicht mehr verändern kann
#define LEDCOUNT 2     // hier definieren wir den Anschlusspin der LEDs auf den DigitalPin 11 des Arduinos und definieren die Anzahl der LEDs als 2

int LichtSensorL = A1;
int LichtSensorR = A2;

int HelligkeitL;
int HelligkeitR;
/////////////////////


//////Initiierung////  // Initiiert Funktionsgruppen, ist Magie aber wichtig :D
Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_GRB + NEO_KHZ800); //Gründet eine LED Gruppe "strip" mit "LEDCOUNT" Menge, an "LEDPIN" angeschlossen. der Rest ist Hardware spezifisch
/////////////////////


//////Funktionsnamen/////     // Wir schreiben unten eigene Funktionen die wir Aufrufen können, damit das Pr0gram weiß das diese exisitieren müssen die einmal benannt werden
void CheckVoltage();          // void ist ein Funktionstyp der keine Daten zurückgibt, CheckVoltage() ist der willkürliche Name den wir der Funktion geben
////////////////////////


/////SETUP///////////
void setup() {
  Serial.begin(9600);
  strip.begin();               // startet Kommunikation der oben gegründeten LED Gruppe "strip"
}
/////////////////////


//////LOOP///////////
void loop() {
            
                                        ///NICHT ANFASSEN!! AKKU SCHUTZ/////
  CheckVoltage();                       //läuft durch die Funktion "CheckVoltage" und aktualisiert damit die "Voltage" Variable
  if(Voltage < 3.7){                    // Wenn die Spannung unter 3.7V liegt füre folgenden Code aus
    strip.setPixelColor(0, 100, 0, 0);  // setzt die 0te LED auf 100Rot 0Grün 0Blau (Farbwerte von 0 bis 255)
    strip.setPixelColor(1, 100, 0, 0);  // das gleiche für 1te LED
    strip.show();                       // updated die realen LEDs
  }
  else{
                                        ////AB HIER DARFST DU WIEDER////////

    for(int i = 0; i < 255; i++){             //eine schleife die 255 mal durchläuft und dabei jedesmal die HilfsVariable "i" um 1 erhöht
      strip.setPixelColor(0, i, 255-1*i, 0);  // zählt den roten wert hoch den günen runter
      strip.setPixelColor(1, 0, i, 255-1*i);  // zählt den grünen hoch den blauen runter
      strip.show(); 
      delay(10);                              // macht eine 50 millisekunden Pause damit alles besser sichtbar ist
      Serial.println(i);                      // hier kannst du i wieder im Plotter beobachten
    }                                         // schreib doch ein Pr0gramm das abhängig von den Lichtensoren die Farbe verändert :D

  }
}
////////////////////


//////FUNKTIONEN//////              // hier werden unsere eigenen Funktionen geschrieben
void CheckVoltage(){                // das ist das Pr0gramm vom vorherigen Versuch
  Voltage = analogRead(VoltagePin);
  Voltage = map(Voltage, 0, 1024, 0, 500);
  Voltage = Voltage/100;
}
//////////////////////
