#include <Keypad.h>
#define Password_Length 5 // Give enough room for 4 chars + NULL char
#define lockled 5
#define openled 4
#define openchk 2
#define motorR 6

/* Display Operations 
 * LCD RS pin to digital pin 13
 * LCD Enable pin to digital pin 12
 * LCD D4 pin to digital pin 11
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 9
 * LCD D7 pin to digital pin 8
  * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Keypad Operations
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'3','2','1'},
  {'6','5','4'},
  {'9','8','7'},
  {'#','0','*'} };
byte rowPins[ROWS] = {19, 18, 17, 16}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 14, 15}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Password KEYS
String passcode1 = "7656";
String passcode2 = "4594";
String passcode3 = "3613";
String passcode4 = "1697";
String passcode5 = "9661";
String password = "";
byte data_count = 0;

void setup(){
 pinMode(openchk, INPUT);
  pinMode(motorR, OUTPUT);
  pinMode(lockled, OUTPUT);
  pinMode(openled, OUTPUT);
  digitalWrite(lockled, HIGH);
  digitalWrite(openled, LOW);
    lockcontrol(0);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.write("LOCKED");
    lockcontrol(0);
}

void loop(){
  char key = keypad.getKey();
  if (key){ // makes sure a key is actually pressed
    if (key == '#'){
      resetpass();
      lcdroutine(0);
      lockcontrol(0);}
    password += key; // store char into data array
    lcd.write(key);
    data_count++;}
  if(data_count == Password_Length-1){ // if the array index is equal to the number of expected chars, compare data to master
      delay(500);
      checkpass();
}
}

void lcdroutine(int k){ // Print message
  if (k==0){
  lcd.clear();
  lcd.write("LOCKED");
  }
  else if(k==1){
  lcd.clear();
  lcd.write("PASSCODE OK!");
    }
  }

void checkpass(){ // Check password
        if(password == passcode1){ // equal to (strcmp(Data, Master) == 0)
            lockcontrol(1);resetpass();}
        else if(password == passcode2){ // equal to (strcmp(Data, Master) == 0)
            lockcontrol(1);resetpass();}
        else if(password == passcode3){ // equal to (strcmp(Data, Master) == 0)
            lockcontrol(1);resetpass();}
        else if(password == passcode4){ // equal to (strcmp(Data, Master) == 0)
            lockcontrol(1);resetpass();}
        else if(password == passcode5){ // equal to (strcmp(Data, Master) == 0)
            lockcontrol(1);resetpass();}
        else{ 
     lockcontrol(0);resetpass();}
  }

void resetpass(){
    password = "";
    data_count = 0;
  }

void lockcontrol(int x){
  if(x == 1){ // Open locking mechanism
    lcdroutine(1);
     digitalWrite(openled, HIGH);
     digitalWrite(lockled, LOW);
    if(digitalRead(openchk) == LOW){digitalWrite(motorR, HIGH);}
    if(digitalRead(openchk) == HIGH){digitalWrite(motorR, LOW);}
    }else{  // Close locking mechanism
    lcdroutine(0);
    digitalWrite(motorR, LOW);
    digitalWrite(openled, LOW);
    digitalWrite(lockled, HIGH);
    }
  }
