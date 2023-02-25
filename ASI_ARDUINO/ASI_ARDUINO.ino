/**
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : RACHEL SYSTEME / OpenProgramming
 * DATE : 12/02/2023
 * 
 * @Board : Arduino Uno
 *
 * Ce programme permet d'alimenter un système ASI à partir d'une source PV et EOLIEN
 * le basculement d'une source à l'autre se fait grâce à un relais. Un bouton poussoir
 * permet d'allumer ou pas la pompe connecté au système ASI. Les Leds sont utilisées
 * comme témoin, un bipeur se déclenche en cas de non-détection de source d'alimentation. 
*/
// Pins utilisés
#define PIN_SRC_EOLIEN 2 // Détecte la présence de courant sur la source éolien
#define PIN_SRC_PV 	   3 // Détecte la présence de courant sur la source PV
#define PIN_RELAIS 	   4 // Relais de basculement de source d'alimention
#define LED_SRC_EOLIEN 5 // Led témoin : indique que la source EOLIEN est active
#define LED_SRC_PV 	   6 //	Led témoin : indique que la source PV est active
#define LED_MOTEUR 	   7 //	Led témoin : indique que le moteur est active
#define PIN_MOTEUR     8 // Permet le contrôle du moteur
#define BTN            9 // Bouton poussoir pour l'activation ou pas du moteur
#define BIPEUR        10 // Alarme indiquant la non présence de source d'alimentation 


#define SRC_PV 	LOW // Etat du relais en fonction de la sélection de la source
#define FREQ 	200 // Fréquence du son de l'alarme

// Prototypes des fonctions
void selectionSrc(void); // Permet la sélection de la source d'alimentation
void gestionMoteur(void); // Permet le contrôle du moteur


// Programme initial
void setup(){
	// Configuration des pins
	pinMode(PIN_SRC_EOLIEN, INPUT);
	pinMode(PIN_SRC_PV, INPUT);
	pinMode(BTN, INPUT_PULLUP);
	pinMode(PIN_RELAIS, OUTPUT);
	pinMode(LED_SRC_EOLIEN, OUTPUT);
	pinMode(LED_SRC_PV, OUTPUT);
	pinMode(LED_MOTEUR, OUTPUT);
	pinMode(PIN_MOTEUR, OUTPUT);
	pinMode(BIPEUR, OUTPUT);

	selectionSrc(); // Appel à la fonction
}

// Programme principal
void loop(){
	selectionSrc();
	gestionMoteur();
}


// Choix de la sélection de la source
void selectionSrc(){
	// Source PV
	if(digitalRead(PIN_SRC_PV) == true){
		digitalWrite(LED_SRC_PV, HIGH);// Led PV ON
		digitalWrite(LED_SRC_EOLIEN, LOW);// Led EOLIEN OFF
		digitalWrite(PIN_RELAIS, SRC_PV);
		noTone(BIPEUR); // Arrêt alarme
	}
	// Source EOLIEN
	else if(digitalRead(PIN_SRC_PV)==false and digitalRead(PIN_SRC_EOLIEN)==true){
		digitalWrite(LED_SRC_PV, LOW);// Led PV OFF
		digitalWrite(LED_SRC_EOLIEN, HIGH);// Led EOLIEN ON
		digitalWrite(PIN_RELAIS, not SRC_PV);
		noTone(BIPEUR); // Arrêt alarme
	}
	// Aucune source active
	else{
		digitalWrite(LED_SRC_PV, LOW);// Led PV OFF
		digitalWrite(LED_SRC_EOLIEN, LOW);// Led EOLIEN OFF
		tone(BIPEUR, FREQ); // Déclanchement de l'alarme
	}
}// fin


// Gestion du moteur
void gestionMoteur(){
	static bool etatMoteur = false; // Variable de contrôle
	
	// Lecture du bouton poussoir
	if (not digitalRead(BTN) == true){
		delay(100);// pause
		if (not digitalRead(BTN) == true){return;}
		etatMoteur = not etatMoteur;
	}

	digitalWrite(PIN_MOTEUR, etatMoteur); // ON / OFF moteur
	digitalWrite(LED_MOTEUR, etatMoteur); // ON / OFF led
}