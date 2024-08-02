#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ir D4
#define alco A0
#define motor_pin1 D5
#define motor_pin2 D3
const int alco_limit=450;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(ir,INPUT);
  pinMode(motor_pin1,OUTPUT);
  pinMode(motor_pin2,OUTPUT);
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  int ir_value=digitalRead(ir);

  if(ir_value==1)
  {
    Serial.println("Person is detected on the seat");
    delay(1000);

    int alco_level=analogRead(alco);
    Serial.print("Alcohol Level: ");
    Serial.println(alco_level);

    if(alco_level>=alco_limit)
    {
      Serial.println("Alcohol Detected");
      Serial.println("You Are Drunk");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alcohol detected");
      lcd.setCursor(0, 1);
      lcd.print("You Are Drunk");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car Stopped");

      delay(100);
      //stop_motor();
      digitalWrite(motor_pin1,LOW);
      digitalWrite(motor_pin2,LOW);

    }

    else
    {
      Serial.println("No Alcohol Detected Save to Drive");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Alcohol");
      lcd.setCursor(0, 1);
      lcd.print("Save Drive");

      delay(1000);
      //run_motor();
      digitalWrite(motor_pin1,HIGH);
      digitalWrite(motor_pin2,LOW);
    }

    delay(2500);
  }

  else
  {
    Serial.println("Person Not Detected on Seat");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Person");
  }

  delay(2000);
}