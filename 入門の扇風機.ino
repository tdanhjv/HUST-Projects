#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0;   // the output pin of LM35
int fan = 11;       // the pin where fan is
int led = 8;        // led pin
int temp;
int tempMin = 20 ;   // the temperature to start the fan
int tempMax = 50 ;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;
 
void setup() {
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tempPin, INPUT);
  lcd.begin(16,2);  
}
 
 
void loop() {  
   temp = readTemp();     // get the temperature from sensor
   if(temp < tempMin) { // if temp is lower than desired temp 
      fanSpeed = 0; // fan is not spinning
      fanLCD = 0;  
      analogWrite(fan, fanSpeed); 
   } 
   if((temp  >= tempMin) && (temp <= tempMax)) { // if temperature is higher than minimum temp 
      fanSpeed = map(temp, tempMin, tempMax, 32, 255); // the actual speed of fan 
      fanLCD = map(temp, tempMin, tempMax, 0, 100); // speed of fan to display on LCD 
      analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed 
   } 
   if(temp > tempMax){        // if temp is higher than tempMax
     digitalWrite(led, HIGH);// turn on led
     fanSpeed = 255;
     fanLCD = 100;

     analogWrite(fan, fanSpeed);
   } else {                    // else turn of led
     digitalWrite(led, LOW); 
   }
 
   lcd.print("TEMP: ");
   lcd.print(temp);      // display the temperature
   lcd.print("C ");
   lcd.setCursor(0,1);   // move cursor to next line
   lcd.print("FANS: ");
   lcd.print(fanLCD);    // display the fan speed
   lcd.print("%");
   delay(200);
   lcd.clear();   
}
 
int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  int voltage = temp * (5000 / 1024.0);
  int temp = voltage / 10;
  return temp;
}
 
