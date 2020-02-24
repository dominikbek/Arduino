
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long time;
int przelacz1 = 7;
int przelacz2 = 8;
int ladowanie = 64;
int przycisk1 = 0;
int przycisk2 = 0;

void setup() {
 
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("format. --> 1");
  lcd.setCursor(0,1);
  lcd.print("ladow. --> 2");
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(6,INPUT);
  pinMode(10,INPUT);
}

void rozladuj(){

for(int i = 0; i <= 10800; i++) {
  float sensorValue0 = analogRead(A0);
  float sensorValue1 = analogRead(A1);
  time=millis()/3600000;
  float srednianap;
  float napiecieRozladowania = (sensorValue0 - sensorValue1) * (5 / 1024.000);
  float pradRozladowaniachwilowy = 1000*(napiecieRozladowania/4.7);
  for(int i = 0; i <= 10000; i++);
  {
    float sumanap;
    float sumaprad;
    sumanap = sumanap + napiecieRozladowania;
    srednianap = sumanap/i;
   }
  digitalWrite(przelacz1, HIGH);
  digitalWrite(przelacz2, HIGH);
  float pradRozladowania = 1000*(srednianap/4.7);
  float pojemnosc = pradRozladowania*time;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rozladowanie");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("nap.");
  lcd.setCursor(6,0); 
  lcd.print(srednianap);
  lcd.setCursor(12,0);
  lcd.print("V");
  lcd.setCursor(0,1);
  lcd.print("prad.");
  lcd.setCursor(12,1);
  lcd.print("mA");
  lcd.setCursor(6,1); 
  lcd.print(pradRozladowaniachwilowy);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("poj.");
  lcd.setCursor(6,0);
  lcd.print(pojemnosc);
  lcd.setCursor(11,0);
  lcd.print("mAh");
  lcd.setCursor(0,1);
  lcd.print("czas");
  lcd.setCursor(6,1);
  lcd.print(time,1);
  lcd.setCursor(11,1);
  lcd.print("h");
  delay(2000);
  if(srednianap <= 0.6)
  {
    break;
    }
  }
}

void laduj(){

for(int i = 0; i <= 10800; i++) {
   time=millis()/3600000;
   digitalWrite(przelacz1, LOW);
   digitalWrite(przelacz2, LOW);
   
   float sensorValue2 = analogRead(A2);
   float sensorValue3 = analogRead(A3);
   float sensorValue4 = analogRead(A4);
   float sensorValue5 = analogRead(A5);
   float napiecieLadowania = (sensorValue2 - sensorValue3) * (5 / 1024.000);
   float pradLadowaniachwilowy = 1000*(napiecieLadowania/10);
   float napiecie_na_baterii = (sensorValue4 - sensorValue5) * (5 / 1024.000);
   float sumanaplad;
   float srednianaplad;
   float sumapradLad;
   float sredniapradLad;
   float srednia_nap_baterii;
   float suma_nap_baterii;
    for(int i = 0; i <= 100; i++);
  {
    sumanaplad = sumanaplad + napiecieLadowania;
    srednianaplad = sumanaplad/i;
    sumapradLad = sumapradLad + pradLadowaniachwilowy;
    sredniapradLad = sumapradLad/i;
    suma_nap_baterii = suma_nap_baterii + napiecie_na_baterii;
    srednia_nap_baterii = suma_nap_baterii/i;
   }
   float pradLadowania = 1000*(srednianaplad/10);
   float pojemnosclad = pradLadowania*time;
     if(sredniapradLad < 100 && ladowanie < 255)
   {
    analogWrite(9,ladowanie++);
   }
   if (sredniapradLad > 120 && ladowanie > 0)
   {
    analogWrite(9,ladowanie--);
   }
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("nap.");
   lcd.setCursor(6,0);
   lcd.print(srednia_nap_baterii);
   lcd.setCursor(12,0);
   lcd.print("V");
   lcd.setCursor(0,1);
   lcd.print("prad.");
   lcd.setCursor(12,1);
   lcd.print("mA");
   lcd.setCursor(6,1); 
   lcd.print(sredniapradLad);
   delay(1000);
   if(srednia_nap_baterii > 1.6 && time > 0.1)
   {
   for(int i = 0; i <= 10800; i++)
   {
   if(sredniapradLad < 10 && ladowanie < 255)
   {
      analogWrite(9,ladowanie++);
   }
   if (sredniapradLad > 20)
   {
    analogWrite(9,ladowanie--);
   }
   }
   }
   }

}
void loop() {
  
  przycisk1 = digitalRead(6);
  przycisk2 = digitalRead(10);
  
  if(przycisk1 == HIGH && przycisk2 == LOW)
  {
  rozladuj();
  delay(1000);
  laduj();
  delay(1000);
  rozladuj();
  delay(1000);
  laduj();
  delay(1000);
  }
  if(przycisk2 == HIGH && przycisk1 == LOW)
  {
  laduj();
  delay(1000);
  }
}

