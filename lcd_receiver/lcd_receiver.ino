#include <LiquidCrystal.h>
#include <DHT.h>
#include <SPI.h>
#include <RH_ASK.h>

#define DHTPIN 13
#define DHTTYPE 11

const int rs = 11, en = 10, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

RH_ASK rf_driver;

DHT dht(DHTPIN, DHTTYPE);

bool saludo = true;
float humedad;
float temperatura;
String strHumedad;
String strTemperatura;
String strIn;

void setup() {
  lcd.begin(16, 2);
  rf_driver.init();
  dht.begin();

}

/*void welcome(){
  lcd.setCursor(4,0);
  lcd.print("Volcano.io");
  lcd.setCursor(3,1);
  lcd.print("Bienvenido!");
  delay(500);
  lcd.clear(){
  saludo = false;
}*/

void dhtLecture(){
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  if(rf_driver.recv(buf, &buflen)){
    strIn = String((char*)buf);
    for(int i = 0; i < strIn.length(); i++){
      if(strIn.substring(i,i+1) == ","){
        strHumedad = strIn.substring(0,i);
        strTemperatura = strIn.substring(i+1);
        break;
      }  
    }
  }
  if(strHumedad >= "50" || strTemperatura >= "50"){
    digitalWrite(12,HIGH);
    delay(100);
    digitalWrite(12,LOW);  
    delay(100);
  }
  lcd.setCursor(0,0);
  lcd.print("Humedad: ");
  lcd.print(strHumedad);
  lcd.print(" %\t");
  lcd.setCursor(0,1);
  lcd.print("Temp.: ");
  lcd.print(strTemperatura);
  lcd.print(" *C ");  
}

void loop() {
  dhtLecture();
}
