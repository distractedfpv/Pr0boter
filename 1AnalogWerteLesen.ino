// In diesem ersten Programm wollen wir die Akkuspannung auslesen und am Computer wieder anzeigen
// Wenn der Roboter am Pc steckt klickst du oben links auf Upload um das Programm auf den Roboter zu laden
// Danach kannst du unter "Tools" Serial Monitor oder Serial Plotter öffnen um die Werte auslesen zu können

// Aufgrund von Hardware Toleranzen gibt es immer Abweichungen bei den Sensoren, deshalb darf man später Filter schreiben um die Sensoren anzugleichen


/////////Librarys///////////    //Librarys sind von anderen geschriebene Befehle die wir nutzen können um uns das Leben einfacher zu machen
#include <Arduino.h>            // das ist die standard Arduino Library die es ermöglicht mit den Pins an dem Arduino zu kommunizieren
#include <Servo.h>              // diese Ermöglicht eine einfache Ansteuerung von Servomotoren
#include <Adafruit_NeoPixel.h>  // diese steuert adressierbare Leds an
////////////////////////////    // nach den Librarys kannst du auch googlen um weitere Funktionen davon kennen zu lernen


//////VARIABELN//////           // Variablen speichern Werte auf die wir später wieder zugreifen können
int VoltagePin = A5;            // int steht für integer dieser kann nur ganzzahlige Werte speichern, 
                                // VoltagePin ist der Name den ich der Variable gegeben habe,
                                // A5 ist eine Variable der Arduino Library um den Analog Pin5 anzusprechen
                                // In Zukunft kann ich also den Analog Pin 5 mit "VoltagePin" ansprechen

float Voltage = 0;              // Float ist eine Variable die auch Kommazahlen speichern kann, dieser Float heißt "Voltage"
                                // Voltage hat aktuell den Wert 0
int LichtSensorL = A1;          // genau wie der "VoltagePin" der Lichtsensor Links hängt an AnalogPin1, Rechts an AnalogPin2
int LichtSensorR = A2;

int HelligkeitL;                // Zwei Variablen in denen wir die gemessenen Werte der Sensoren schreiben können
int HelligkeitR;
/////////////////////


/////SETUP///////////
void setup() {                 // Setup läuft einmal am start durch und legt Dinge für uns fest

  Serial.begin(9600);          // startet die Kommunikation über USB wie und warum ist erstmal egal

}
/////////////////////


//////LOOP///////////
void loop() {                                 // loop läuft nach dem Setup immer und immer wieder durch, hier passiert das eigentlich spannende

  Voltage = analogRead(VoltagePin);           // Wir schreiben in die Variable "Voltage" den Wert den die Funktion "analogRead" am "VoltagePin" liest
                                              // die AnalogPins lesen oder geben eine Spannung von 0 bis 5V aus in 1024 (10Bit) Schritten
 // Voltage = map(Voltage, 0, 1024, 0, 500);  // map ist eine Funktion die den Analogen Wert (0 bis 1024) auf die mögliche Spannung am Pin (000 bis 500V)/100 rechnet
                                              // map gibt nur ganze Zahlen!
 // Voltage = Voltage/100;                    // teilt den Wert durch 100 um die richtige Spannung zu lesen

  HelligkeitL = analogRead(LichtSensorL);     // Schreibt den Wert des Linken Lichtsensors (0 bis 1024) in die Variable

  Serial.print("HelligkeitL: ");              // Schreibt genau den Text in den "" über Usb
  Serial.print(HelligkeitL);                  // Schreibt den Wert der Variable daneben
  Serial.print(" HelligkeitR: ");
  Serial.print(analogRead(LichtSensorR));     // Wir können den Wert auch direkt auslesen und schreiben
  Serial.print(" Voltage: ");
  Serial.println(Voltage);                    // das .println macht nach dem schreiben einen Zeilen umbruch, das ist wichtig für den Plotter und das lesen im Monitor
}
////////////////////

//Mit "//" kannst du Zeilen auskommentieren und sehen wie sich der Wert verändert
