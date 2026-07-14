// AeroPuff
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT , &Wire , OLED_RESET)

//On va definiiir les broches 
const int BTN_NEXT = 14;
const int BTN_PREV = 12;
const int DHT_PIN = 4;

//Laaaa machine d etat 
enum Mode `{ ACCEUIL , CLIMAT_INTERIEUR , CONSEIL };
Mode modeActuel = ACCEUIL;

//Variableeee
float tempSimulee = 22.5;
float humSimulee = 55.0;

void setup() {
  Serial.begin(115200);

pinMode(BTN_NEXT, INPUT_PULLUP);
pinMode(BTN_PREV, INPUT_PULLUP);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Erreur : Ecran OLED non detecte"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Initialisation...");
  display.display();
  delay(1000);
}

void loop() {
  // Lecture non-bloquante des boutons (State Machine Inputs)
  if (digitalRead(BTN_NEXT) == LOW) {
    delay(200); // Anti-rebond
    if (modeActuel == ACCUEIL) modeActuel = CLIMAT_INTERIEUR;
    else if (modeActuel == CLIMAT_INTERIEUR) modeActuel = CONSEIL;
    else modeActuel = ACCUEIL;
  }
  
  if (digitalRead(BTN_PREV) == LOW) {
    delay(200); // Anti-rebond
    if (modeActuel == ACCUEIL) modeActuel = CONSEIL;
    else if (modeActuel == CLIMAT_INTERIEUR) modeActuel = ACCUEIL;
    else modeActuel = CLIMAT_INTERIEUR;
  }

//Mise a jour de mon affichage 
display.clearDisplay();
display.setCursor( 0 , 0 );

switch(modeActuel) {
 case ACCEUIL:
  display.setTextSize(1);
  display.println("=====================================");
  display.println("        Welcome to AEROPUF !         ");
  display.println("=====================================");
  display.println("\n Click on any button  ");
  display.println("  to naviguate ...  ");
 
 case CLIMAT_INTERIEUR:
  display.setTextSize(1);
  display.println("======== ANALYSE CLIMAT =========");
  display.println(" ");
  if (tempSimulee > 24.0) {
  display.println("Statut : So Hot !");
  display.println("Advice: Open the   ");
  display.println("  window  ...  ")
  } else {
  display.println("Statut : Comfortable");
  display.println("Advice: Everything is OK!");   
  }
  break;
 }

display.display();
delay(50);
}







}











}