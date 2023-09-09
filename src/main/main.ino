int waterTime = 4; // for how long the pump will be on [seconds]
int waitTime = 0.5; // how long to wait between watering [minutes]
int pumpPin = 3; // pin that turns the motor on
int ledPin = 13; // pin that turns the led on

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows


void setup()
{
  pinMode(pumpPin, OUTPUT); // set pin 3 to an output
  pinMode(ledPin, OUTPUT); // set pin 13 to an output
  Serial.begin(9600); // begin communication

  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  int analogMoisture = analogRead(A0); //read analog value of moisture
  int moisture = ( 100 - ( (analogMoisture / 1023.00) * 100 ) ); //convert value to %

  Serial.println(moisture); // print moisture value to serial monitor

  if (moisture < 50) {  // Water the plant when the soil is dry
    digitalWrite(pumpPin, HIGH); // turn the pump on
    digitalWrite(ledPin, HIGH); // turn the led on
    lcd.clear(); // clear the display 
    lcd.setCursor(0, 0);  // move the cursor to (0, 0)
    lcd.print("WATERING");  // print the message at (0, 0)      
    lcd.setCursor(2, 1); // move the cursor to (2, 1)
    lcd.print("IS ON"); // print the message at (2, 1)
    delay(waterTime * 1000);      // delay in miliseconds
  }
  else {
    digitalWrite(pumpPin, LOW);  // turn the pump off
    digitalWrite(ledPin, LOW);  // turn the led off
    lcd.clear();                 // clear the display
    lcd.setCursor(0, 0);         // move the cursor tom(0, 0)
    lcd.print("MOISTURE [%]:");        // print the message at (0, 0)
    lcd.setCursor(2, 1);
    lcd.print(moisture); // print the message at (2, 1)
    delay(waitTime * 60000);      // delay in miliseconds
  }

}