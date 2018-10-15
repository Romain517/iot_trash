#include <SoftwareSerial.h>
#include "Set.h"
#include "Menu.h"

void mesure(float *);

SoftwareSerial mySerial(10, 11); // 10 relié au TX, 11 relié au RX du module LoRa 



/* Capteur ultrason
 *  
 *  VCC sur Arduino 5v 
 GND sur Arduino GND
 Echo sur Arduino broche 7 
 Trig sur Arduino broche 8*/
 
// Module LoRa 
//gnd SET_A and SET_B for Normal Mode (Send and Receive)



/* Database
 *  
 *  Gobetwino configuration
 *  
 *  Onglet "Commands" -> "New Command" -> "LGFIL" -> Path
 *  
 *  
 *  
 */

/* Constantes pour les broches */
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO


 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

float taux;

float lg_poubelle = 33.0; // en centimètres

 

 
/** Setup */
void setup() {
 

 /* Initialise le port série */
  Serial.begin(9600);
  mySerial.begin(9600);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
}



 
/** Programme principal */
void loop() {

  mesure(&taux);

  byte percent;
  /* Affiche le menu principal */
  percent = floor(taux);

 mySerial.write(percent);   


  //mySerial.write("2");

  delay(1000);
  
}
 
/** Fonction retournant le bouton appuyé (s’il y en a un). */
 

void mesure(float *taux){
  
    /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
//  digitalWrite(TRIGGER_PIN, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(TRIGGER_PIN, LOW);
//  
//  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
//  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);

float duration,measure;
 digitalWrite(TRIGGER_PIN, LOW); 
 delayMicroseconds(2); 

 digitalWrite(TRIGGER_PIN, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(TRIGGER_PIN, LOW);

 // Attend que la broche Echo passe au niveau HAUT 
 // retourne la durée
 duration = pulseIn(ECHO_PIN, HIGH);
 
 //Calculer la distance (en cm, basé sur la vitesse du son).
 measure = duration/58.2;

//*taux=measure;

   
  /* 3. Calcul la distance à partir du temps mesuré */
//  float distance_mm = measure / 2.0 * SOUND_SPEED;
//  float distance_m = distance_mm*1000;
//
//  //distance_m=1.2;
//
//  //dtostrf(distance_m,1, 1, dist);  
//
  //*taux = ((lg_poubelle-measure)/(lg_poubelle))*100.0;
  *taux = measure;

}







