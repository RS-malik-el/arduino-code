/**
 * @email : openprogramming23@gmail.com
 * @Auteur : Exaucé KIMBEMBE
 * @Date : 24/10/2023
 * 
 *@Board : ARDUINO 
 * 
*/

// Vérification de la carte Arduino 
#ifndef __AVR__
	#error "Ce programme a été tester sur une carte Arduino"
#endif

#define LCD_I2C true
#define COL 16 // Nombre de colonne de l'écran
#define ROW 2  // Nombre de ligne de l'écran

#include "CheapStepper.h"

// Déclaration de l'objet LiquidCrystal
#if LCD_I2C == true
	#include <LiquidCrystal_I2C.h>
	LiquidCrystal_I2C lcd(0x27,COL,ROW);
	CheapStepper moteur(6,7,8,9); // Object CheapStepper
#else
	#include <LiquidCrystal.h>

	#define RS 6
	#define E  7
	#define D4 8
	#define D5 9
	#define D6 10
	#define D7 11
	
	LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
	CheapStepper moteur(12,13,22,23);// Object CheapStepper
#endif

// Pins utilisés
#define PIN_BNT_O_F  2 // Bouton marche/arrêt
#define PIN_BNT_OK   3 // Bouton OK
#define PIN_BNT_UP   4 // Bouton up 
#define PIN_BNT_DOWN 5 // Buton  down

// Menu de demarrage
#define ACCEUIL_l1	"    WELCOME     "
#define ACCEUIL_l2 	"OPENPROGRAMMING "

// Menu de selection
#define MENU_1 	"-> Get speed    "
#define MENU_2 	"-> Set speed    "
#define MENU_3  "-> Get direction"
#define MENU_4  "-> Set direction"

String tab_menu[4]={ MENU_1, MENU_2, MENU_3, MENU_4};

// Paramètres du moteur pas à pas
#define VITESSE_MAX 24  //  120tr/min vitesse du moteur avec couple faible (Vitesse de configuration)
#define VITESSE_MIN 6   
#define PAS         4096// Nombre de pas pour effectuer un tour complet

uint8_t vitesse = VITESSE_MAX;   // vitesse de rotation des tubes

bool state_moteur = false; // Indique si le moteur est en marche ou pas
bool sens		  = true;  // sens par défaut
uint8_t index_option = 0;  // Index de l'option a afficher
uint8_t tab_af[2] = {0,1}; // Tableau contenant l'index du menu à afficher
uint8_t ligne_cursor = 0;  // Position du curseur sur l'ecran 

#define DELAY 3000 // Pause système setup() (ms)

void menu(void);
bool detectionAppui(uint8_t pin);
void gestionBouton_O_F(void); // Utiliser dans l'intérruption
void gestionBouton_OK(void);
void gestionBouton_UP(void);
void gestionBouton_DOWN(void);
void revolution(void); // Permet la rotation du moteur
void setSpeed(void);

void setup(){
	Serial.begin(115200);//Initialisation de la communication série
	// Configuration de l'ecran lcd
	#if LCD_I2C == true
		lcd.init();
		lcd.backlight();
	#else
		lcd.begin(COL,ROW);
	#endif

	lcd.blink();
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(ACCEUIL_l1);
	lcd.setCursor(0,1);
	lcd.print(ACCEUIL_l2);	

	// Configuration des boutons de réglage
	pinMode(PIN_BNT_O_F, INPUT_PULLUP);
	pinMode(PIN_BNT_OK,  INPUT_PULLUP);
	pinMode(PIN_BNT_UP,  INPUT_PULLUP);
	pinMode(PIN_BNT_DOWN,INPUT_PULLUP);

	// Configuration du moteur pas à pas
	moteur.setRpm(vitesse);
	moteur.setTotalSteps(PAS);

	// Configuration de l'intérruption de changement d'état du moteur
	attachInterrupt(digitalPinToInterrupt(PIN_BNT_O_F), gestionBouton_O_F, FALLING);

	delay(DELAY);

	lcd.setCursor(0,0);
	lcd.print(tab_menu[tab_af[0]]);
	lcd.setCursor(0,1);
	lcd.print(tab_menu[tab_af[1]]);
}

void loop(){
	// Mise en marche du moteur
	if(state_moteur==true){
		Serial.println("moteur en marche");
		revolution();
	}
	else{
		menu();// Affichage du menu
		gestionBouton_OK();//Permet de lancer l"option selectionner
		gestionBouton_DOWN();
		gestionBouton_UP();
	}
}

//---------------- Gestion des boutons
void gestionBouton_O_F(void){
	// changement d'état de la variable
	state_moteur = not state_moteur;
	// Arrêt du moteur
	if(state_moteur==false){
		Serial.println("moteur off");
		moteur.stop();
	}
}

// Permet de lancer l"option selectionner
void gestionBouton_OK(void){
	if (detectionAppui(PIN_BNT_OK)==true){
		Serial.println("Le bouton ok est cliqué");

		// Affiche la vitesse actuelle
		if(index_option==0){
			lcd.setCursor(0,0);
			lcd.print(" Current speed  ");
			lcd.setCursor(0,1);
			lcd.print("N = "+String(moteur.getRpm())+" tr/min     ");
			// Appuie sur le bouton OK pour sortir
			while(true){
				if (detectionAppui(PIN_BNT_OK)==true){break;}
			}
		}
		// Modifie la vitesse actuelle
		else if(index_option==1){setSpeed();}
		// Affiche le sens de rotation du moteur
		else if(index_option==2){
			getDirection();
			// Appuie sur le bouton OK pour sortir
			while(true){
				if (detectionAppui(PIN_BNT_OK)==true){break;}
			}
		}
		// Modifie le sens de rotation du moteur
		else if(index_option==3){
			sens = not sens; // Modifie le sens de rotation
			getDirection();
			delay((int)DELAY/2);
		}
	}
}

// Chaque appui permet de décrémenté la variable pour aller ---> 0 (vers le bas)
void gestionBouton_DOWN(void){
	if (detectionAppui(PIN_BNT_UP)==true){
		if(index_option >= 1){
			--index_option;
			Serial.println(index_option);		
		}
	}
}

// Chaque appui permet d'incrémenté la variable pour aller ---> index + 1 (vers le haut)
void gestionBouton_UP(void){
	if (detectionAppui(PIN_BNT_DOWN)==true){
		if(index_option < ((int)(sizeof(tab_menu)/sizeof(tab_menu[0]))) - 1){
			++index_option;
			Serial.println(index_option);
		}
	}
}

// Fonction permettant de détecter un appui sur un bouton
bool detectionAppui(uint8_t pin){
	if(not digitalRead(pin)==true){
		delay(100);// Attente après chaque appui
		while(not digitalRead(pin)==true){}// Si appui maintenant on ne fait rien
		if(not digitalRead(pin)==false){
			return true;
		}
	}
	return false;
}

// Affiche le menu sur l'écran lcd en fonction 
void menu(void){
	static unsigned long _init = millis();

	// Mise à jour des index dans le tableau a afficher
	if(index_option==0 or index_option==1){
		tab_af[0] = 0;
		tab_af[1] = 1;
	}
	else if(index_option==2 or index_option==3){
		tab_af[0] = 2;
		tab_af[1] = 3;
	}
	
	// Affiche le message à l'écran
	if((millis() - _init) >= 500){
		lcd.setCursor(0,0);
		lcd.print(tab_menu[tab_af[0]]);
		lcd.setCursor(0,1);
		lcd.print(tab_menu[tab_af[1]]);
		
		_init = millis();// initialisation du temps
	}

	// Indique la ligne active sur l'écran
	if(index_option==0 or index_option==2)
		lcd.setCursor(1,0);
	else
		lcd.setCursor(1,1);
}

// Permet la rotation du moteur
void revolution(void){
	
	if(moteur.getStepsLeft()==0){
		moteur.newMove(sens,PAS);
	}
	moteur.run();
}

// Permet de définir la vitesse de rotation du moteur
void setSpeed(void){
	unsigned long _init = millis();

	lcd.setCursor(0,0);
	lcd.print("Regl -> Vitesse ");
	
	while(true){ 
		if(detectionAppui(PIN_BNT_UP)==true){
			if(vitesse < VITESSE_MAX)
			 ++vitesse;
		}
		if(detectionAppui(PIN_BNT_DOWN)==true){
			if(vitesse > VITESSE_MIN)
			 --vitesse;
		}

		if((millis() - _init) >= 500){
			lcd.setCursor(0,1);
			lcd.print("N = "+String(vitesse)+" tr/min    ");
			_init = millis();// initialisation du temps
		}

		if(detectionAppui(PIN_BNT_OK)==true){
			moteur.setRpm(vitesse);
			break;//Fin de la boucle avec mise a jour de la vitesse
		}
	}
}

// Affiche le sens de rotation du moteur
void getDirection(void){
	lcd.setCursor(0,0);
	lcd.print("  Current dir   ");
	lcd.setCursor(0,1);
	if(sens==true)
		lcd.print("-> Clockwise    ");
	else
		lcd.print("-> Anticlockwise");
}