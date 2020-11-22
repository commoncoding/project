#include <Keypad.h>  // for 4 *4 Keypad
#include <Servo.h>  // for servo motor

Servo servo;
char* password = "0123";  // set password

int position = 0;   // Variable that stores positions when comparing passwords


// keypadd button position
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[4] = {9,8,7,6};
byte colPins[4] = {5,4,3,2};

//initialize keypad 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4); 

void setup(){
  Serial.begin(9600);
  setLocked(true); 
  servo.attach(10);
  servo.write(180);
}

void loop()
{
  char key = keypad.getKey();

  Serial.println(key);
  
  if(('0' <= key && key <= '9') || ('A' <= key && key <='D') || (key == '*' || key == '#'))
  {                   
    if(key == '*' || key == '#')
    { //When the key is * or #, it resets the current position and keeps it locked.
      position = 0; 
      setLocked(true);
    } 
 
    else if(key == password[position])
    { //If the password of the current position and the entered key are the same, increase the position value.
      position++;
    }
    
    else if(key != password[position])
    { //If the password is incorrect, initialize it.
      position = 0;
      setLocked(true);
    }
  
    if(position == 4)
    { //password is correct, open the door.
      setLocked(false);
    }
    
  }
  delay(100);
}

void setLocked(int locked) 
{ 
  if(locked) 
  { 
    servo.write(180);
  }
  else
  {
    delay(500);
    servo.write(120);
  } 
}

 
