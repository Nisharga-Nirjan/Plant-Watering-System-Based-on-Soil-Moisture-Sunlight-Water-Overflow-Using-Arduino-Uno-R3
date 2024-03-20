//LCD: Library- Frank De Brabander
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);

//LDR
int photoPin = A3;

//Soil Moisture Sensor
int soilPin = A2;

//Ultrasonic
const int trigPin = 9; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor
float initial_distance, rate;
//Buzzer
int buzzPin = 7;

//Relay
int relayPin = 5;

void setup() //loops once
{
  Serial.begin(9600);
  
  //lcd
  lcd.init();
  lcd.backlight();
  
  
  //LDR
  pinMode(photoPin, INPUT);
  
  //soil
  pinMode(soilPin, INPUT);
  
  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long initial_duration_micro = pulseIn(echoPin, HIGH); //reading the duration till the high pulse in microseconds 
  initial_distance = (initial_duration_micro/2000000.0)*34300.0;  //unit: cm
  float max_depth_of_water = 5.0;	//Changeable....unit:cm
  rate = 100.0 / max_depth_of_water;
  
  //buzzer
  pinMode(buzzPin, OUTPUT);
  
  //Relay
  pinMode(relayPin, OUTPUT);
  

}

void loop()
{
  //Calculations
  int lightValue = analogRead(photoPin); // 0(Dark) to 1023(Light) range.
  float lightValue_percent = (lightValue/350.0) * 100;
  //actual range based on resistance: 34(DARK)-350(LIGHT)
  //condition:192
  
  int moistureValue = analogRead(soilPin); // 0(WET) to 1023(DRY) range.
  float moistureValue_percent = (1-(moistureValue/850.0)) * 100;
  //actual range: 400(WET)-850(DRY)
  //condition:625
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration_micro = pulseIn(echoPin, HIGH); //reading the duration till the high pulse in microseconds 
  float distance = (duration_micro/2000000.0)*34300.0;  //unit:cm
  float water_filled_percent = (initial_distance - distance) * rate;
  
  //Conditions
  if (lightValue > 192)
  {
    if (moistureValue > 625)
    {
      //Need Water
      digitalWrite(relayPin, HIGH); //Motor On
      
      lcd.clear();
      delay(500);
      
      lcd.setCursor(0,0);	//(position 0-15,row)
      lcd.print("SUN:");
      lcd.print(lightValue_percent,0);
      lcd.print("%");
      
      lcd.setCursor(0,1);
      lcd.print("MOIS:");
      lcd.print(moistureValue_percent,0);
      lcd.print("%");
      
      lcd.setCursor(10,0);
      lcd.print("MOTOR");
      lcd.setCursor(10,1);
      lcd.print("ON");
    }
    else
    {
      //Don't Need Water
      digitalWrite(relayPin, LOW); //Motor Off
      
      lcd.clear();
      delay(1000);
      
      lcd.setCursor(0,0);	//(position 0-15,row)
      lcd.print("SUN:");
      lcd.print(lightValue_percent,0);
      lcd.print("%");
      
      lcd.setCursor(0,1);
      lcd.print("MOIS:");
      lcd.print(moistureValue_percent,0);
      lcd.print("%");
      
      lcd.setCursor(10,0);
      lcd.print("MOTOR");
      lcd.setCursor(10,1);
      lcd.print("OFF");
    }
    delay(500);
  }
  else
  {
    //Not Enough Sunlight for Water
    digitalWrite(relayPin, LOW); //Motor Off
    
    lcd.clear();
    delay(500);
      
    lcd.setCursor(0,0);	//(position 0-15,row)
    lcd.print("SUN:");
    lcd.print(lightValue_percent,0);
    lcd.print("%");
      
    lcd.setCursor(0,1);
    lcd.print("MOIS:");
    lcd.print(moistureValue_percent,0);
    lcd.print("%");
      
    lcd.setCursor(10,0);
    lcd.print("MOTOR");
    lcd.setCursor(10,1);
    lcd.print("OFF");
    
    delay(500);
  }
  
  if (water_filled_percent > 50)	//Alarm!
  {
    tone(buzzPin,500);
    
    lcd.clear();
    delay(500);
    
    lcd.setCursor(1,0);
    lcd.print("Overflow:");
    lcd.print(water_filled_percent,1);
    lcd.print("%");
    lcd.setCursor(11,1);
    lcd.print("ALARM");
    
    lcd.setCursor(1,1);
    if (digitalRead(relayPin) == LOW)	//No Motor Issues
    {
      lcd.print("MOTOR OFF");
    }
    else	//Motor Issues
    {
      lcd.print("MOTOR ON");
    }
    delay(500);
  }
  
  else	//No Alarm
  {
    noTone(buzzPin);
    
    lcd.clear();
    delay(500);
    
    lcd.setCursor(1,0);
    lcd.print("Underflow:");
    lcd.print(water_filled_percent,1);
    lcd.print("%");
    lcd.setCursor(8,1);
    lcd.print("NO ALARM");
    
    delay(500);
  }
  
  
  
  
  
  
}