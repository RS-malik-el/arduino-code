/*
  DATE  : 14/01/2022
  Admin : RACHEL SYSTEME

  Ce programme permet de controler l'allumage de deux leds
  via le moniteur série arduino ou avec le module pyserial
  de python.
*/

//pins utilisé
byte pinLed_1 = 2;
byte pinLed_2 = 3;

bool etat = false;

//Temps initial
unsigned long init_time = millis();

int attente = 250; //Durée de clignotement

String instruction = ""; 

void setup(){
  //Initialisation de la communication série
  Serial.begin(9600);

  //Définition des pins OUTPUT
  pinMode(pinLed_1,OUTPUT);
  pinMode(pinLed_2,OUTPUT);
}

void loop(){

  //mise a jour de la variable etat
  if ((millis() - init_time) > attente){
    etat = !etat;
    init_time = millis();
    }

  //Reception des données via le port série
  if (Serial.available() > 0){
    instruction = Serial.readStringUntil('\n');
    }

  // Décodage et exécution des instructions
  if (instruction == "all on"){
    digitalWrite(pinLed_1,HIGH);
    digitalWrite(pinLed_2,HIGH);
    }
  else if (instruction == "led 1 on"){
    digitalWrite(pinLed_1,HIGH);
    digitalWrite(pinLed_2,LOW);
    }
  else if (instruction == "led 2 on"){
    digitalWrite(pinLed_1,LOW);
    digitalWrite(pinLed_2,HIGH);
    }
  else if (instruction == "blink"){
    digitalWrite(pinLed_1,etat);
    digitalWrite(pinLed_2,etat);
    }
  else{
    digitalWrite(pinLed_1,LOW);
    digitalWrite(pinLed_2,LOW);
    }
}
