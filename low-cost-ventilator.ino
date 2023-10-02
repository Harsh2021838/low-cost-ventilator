#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
int potpin = 0;
int val;
#define d1 10
#define d2 11
uint8_t a,b;

#define mot_en 5
#define mot_in1 7
#define mot_in2 8





void setup()
{
  Serial.begin(9600);
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(mot_en,OUTPUT);
  pinMode(mot_in1,OUTPUT);
  pinMode(mot_in2,OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   VENTILATOR");
  lcd.setCursor(0, 1);
  lcd.print("    ");
  delay(2000);
}


void loop()
{
   a=digitalRead(d1);
   b=digitalRead(d2);
   motorun();
   
}

  void motorun()
  {
    if(a==LOW)
    {
      
        if(b==LOW)
      {
        adult();
        Serial.print("adult");
      }
       else if(b==HIGH)
      {
        child();
        Serial.print("child");
      }
    }
    else if(a==HIGH)
    {
      manual();
    }
  }

  
  
  void child()
  {
    lcd.clear();
    lcd.print("  Mode - Child");
    lcd.setCursor(0,1);
    lcd.print("Breath cycle 4 sec");
     analogWrite(mot_en,1000);
     digitalWrite(mot_in1,1);
     digitalWrite(mot_in2,0);
     delay(400);
     analogWrite(mot_en,50);
     digitalWrite(mot_in1,0);
     digitalWrite(mot_in2,1);
     delay(200);
    }
    
  

  void adult()
  {   
    lcd.clear();
    lcd.print("  Mode - Adult");
    lcd.setCursor(0,1);
    lcd.print("Breath cycle 5.5 sec");
     analogWrite(mot_en,1023);
     digitalWrite(mot_in1,1);
     digitalWrite(mot_in2,0);
     delay(500);
     analogWrite(mot_en,50);
     digitalWrite(mot_in1,0);
     digitalWrite(mot_in2,1);
     delay(200);
    
  }


  void manual()
  {
    val = analogRead(potpin);            
    val = map(val, 0, 1023, 0, 180);    
    
  if (val <=60 ) 
  {
    lcd.clear();
    lcd.setCursor(0,0);           
    lcd.print("Speed: LOW  ");
    lcd.setCursor(0,1);           
    lcd.print("Breath cycle 5 sec ");
    
     analogWrite(mot_en,990);
     digitalWrite(mot_in1,1);
     digitalWrite(mot_in2,0);
     delay(600);
     analogWrite(mot_en,50);
     digitalWrite(mot_in1,0);
     digitalWrite(mot_in2,1);
     delay(200);
      }
  
  
  else if (val >60 && val<=120) 
  {  
     lcd.clear();
     lcd.setCursor(0,0);           
     lcd.print("Speed: Medium"); 
     lcd.setCursor(0,1);           
     lcd.print("Breath cycle 3.5 sec ");
      
     analogWrite(mot_en,1000);
     digitalWrite(mot_in1,1);
     digitalWrite(mot_in2,0);
     delay(500);
     analogWrite(mot_en,50);
     digitalWrite(mot_in1,0);
     digitalWrite(mot_in2,1);
     delay(200);
  }
  
   else if (val<=180) 
   {
     lcd.clear();
     lcd.setCursor(0,0);           
     lcd.print("Speed: Fast"); 
     lcd.setCursor(0,1);           
     lcd.print("Breath cycle 3 sec ");
     analogWrite(mot_en,1023);
     digitalWrite(mot_in1,1);
     digitalWrite(mot_in2,0);
     delay(420);
     analogWrite(mot_en,50);
     digitalWrite(mot_in1,0);
     digitalWrite(mot_in2,1);
     delay(200);
  } 

 
  
  }
