#include <Wire.h> 
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

float opt_signal= 0.0;

void setup() {
  Serial.begin(9600);
  Serial.print("go");
  ads.begin();
  delay(100);
}

void loop() {
  int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result
  adc0 = ads.readADC_SingleEnded(0);
  opt_signal = adc0;
  Serial.print(opt_signal);
  Serial.print(adc0);
  Serial.print("\n");
  delay(1000);
}
