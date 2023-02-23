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
 * Tester son joystick 
 * */

// Pins Joystick
#define VRx A0
#define VRy A1
#define SW  2

void setup(){
	Serial.begin(115200);
	// Configuration des pins
	pinMode(VRx, INPUT);
	pinMode(VRy, INPUT);
	pinMode(SW, INPUT_PULLUP);
}

void loop(){
	Serial.println("Rx : "+String(analogRead(VRx)));
	Serial.println("Ry : "+String(analogRead(VRy)));
	Serial.println("SW : "+String(not digitalRead(SW)));
	Serial.println("");
	delay(1000);
}