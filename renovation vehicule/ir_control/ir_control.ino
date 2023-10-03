/**
 * e-mail : openprogramming23@gmail.com
 * gitHub : https://github.com/RS-malik-el
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 18/09/2023
 * 
 * @Board : Arduino Nano
 * 
*/
#ifndef __AVR_ATmega328P__
  #error "Selectionner la carte Arduino Nano : Programme tester une carte arduino Nano"
#endif

// Insertion bibliothèque
#define DECODE_NEC // Protocole utilisé
#include <IRremote.h>
#include <Servo.h>

#define PIN_IR_REC 2 // Pin reception infrarouge
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

#define _REPEAT  0X1 // Valeur flag de répétition (appui maintenu du bouton)
#define CMD_0   0xE916FF00 // Touche 0 de la télécommande
#define CMD_1   0xF30CFF00 // Touche 1 de la télécommande
#define CMD_2   0xE718FF00 // Touche 2 de la télécommande
#define CMD_3   0xA15EFF00 // Touche 3 de la télécommande
#define CMD_4   0xF708FF00 // Touche 4 de la télécommande
#define CMD_5   0xE31CFF00 // Touche 5 de la télécommande
#define CMD_6   0xA55AFF00 // Touche 6 de la télécommande
#define CMD_7   0xBD42FF00 // Touche 7 de la télécommande
#define CMD_8   0xAD52FF00 // Touche 8 de la télécommande
#define CMD_9   0xB54AFF00 // Touche 9 de la télécommande
#define CMD_VG  0xBB44FF00 // Touche <<< de la télécommande
#define CMD_VD  0xBF40FF00 // Touche >>> de la télécommande
#define CMD_VN  0xBC43FF00 // Touche play/pause de la télécommande
#define CMD_AR  0xBA45FF00 // Touche CH- de la télécommande
#define CMD_AV  0xB847FF00 // Touche CH+ de la télécommande
#define CMD_ST  0xB946FF00 // Touche CH de la télécommande


unsigned long init_ts = millis();
const int timeout_blink = 250;
uint32_t valCmd = 0 ; // Stocke la valeur du signal reçu
bool blink_r = false;
bool blink_g = false;
bool blink_b = false;

Servo virage;

void ir_reception(void);
bool detection_obstacle(const uint8_t trig, const uint8_t echo);
bool obstacle_f(void);
bool obstacle_b(void);
void move_f(void);
void move_b(void);
void stop(void);

void all_led_off(void);
void led_av_on(void);
void led_av_off(bool s=false);

void rbg_off(bool s=false);
void rgb_rouge(bool s=false);
void rgb_vert(bool s=false);
void rgb_bleu(bool s=false);

void noBlink(void);
void blink_rgb_rouge(void);
void blink_rgb_vert(void);
void blink_rgb_bleu(void);

void setup() {
  Serial.begin(9600);

  IrReceiver.setReceivePin(PIN_IR_REC);
  IrReceiver.start();
  printActiveIRProtocols(&Serial);
  Serial.println(" ");

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
  ir_reception();
  blink_rgb_rouge();
  blink_rgb_vert();
  blink_rgb_bleu();

  if(obstacle_b()==true or obstacle_f()==true){
    stop();
  }
}


void ir_reception(void){
  if(IrReceiver.decode() == true){
    // reception de potentiel bruit ou d'appuis maintenu du bouton
    if (IrReceiver.decodedIRData.protocol == UNKNOWN || IrReceiver.decodedIRData.flags == _REPEAT){
      IrReceiver.resume(); // Préparation pour une nouvelle réception
      return; // fin 
    }
    valCmd = IrReceiver.decodedIRData.decodedRawData; // Stockage de la valeur du signal reçu
    // Affichage des résulats dans le moniteur série
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume(); 

    all_led_off();
    led_av_on();
    led_av_off();
    rbg_off();
    rgb_rouge();
    rgb_vert();
    rgb_bleu();

    if (valCmd == CMD_7){
      noBlink();
      blink_r = true;
    }
    else if (valCmd == CMD_8){
      noBlink();
      blink_g = true;
    }
    else if (valCmd == CMD_9){
      noBlink();
      blink_b = true;
    }
    else if (valCmd == CMD_VG){virage.write(ANG_GAUCHE);}
    else if (valCmd == CMD_VD){virage.write(ANG_DROITE);}
    else if (valCmd == CMD_VN){virage.write(ANG_NEUTRE);}
    else if (valCmd == CMD_AV){move_f();}
    else if (valCmd == CMD_AR){move_b();}
    else if (valCmd == CMD_ST){stop();}
  }
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
}


void move_b(void){
  Serial.println("marche en arrière");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  blink_b = true;
  blink_rgb_bleu();
}

void stop(void){
  Serial.println("marche : stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  noBlink();
  rgb_rouge(true);
}

void all_led_off(void){
  if (valCmd == CMD_0){
    led_av_off(true);
    rbg_off(true);
    noBlink();
  }
}

void led_av_on(void){
  if (valCmd == CMD_1){
    digitalWrite(LED_AV_G, HIGH);
    digitalWrite(LED_AV_D, HIGH);
  }
}

void led_av_off(bool s=false){
  if (valCmd == CMD_2 or s == true){
    digitalWrite(LED_AV_G, LOW);
    digitalWrite(LED_AV_D, LOW);
  }
}

void rbg_off(bool s=false){
   if (valCmd == CMD_3 or s == true){
    
    if(valCmd == CMD_3){noBlink();}

    digitalWrite(LED_RGB_AR_GR, LOW);
    digitalWrite(LED_RGB_AR_GG, LOW);
    digitalWrite(LED_RGB_AR_GB, LOW);

    digitalWrite(LED_RGB_AR_DR, LOW);
    digitalWrite(LED_RGB_AR_DG, LOW);
    digitalWrite(LED_RGB_AR_DB, LOW);
  }
}

void rgb_rouge(bool s=false){
  if (valCmd == CMD_4 or s == true){

    if(valCmd == CMD_4){noBlink();}

    digitalWrite(LED_RGB_AR_GR, HIGH);
    digitalWrite(LED_RGB_AR_GG, LOW);
    digitalWrite(LED_RGB_AR_GB, LOW);

    digitalWrite(LED_RGB_AR_DR, HIGH);
    digitalWrite(LED_RGB_AR_DG, LOW);
    digitalWrite(LED_RGB_AR_DB, LOW);
  }
}

void rgb_vert(bool s=false){
  if (valCmd == CMD_5 or s == true){

  if(valCmd == CMD_5){noBlink();}

    digitalWrite(LED_RGB_AR_GR, LOW);
    digitalWrite(LED_RGB_AR_GG, HIGH);
    digitalWrite(LED_RGB_AR_GB, LOW);

    digitalWrite(LED_RGB_AR_DR, LOW);
    digitalWrite(LED_RGB_AR_DG, HIGH);
    digitalWrite(LED_RGB_AR_DB, LOW);
  }
}

void rgb_bleu(bool s=false){
   if (valCmd == CMD_6 or s == true){

    if(valCmd == CMD_6){noBlink();}

    digitalWrite(LED_RGB_AR_GR, LOW);
    digitalWrite(LED_RGB_AR_GG, LOW);
    digitalWrite(LED_RGB_AR_GB, HIGH);

    digitalWrite(LED_RGB_AR_DR, LOW);
    digitalWrite(LED_RGB_AR_DG, LOW);
    digitalWrite(LED_RGB_AR_DB, HIGH);
  }
}

void noBlink(void){
  blink_r = false;
  blink_g = false;
  blink_b = false;
}

void blink_rgb_rouge(void){
  static bool state_1 = false;
  
  if (blink_r == true){
    if((millis()-init_ts) >= timeout_blink){
      state_1 = not state_1;
      if (state_1==true)
        rgb_rouge(true);
      else
        rbg_off(true);
      init_ts = millis();
    }
  }
}

void blink_rgb_vert(void){
  static bool state_2 = false;

  if (blink_g == true){
    if((millis()-init_ts) >= timeout_blink){
      state_2 = not state_2;
      if (state_2==true)
        rgb_vert(true);
      else
        rbg_off(true);
      init_ts = millis();
    }
  }
}

void blink_rgb_bleu(void){
  static bool state_3 = false;
  
  if (blink_b == true){
    if((millis()-init_ts) >= timeout_blink){
      state_3 = not state_3;
      if (state_3==true)
        rgb_bleu(true);
      else
        rbg_off(true);
      init_ts = millis();
    }
  }
}
