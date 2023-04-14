#include <LiquidCrystal.h>
#include <EEPROM.h>
#define buzzer 11
#define led_bleu  A3
#define led_rouge  A0
#define led_verte  A1
#define led_jaune  A2
#define bouton_ledBleu  7
#define bouton_ledRouge  10
#define bouton_ledVerte  9
#define bouton_ledJaune  8

LiquidCrystal lcd(1, 2, 3, 4, 5, 6);

int leds;
int etatBouton =  0;

bool continu = true;  
String simonInput;         
int niveau = 1;          
int address = 0;            
int score = 0;             

void setup() {
  pinMode(bouton_ledBleu,INPUT);
  pinMode(bouton_ledRouge,INPUT);
  pinMode(bouton_ledVerte,INPUT);
  pinMode(bouton_ledJaune,INPUT);
  
  pinMode(led_bleu, OUTPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16,2);                  
  lcd.print("niveau : " + String(niveau));
  lcd.setCursor(0,1);
  lcd.print("Score : " + String(score));   
  
  randomSeed(analogRead(A5));              
}

void loop() { 
  while(continu == true) {
    lcd.setCursor(0,0);
    lcd.print("Niveau : " + String(niveau));

    lcd.setCursor(0,1);
    lcd.print("Score: " + String(score));
    continu = manche();   
  }

  score = 0;

  while(continu == false) {
    leds = 0;                 
    simonInput = "";           
    continu = nouvellePartie();
    lcd.setCursor(0,1);
    lcd.print("Score: " + String(score));
  }
}


bool manche() { 
  delay(300);
  String userInput;
  bool boutonPresse = false;
  int newLED = random(4);
  simonInput = simonInput + newLED;  
  leds++;

  niveau++;
  
  for(int i = 0; i < leds; i++) {
    displayPattern(simonInput.charAt(i), niveau);
  }

  for(int i = 0; i < leds; i++) {
    while(boutonPresse == false) {
      if(boutonPresse = digitalRead(bouton_ledBleu) == true) {       
        digitalWrite(led_bleu, HIGH);
        delay(700);

        digitalWrite(led_bleu, LOW);
        boutonPresse = true;

        userInput = userInput + 0;
        delay(400);

      } else if(boutonPresse = digitalRead(bouton_ledRouge) == true) {
        digitalWrite(led_rouge, HIGH); 
        delay(700);
        
        digitalWrite(led_rouge, LOW);
        boutonPresse = true;
        
        userInput = userInput + 1;
        delay(400);

      } else if(boutonPresse = digitalRead(bouton_ledVerte) == true) {
        digitalWrite(led_verte, HIGH);
        delay(700);
        
        digitalWrite(led_verte, LOW);    
        boutonPresse = true;

        userInput = userInput + 2;
        delay(400);
        
      } else if(boutonPresse = digitalRead(bouton_ledJaune) == true) {        
        digitalWrite(led_jaune, HIGH);
        delay(700);
        
        digitalWrite(led_jaune, LOW);
        boutonPresse = true;

        userInput = userInput + 3;
        delay(400);
      }
    }

    if(userInput.charAt(i) != simonInput.charAt(i)) {  
        gameOver();                 
        return false;     
      }

    boutonPresse = false;
  }

  score++;                         
  lcd.setCursor(0,1);
  lcd.print("Score: " + String(score)); 
  return true;
    
}

void displayPattern(char led, int niveau) {
  if(led == '0') {
    digitalWrite(led_bleu, HIGH);
    mon_delay(niveau);

    digitalWrite(led_bleu, LOW);
  } else if(led == '1') {
    digitalWrite(led_rouge, HIGH);
    mon_delay(niveau);

    digitalWrite(led_rouge, LOW);
  } else if(led == '2') {
    digitalWrite(led_verte, HIGH);
    mon_delay(niveau);
    
    digitalWrite(led_verte, LOW);
  } else if(led == '3') {
    digitalWrite(led_jaune, HIGH);
    mon_delay(niveau);

    digitalWrite(led_jaune, LOW);
  }
}

bool nouvellePartie() {
  bool boutonPresse = false;

  while(boutonPresse == false) {
    if(etatBouton = digitalRead(bouton_ledBleu) == true) {
      boutonPresse = true;

    } else if(etatBouton = digitalRead(bouton_ledRouge) == true) {
      boutonPresse = true;
      
    } else if(etatBouton = digitalRead(bouton_ledVerte) == true) {
      boutonPresse = true;
    
    } else if(etatBouton = digitalRead(bouton_ledJaune) == true) {
      boutonPresse = true;
      
    }
  }
  
  int count = 0;
  niveau = 0;  
  
  while(count < 3) {
    digitalWrite(led_bleu,HIGH);
    digitalWrite(led_rouge,HIGH);
    digitalWrite(led_verte,HIGH);
    digitalWrite(led_jaune,HIGH);
    
    delay(200);
    
    digitalWrite(led_bleu,LOW);
    digitalWrite(led_rouge,LOW);
    digitalWrite(led_verte,LOW);
    digitalWrite(led_jaune,LOW);
    
    delay(200);
    
    count++;
  }

  delay(300);
  
  return boutonPresse;
}

void gameOver() {
  int count = 0;
  while(count < 3)  {
    digitalWrite(led_bleu,HIGH);
    digitalWrite(led_rouge,HIGH);
    digitalWrite(led_verte,HIGH);
    digitalWrite(led_jaune,HIGH);
    tone(buzzer, 1900);

    delay(300);
    
    digitalWrite(led_bleu,LOW);
    digitalWrite(led_rouge,LOW);
    digitalWrite(led_verte,LOW);
    digitalWrite(led_jaune,LOW);
    tone(buzzer, 1900);
    
    delay(300);
    
    noTone(buzzer);
    
    count++;
  }
}

void mon_delay(int niveau){
  if (niveau < 5) {
    delay(700);
  } else if (niveau < 10) {
    delay(500);    
  } else {
    delay(300);
  }
}