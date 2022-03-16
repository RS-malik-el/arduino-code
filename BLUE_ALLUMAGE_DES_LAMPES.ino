/*
	Ce programme permet de controler l'allumage et l'extinction
  des lampes depuis son téléphone via le module bluetooth
	
 *** AUTEUR : RACHEl SYSTEME
 *** DATE 	: 11 / 03 / 2022
 *** YOUTUBE: 

*/

#include <SoftwareSerial.h>

#define _RX 10
#define _TX 11
#define _LAMPE_1 2
#define _LAMPE_2 3

// Création de l'objet SoftwareSerial
SoftwareSerial mySerial(_RX,_TX);
String reception = "";

void setup(){
  // Initialisation de la communication Série et SoftwareSerial
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(_LAMPE_1,OUTPUT);
  pinMode(_LAMPE_2,OUTPUT);
  digitalWrite(_LAMPE_1,HIGH);
  digitalWrite(_LAMPE_2,HIGH);

  Serial.println("Attente reception : "); 
}

void loop(){
  // Réception des caractères via le module bluetooth
	if (mySerial.available())
    reception += (char) mySerial.read();
  
  // Allumage ou extinction des lampes
 	if (reception == "ON_1")
 	{
    affiche();
    digitalWrite(_LAMPE_1,LOW); 
 	}  
   if (reception == "ON_2")
  {
    affiche();
    digitalWrite(_LAMPE_2,LOW); 
  }
  if (reception == "OFF_1")
  {
    affiche();
    digitalWrite(_LAMPE_1,HIGH); 
  }
  if (reception == "OFF_2")
  {
    affiche();
    digitalWrite(_LAMPE_2,HIGH); 
  }

  if(reception.length() > 5)
    reception = "";
}

void affiche(){
  Serial.println(reception);
  reception = "";
}
