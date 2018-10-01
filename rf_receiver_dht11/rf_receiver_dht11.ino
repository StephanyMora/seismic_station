#include <RH_ASK.h>
#include <SPI.h> 
 
String str_hum;
String str_temp;
String str_in;
 
RH_ASK rf_driver;
 
void setup()
{
    rf_driver.init();
    Serial.begin(9600);
}
 
void loop()
{
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    if (rf_driver.recv(buf, &buflen)){
      str_in = String((char*)buf);
      for (int i = 0; i < str_in.length(); i++){
        if (str_in.substring(i, i+1) == ","){
          str_hum = str_in.substring(0, i);
          str_temp = str_in.substring(i+1);
        break;
        }
      }
      Serial.print("Humidity: ");
      Serial.print(str_hum);
      Serial.print("  - Temperature: ");
      Serial.println(str_temp);              
    }
}
