#include <LiquidCrystal.h>

const int rs = 11, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);

}

void welcome(){
  lcd.setCursor(5,0);
  lcd.print("U De C");
  lcd.setCursor(3,1);
  lcd.print("Bienvenido!");
  delay(500);
}

void loop() {
  welcome();
 

}
