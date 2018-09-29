#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

float darksig = 0;
float lightsig = 0;
float total = 0;

int sensor = A0;  // output pin of OPT101 attached to Analog 0
int LEDpin = 2;    // LED + attached to D2

int counter = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Measuring...");
  
  pinMode (2, OUTPUT); //for cell 1 LED
  delay(1000);
}

void loop() {
  delay(1000);
  counter = 10;
  for (int dummy = 0; dummy < 10; dummy++)
  {
    lcd.clear();
    lcd.print("Measuring...");
    lcd.setCursor(0, 1);
    lcd.print("Starting in: ");
    lcd.print(counter);
    counter = abs(counter - 1);
    delay(1000);
  }
  measurement(10);
  
  delay(100);
}

void measurement(int multiplier) {
  darksig = 0;
  delay(1000);
  lcd.clear();
  lcd.print("Dark: ");
  delay(1000);
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(500);
    darksig = abs(darksig + analogRead(sensor));
    delay(500);
  }
  delay(1000);
  lcd.print(darksig);
  delay(2000);
  
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  
  lightsig = 0;
  delay(100);
  digitalWrite(LEDpin, HIGH); //turns exp LED on
  delay(1000);
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(500);
    lightsig = (lightsig + analogRead(sensor));
    delay(500);
  }
  delay(1000);
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!

  lcd.print(lightsig);
  total = abs(lightsig - darksig);
  
  delay(1000);
  Serial.print("cell_1");
  Serial.print(',');
  Serial.print(darksig);
  Serial.print(',');
  Serial.print(lightsig);
  Serial.print(',');
  Serial.print(total);
  Serial.print('\n'); 
}
