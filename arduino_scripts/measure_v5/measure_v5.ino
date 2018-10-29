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
float total_signal = 0;
float total = 0;
float temp = 0;
float blank = 0;
float blanksignal = 0;

bool blanked = false;

int sensor = A0;  // output pin of OPT101 attached to Analog 0
int LEDpin = 2;    // LED + attached to D2
int Buttonpin = 3; // Button attached to D3
int buttonState = 0;

int counter = 0;

void setup() {
  pinMode(Buttonpin, INPUT);
  Serial.begin(9600);
  delay(100);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  counter = 10;
  for (int dummy = 0; dummy < 10; dummy++)
  {

    buttonState = digitalRead(Buttonpin);
    if (buttonState == HIGH){
      counter = 20;
      for (int dummy = 0; dummy < 10; dummy++){
        lcd.setCursor(0, 0);
        lcd.print("                            ");
        lcd.setCursor(0, 1);
        lcd.print("                            ");
        lcd.setCursor(0, 0);
        lcd.print("Done in: ");
        lcd.print(counter);
        lcd.setCursor(0, 1);
        lcd.print("Blanking...");
        blanksignal = ODblank(1);
        blank = blank + blanksignal;
        
        counter = abs(counter - 1);
      }
      blanked = true;
      break;
    } else {
      blanked = false;
    }
     
    lcd.setCursor(0, 0);
    lcd.print("                            ");
    lcd.setCursor(0, 1);
    lcd.print("                            ");
    
    lcd.setCursor(0, 0);
    lcd.print("Starting in: ");
    lcd.print(counter);
    counter = abs(counter - 1);
    lcd.setCursor(0, 1);
    lcd.print("Press for blank!");
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
  Serial.print(',');
  TEMPmeasurement();
  Serial.print('\n');
   
  delay(100);
}

float ODblank(int multiplier) {
  darksig = 0;
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(100);
    darksig = abs(darksig + analogRead(sensor));
    delay(100);
  }
  delay(100);

  lightsig = 0;
  digitalWrite(LEDpin, HIGH); //turns exp LED on
  delay(1000);
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(100);
    lightsig = (lightsig + analogRead(sensor));
    delay(100);
  }
  delay(100);
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  delay(1000);
  
  total_signal = abs(lightsig - darksig)/multiplier;
  return total_signal;
}

void ODmeasurement(int multiplier) {
  darksig = 0;
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(100);
    darksig = abs(darksig + analogRead(sensor));
    delay(100);
  }
  delay(100);

  lightsig = 0;
  digitalWrite(LEDpin, HIGH); //turns exp LED on
  delay(1000);
  for (int dummy = 0; dummy < multiplier; dummy++)
  {
    delay(100);
    lightsig = (lightsig + analogRead(sensor));
    delay(100);
  }
  delay(100);
  digitalWrite(LEDpin, LOW); //ensures cell 1 LED is off!!!!
  delay(1000);
  
  total_signal = abs(lightsig - darksig);

  

  lcd.setCursor(0, 0);
  lcd.print("                                  ");
  lcd.setCursor(0, 0);
  lcd.print("Signal: ");
  if(blanked == true){
    total = -log10(total_signal/(blank*multiplier));
    lcd.print(total);
    lcd.print(" OD");
    delay(100);
    Serial.print(total);
  }
  else {
    lcd.print(total_signal);
    delay(100);
    Serial.print(total_signal);
  }
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
