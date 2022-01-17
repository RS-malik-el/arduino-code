//pins boutons poussoir
const byte s_white = 2;
const byte s_red = 3;
const byte s_blue = 4;

//pins connexion leds
const byte yellow_led = 5;
const byte blue_led = 6;
const byte red_led = 7;

// etat des leds
bool etat_yellow_led = false;
bool etat_red_led = false;
bool etat_blue_led = false;

void setup() {
Serial.begin(9600);
  for(byte i = 2; i <= 4; i++ )
  {
    Serial.println(i);
    pinMode(i, INPUT_PULLUP);
  }

  for(byte i = 5; i <= 7; i++ )
  {
    Serial.println(i);
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);
  }

}

void loop() {
bool appui_1, appui_2, appui_3;

appui_1 = !digitalRead(s_white);
appui_2 = !digitalRead(s_red);
appui_3 = !digitalRead(s_blue);

// changement de l'etat de la led a chaque appui
  if(appui_1)
  {
    if(etat_yellow_led == true)
      etat_yellow_led = false;
    else
      etat_yellow_led = true;
  }

  if(appui_2)
  {
    if(etat_red_led == true)
      etat_red_led = false;
    else
      etat_red_led = true;
  }

  if(appui_3)
    {
      if(etat_blue_led == true)
      etat_blue_led = false;
      else
        etat_blue_led = true;
    }


digitalWrite(yellow_led, etat_yellow_led);
digitalWrite(blue_led, etat_red_led);
digitalWrite(red_led, etat_blue_led);

delay(200);
}
