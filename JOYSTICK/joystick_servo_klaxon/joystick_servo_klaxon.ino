/**
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : RACHEL SYSTEME / OpenProgramming
 * DATE : 23/02/2023
 * 
 * @Board : Arduino
 * 
 * Joystick, bipeur et servomoteurs
 * */

#include <Servo.h>

// Pins Joystick
#define VRx A0
#define VRy A1
#define SW  2

// Pin Buzzer
#define BIPEUR 3 // Connecter au pin 3
#define FREQ  200
#define DUREE 250

//Pins servomoteur
#define PIN_SERVO_RX 4
#define PIN_SERVO_RY 5

// Objects de type Servo
Servo servoRx;
Servo servoRy;

// Variable de controle
int angleForRx = 90;
int angleForRy = 90;

void setup(){
	Serial.begin(115200);
	// Configuration des pins
	pinMode(VRx, INPUT);
	pinMode(VRy, INPUT);
	pinMode(SW, INPUT_PULLUP);
	pinMode(BIPEUR, OUTPUT);
	// Configuration servomoteurs
	servoRx.attach(PIN_SERVO_RX);
	servoRy.attach(PIN_SERVO_RY);
	servoRx.write(angleForRx);
	servoRy.write(angleForRy);
}


void loop(){
	// Klaxon
	if(not digitalRead(SW)==true){
		delay(50);
		if(not digitalRead(SW)==true){return;}
		tone(BIPEUR,FREQ,DUREE);
	}

	// L'angle suivant Rx 
	angleForRx = map(analogRead(VRx),0,1023,180,0);
	// L'angle suivant Ry 
	angleForRy = map(analogRead(VRy),1023,0,180,0);

	// Affichage sur le moniteur série
	Serial.println("Rx : "+String(angleForRx)+"°");
	Serial.println("Ry : "+String(angleForRy)+"°");

	// Positionnement des servomoteurs
	servoRx.write(angleForRx);
	servoRy.write(angleForRy);
}