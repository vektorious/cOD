#include <OneWire.h>
#define ONE_WIRE_BUS 4
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float darksig = 0;
float lightsig = 0;
float total = 0;
float temp = 0;

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
  counter = 10;
  for (int dummy = 0; dummy < 10; dummy++)
  {
    lcd.setCursor(0, 0);
    lcd.print("                            ");
    lcd.setCursor(0, 0);
    lcd.print("Starting in: ");
    lcd.print(counter);
    counter = abs(counter - 1);
    delay(1000);
  }
  lcd.setCursor(0, 0);
  lcd.print("                                  ");
  lcd.setCursor(0, 0);
  lcd.print("Signal: ");

  lcd.setCursor(0, 1);
  lcd.print("                                  ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  
  pinMode (2, OUTPUT); //for cell 1 LED
  delay(1000);
}

void loop() {
  delay(100);
  
  ODmeasurement(10);
  TEMPmeasurement();
  Serial.print('\n');
   
  delay(100);
}

void ODmeasurement(int multiplier) {
  darksig = 0;
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(500);
    darksig = abs(darksig + analogRead(sensor));
    delay(500);
  }
  delay(500);

  lightsig = 0;
  digitalWrite(LEDpin, HIGH); //turns exp LED on
  delay(1000);
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(500);
    lightsig = (lightsig + analogRead(sensor));
    delay(500);
  }
  delay(500);
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!

  total = abs(lightsig - darksig);

  lcd.setCursor(0, 0);
  lcd.print("                                  ");
  lcd.setCursor(0, 0);
  lcd.print("Signal: ");
  lcd.print(total);
  
  delay(100);
  Serial.print("cell_1");
  Serial.print(',');
  Serial.print(darksig);
  Serial.print(',');
  Serial.print(lightsig);
  Serial.print(',');
  Serial.print(total);
  Serial.print(',');  
}

void TEMPmeasurement() 
{
  delay(500) ; 
  sensors.requestTemperatures(); // Send the command to get temperature readings
  temp = sensors.getTempCByIndex(0);
  
  lcd.setCursor(0, 1);
  lcd.print("                                  ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C"); 
  Serial.print(temp);
} 
