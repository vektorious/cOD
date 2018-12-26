#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int sense = A0;  // output pin of OPT101 attached to Analog 0
int val = 0 ;  
void setup()
{
  Serial.begin(9600);
  delay(100);
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Measuring OD");
  pinMode (2, OUTPUT); //for cell 1 LED
}

void loop()
{
  digitalWrite(2, HIGH);
  val = analogRead(sense);
  delay(1000);
  Serial.print(val);
  Serial.print(" alexunits OFF");
  Serial.print('\n');
  lcd.setCursor(0, 1);
  lcd.print(val);
  lcd.print(" alexunits");

}
