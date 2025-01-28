/*
 * original program by Nicu FLORICA (niq_ro)
 * 0 - intial (momentary switch at D2__/__GND)
 * 0a - added on tine in serial hh:mm:ss
 * 0b - added 2 external leds
 */

#define senzor 2
#define LED0 13
#define LED1 3  // red led
#define LED2 4  // yellow led
#define LED3 5  // green led

byte staresenzor1 = 1;  // stare actuala senzor
byte staresenzor0 = 1; // stare anterioara senzor
byte actionare = 0;  // numere pare (parcare libera)

unsigned long timp1;
unsigned long timp2;
unsigned long timp0;


void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("ON/OFF control with momentary button");
  Serial.println("Program by Nicu FLORICA (niq_ro)");
  Serial.println("ver. 0 - 18.01.2025, Craiova");
  Serial.println("---------------------");
  
  pinMode (LED0, OUTPUT);
  digitalWrite(LED0, 0);
  pinMode (LED1, OUTPUT);
  digitalWrite(LED1, 0);
  pinMode (LED2, OUTPUT);
  digitalWrite(LED2, 1);
  pinMode (LED3, OUTPUT);
  digitalWrite(LED3, 0); 
  
  pinMode (senzor, INPUT);
  digitalWrite(senzor, HIGH);
}

void citirebutoane() 
{
  staresenzor1 = digitalRead(senzor);  // se citeste starea actuala a senzorului
  if (staresenzor1 != staresenzor0) // daca senzorul a fost activat
   {
    if (staresenzor1 == LOW) // si inca este activat
     {  
     actionare++;
     digitalWrite(LED0, actionare%2);
     digitalWrite(LED1, actionare%2);
     digitalWrite(LED2, (actionare+1)%2);
     Serial.println("Button was push !");
     if (actionare%2 == 1)
     {
      Serial.println("LED is now ON !");
      timp2 = millis()/1000;
     }
     else
     {
      Serial.println("LED is now OFF!");
      timp1 = millis()/1000;
      timp0 = timp1 - timp2;
      Serial.print("LED was on: ");
      Serial.print((timp0/3600)/10);
      Serial.print((timp0/3600)%10);
      Serial.print("h:");
      Serial.print(((timp0%3600)/60)/10);
      Serial.print(((timp0%3600)/60)%10);
      Serial.print("m:");
      Serial.print(((timp0%3600)%60)/10);
      Serial.print(((timp0%3600)%60)%10);
      Serial.println("s");
     }
     } 
    delay(30);
  staresenzor0 = staresenzor1;  // starea actuala a senzorului este memorata
  }
digitalWrite(LED3, (millis()/1000)%2);   
} // sfarsit subrutina citire stare senzor


void loop() {
  citirebutoane();

delay(100);
}  // sfarsit de program principal
