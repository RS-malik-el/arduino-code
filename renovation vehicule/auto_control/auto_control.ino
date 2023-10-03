/**
 * e-mail : openprogramming23@gmail.com
 * gitHub : https://github.com/RS-malik-el
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 14/09/2023
 * 
 * @Board : Arduino Nano
 * 
*/
#ifndef __AVR_ATmega328P__
  #error "Selectionner la carte Arduino Nano : Programme tester une carte arduino Nano"
#endif

// Insertion bibliothèque
#include <Servo.h>

#define PIN_SERVO 6
#define BUZZER 5
// Leds avant
#define LED_AV_G 3
#define LED_AV_D 4
// Led rgb arrière droite
#define LED_RGB_AR_DR 7
#define LED_RGB_AR_DG 8
#define LED_RGB_AR_DB 11
// Led rgb arrière gauche
#define LED_RGB_AR_GR A0
#define LED_RGB_AR_GG 13
#define LED_RGB_AR_GB 12
// Pins capteurs ultrason
#define TRIG_AV A1
#define ECHO_AV A2
#define TRIG_AR A3
#define ECHO_AR A4
// Pins drivers moteur arrière
#define IN1 A5
#define IN2 A6
// Pins hc-05
#define TX 10 // Connecté au rx du hc-05
#define RX 9  // Connecté au tx du hc-05

// Angles de guidage de direction du servomoteur
#define ANG_NEUTRE 95
#define ANG_GAUCHE 75
#define ANG_DROITE 115

#define DISTANCE 20 // Distance de détection
#define FREQ  150

Servo virage;

bool detection_obstacle(const uint8_t trig, const uint8_t echo);
bool obstacle_f(void);
bool obstacle_b(void);
void move_f(void);
void move_b(void);
void stop(void);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A7));

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(LED_AV_G, OUTPUT);
  pinMode(LED_AV_D, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(TRIG_AV, OUTPUT);
  pinMode(ECHO_AV, INPUT);
  pinMode(TRIG_AR, OUTPUT);
  pinMode(ECHO_AR, INPUT);

  pinMode(LED_RGB_AR_DR, OUTPUT);
  pinMode(LED_RGB_AR_DG, OUTPUT);
  pinMode(LED_RGB_AR_DB, OUTPUT);

  pinMode(LED_RGB_AR_GR, OUTPUT);
  pinMode(LED_RGB_AR_GG, OUTPUT);
  pinMode(LED_RGB_AR_GB, OUTPUT);

  virage.attach(PIN_SERVO);
  virage.write(ANG_NEUTRE);
}

void loop() {
  // Marche en avant
  while(obstacle_f() == false){move_f();}
  // Marche en arrière
  if(obstacle_b() == false){
    unsigned long init_t = millis();
    unsigned long init_ts = millis();
    const int timeout = 5000;
    const int timeout_buzzer = 200;
    bool sens = random(0,2); // sens d'orientation des roues

    while(obstacle_b() == false){
      move_b();
      // sens d'orientation des roues
      if(sens == 1){virage.write(ANG_GAUCHE);}
      else{virage.write(ANG_DROITE);}
      
      if((millis()-init_ts) >= timeout_buzzer){
        tone(BUZZER,FREQ,(int)timeout_buzzer/2);
        init_ts = millis();
      }
      
      if((millis()-init_t) >= timeout){break;}
    }
    virage.write(ANG_NEUTRE);
  }

  stop();
  delay(3000);
}


bool detection_obstacle(const uint8_t trig, const uint8_t echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duree = pulseIn(echo, HIGH);
  unsigned int distance = duree*0.0343 / 2;

  if(DISTANCE >= distance)
    return true;
  else
    return false;
}

bool obstacle_f(void){
  return detection_obstacle(TRIG_AV, ECHO_AV);
}

bool obstacle_b(void){
  return detection_obstacle(TRIG_AR, ECHO_AR);
}

void move_f(void){
  Serial.println("marche en avant");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(LED_AV_G, HIGH);
  digitalWrite(LED_AV_D, HIGH);

  digitalWrite(LED_RGB_AR_GR, LOW);
  digitalWrite(LED_RGB_AR_GG, HIGH);
  digitalWrite(LED_RGB_AR_GB, LOW);

  digitalWrite(LED_RGB_AR_DR, LOW);
  digitalWrite(LED_RGB_AR_DG, HIGH);
  digitalWrite(LED_RGB_AR_DB, LOW);
}


void move_b(void){
  Serial.println("marche en arrière");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(LED_AV_G, HIGH);
  digitalWrite(LED_AV_D, HIGH);

  digitalWrite(LED_RGB_AR_GR, LOW);
  digitalWrite(LED_RGB_AR_GG, LOW);
  digitalWrite(LED_RGB_AR_GB, HIGH);

  digitalWrite(LED_RGB_AR_DR, LOW);
  digitalWrite(LED_RGB_AR_DG, LOW);
  digitalWrite(LED_RGB_AR_DB, HIGH);
}

void stop(void){
  Serial.println("marche : stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(LED_AV_G, LOW);
  digitalWrite(LED_AV_D, LOW);

  digitalWrite(LED_RGB_AR_GR, HIGH);
  digitalWrite(LED_RGB_AR_GG, LOW);
  digitalWrite(LED_RGB_AR_GB, LOW);

  digitalWrite(LED_RGB_AR_DR, HIGH);
  digitalWrite(LED_RGB_AR_DG, LOW);
  digitalWrite(LED_RGB_AR_DB, LOW);
}