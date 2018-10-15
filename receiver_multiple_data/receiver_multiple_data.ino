#include <RH_ASK.h>
#include <SPI.h>

String strIn;
String strHum;
String strTemp;
String strAx;
String strAy;
String strAz;
String strAux1;
String strAux2;
String strAux3;

RH_ASK rf_driver;

void setup()
{
  rf_driver.init();
  Serial.begin(9600);
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {
    //strIn = ((char*)buf);//take the strig in the buffer
    strIn = String((char*)buf);
    for (int i = 0; i < strIn.length(); i++) {
      if (strIn.substring(i, i + 1) == ",") {
        strHum = strIn.substring(0, i);
        strAux1 = strIn.substring(i + 1);
        break;
      }
    }
    for (int j = 0; j < strAux1.length(); j++) {
      if (strAux1.substring(j, j + 1) == ",") {
        strTemp = strAux1.substring(0, j);
        strAux2 = strAux1.substring(j + 1);
        break;
      }
    }
    for (int k = 0; k < strAux2.length(); k++) {
      if (strAux2.substring(k, k + 1) == ",") {
        strAx = strAux2.substring(0, k);
        strAux3 = strAux2.substring(k + 1);
        break;
      }
    }
    for (int l = 0; l < strAux3.length(); l++) {
      if (strAux3.substring(l, l + 1) == ",") {
        strAy = strAux3.substring(0, l);
        strAz = strAux3.substring(l + 1);
        break;
      }
    }
    Serial.println("Humidity - Temperature - Ax - Ay - Az: ");
    Serial.println(strHum);
    Serial.println(strTemp); 
    Serial.println(strAx);
    Serial.println(strAy);
    Serial.println(strAz);
  }
}
