/**
 * e-mail : openprogramming23@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 * 
 * AUTEUR : Exaucé KIMBEMBE / OpenProgramming
 * DATE : 23/08/2021
 * 
 * @Board : arduino Uno
 * 
 * Ce programme permet d'allumer de façons aléatoire les leds connectés au pins 2 à 7.
 * Ouvrez le moniteur série afin de connaitre le nombre tiré
 * 
 * Merci de bien vouloir vous abonnez à la chaîne et de la partager s'il vous plaît !!!
 * 
**/

int pin_aleatoire = 2;                    // variable de stockage du pin tiré da façon aléatoire
unsigned long temps_av_millis = millis(); // temps de réference de tirage

// prototype de la fonction
void tirage (int temps_de_tirage);

// programme initial
void setup(){
  Serial.begin(9600);                          //initialiisation de la communication sérial
  randomSeed(analogRead(A0));                  //initialisation de la série aléatoire 
  for(int i=2; i<=7; i++){pinMode(i, OUTPUT);} //pins 2 à 7 définit comme sortie
}

// programme principal
void loop() {
  tirage(150);
  digitalWrite(pin_aleatoire, HIGH);
}

/*
 * fonction qui permet de tirer un pin de façon aléatoire
 * après le temps inscrit en paramètre
 * paramètre: temps d'attende après tirage
 */
void tirage (int temps_de_tirage){
  if(millis() - temps_av_millis >= temps_de_tirage){
    pin_aleatoire = random(2,8);   // tirage aléatoire des pins entre 2 et 8 (sauf 8)
    Serial.println(pin_aleatoire); // affichage du pin tiré sur le moniteur série
    // on éteint tout
    for(int i=2; i<=7; i++){digitalWrite(i,LOW);}
    temps_av_millis = millis(); // mise à jour du temps de réference
  }
}
