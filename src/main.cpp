#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int motorPin1 = 0;
int motorPin2 = 1;
int motorPin3 = 2;
int motorPin4 = 3;
int motorSpeed = 4;
char val = '0';
Servo myservo;
int position = 0;
int pos = 0;
const byte ROWS = 4;
const byte COLS = 4;
char pass[6];
char unlock[6];
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
char key;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  myservo.attach(4);
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
}


void loop() {
  if (position == 0)
  {
    do
    {
      position = 0;
      lcd.setCursor(0,0);
      lcd.print("Press Enter");
      lcd.setCursor(0,1);
      lcd.print("Anykey to LOCK");
    } while (keypad.getKey() == NO_KEY);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SetPassword 6dit");
    while (position < 6)
    {   
      lcd.setCursor(position,1);
      key = keypad.getKey();
      if (key != NO_KEY)
      {
        pass[position] = key;
        lcd.print("*");
        position ++;
      }
    }
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Password");
    int num=0;
    while (num < 6)
    {
      lcd.setCursor(num,1);
      key = keypad.getKey();
      if (key != NO_KEY)
      {
        unlock[num] = key;
        lcd.print("*");
        num ++;
      }
    }
    int check = 0;
    while (check < 6)
    {
      if (unlock[check] == pass[check])
      {
        check ++;
      }
      else {
        num = 0;
        check = 7;
        lcd.clear();
        lcd.print("Password Wrong");
        delay(1000);
        lcd.clear();
      }
      
    }
    if (check == 6)
    {
      
    lcd.clear();
    lcd.print("Correct");
    myservo.write(180);         
    delay(5000);          
    myservo.write(90);  
    delay(3000); 
    myservo.write(45); 
      delay(5000);          
    myservo.write(90); 
  
  /* for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);         
    delay(15);                  
  }*/

     
    }
    
  }