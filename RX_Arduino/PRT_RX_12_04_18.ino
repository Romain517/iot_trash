//SOLUTION BASIQUE QUI MARCHE


#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11); // 10 relié au TX, 11 relié au RX du module LoRa
int SerialValue;
String phrase;

void setup(){
 Serial.begin(9600);
 //while (!Serial){}
 mySerial.begin(9600);
}

void loop(){
 if (mySerial.available()){
 SerialValue = mySerial.read();
 //Serial.print(SerialValue);

 phrase=SerialValue;
 

Serial.print("#S|SEND|[");
Serial.print(SerialValue);
Serial.println(";]#");
 

delay(1000); 
 }
 //if (Serial.available())
 //mySerial.write(Serial.read());
}
