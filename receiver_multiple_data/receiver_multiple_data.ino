#include <RH_ASK.h>
#include <SPI.h> 
 
String strHum;
String strTemp;
String strIn;
String strHello;
String strPrincess;
 
RH_ASK rf_driver;
 
void setup()
{
    rf_driver.init();
    Serial.begin(9600);
}
 
void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    if (rf_driver.recv(buf, &buflen)){
      strIn = String((char*)buf);
      strHum = strIn.substring(0,5);
      strTemp = strIn.substring(6,11);
      strHello = strIn.substring(12,17);
      strPrincess = strIn.substring(18);
      //MSG1
      Serial.print("Humidity: "); Serial.print(strHum);
      Serial.print("  - Temperature: "); Serial.println(strTemp);   

      //MSG2
      Serial.print("Message 2 \t");
      Serial.print(strHello); Serial.print("\t");
      Serial.println(strPrincess);           
    }
}
