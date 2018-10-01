#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK rf_driver;

void setup()
{
  rf_driver.init();
}

void loop()
{
    const char *msg = "Welcome princess yoany!";
    rf_driver.send((uint8_t*)msg, strlen(msg));
    delay(1000);
}
