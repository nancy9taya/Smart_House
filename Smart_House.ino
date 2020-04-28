#include<Keypad.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(A1,A2,3,2,1,A3);
const byte ROWS = 4; 
const byte COLS = 4; 

char KeyMap[ROWS][COLS] = {
  {'7', '8', '9', '*'},
  {'4', '5', '6', '/'},
  {'1', '2', '3', '-'},
  {'#', '0', '=', '+'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {7,6, 5, 4}; 

Keypad customKeypad = Keypad(makeKeymap(KeyMap), rowPins, colPins, ROWS, COLS); 
int controller = 13;
int House = 12;  
int Fan = 0;
volatile int buttonState; 
int input;
char password[4]={'9','2','4','8'};
boolean flag = 1;
float temp_old, temp_new;
int x=0;
int password_enterd =0;

void setup() {
  
  lcd.begin(16,2);
  pinMode(controller, INPUT); 
  pinMode(House, OUTPUT);  
  pinMode(Fan, OUTPUT);  
  lcd.print(" password");
  attachInterrupt(1, pin_input, CHANGE);
}

void loop() {
  flag=1;
  //wait for owner to enter the password to enter house
  if( password_enterd == 0){
  for(int i = 0 ;i <sizeof(password) ;i++){
  char key = customKeypad.waitForKey();
  //lcd.clear();
  lcd.setCursor(i,1);
  lcd.print("#");
 // lcd.scroll()
  if(key != password[i]){
     flag = 0;
    }
   }
  }
  if(flag){
     x=1;
     password_enterd =1;
  }
  temp_old = analogRead(A0);
  temp_new = temp_old * 0.489;
 // input = digitalRead(controller); 
  if(flag ){
  //digitalWrite(House, HIGH); 
 if(temp_new >= 25){
   digitalWrite(Fan, HIGH); 
  }
  else{
    digitalWrite(Fan, LOW); 
    }
   lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("temp is");
  lcd.setCursor(0,1);
  lcd.print(temp_new);
  delay(1000);

  }
  else if(flag == 0){
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("wrong");
      }
}


void pin_input() {
  buttonState = digitalRead(controller); 
  if(x ==1){
   if(buttonState == 0 ){
    digitalWrite(House, LOW); 
    }
    else{
    digitalWrite(House, HIGH); 
      }
  }
}
