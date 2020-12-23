#include <Servo.h>

int servoPin = 9;
int cdsPin = A0;
int jump = 0;
int readytojump = 0;
int cdst1 = 0;
int cdst2 = 0;
int highValue = 206;//190 206
int lowValue = 195   ;// 170 190 
Servo servo;

int angle = 0; // servo position in degrees

void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);
  servo.write(180);
  delay(1000);
}

 

void loop() {
  
  int  cdst3 = analogRead(cdsPin);

  // averaging past three values
  int  cds = (cdst1 + cdst2 + cdst3) / 3                ;
  cdst1 = cdst2;
  cdst2 = cdst3;
Serial.println(cds);
  if (cds > highValue && readytojump == 1) {
      jump = 1;
      readytojump = 0;
  } else if(cds < lowValue) {
      readytojump = 1;
      jump = 0; 
  }
 
  if(jump == 1) { 
    jump = 0;
    Serial.println("JUMP!");
    servo.write(165);
    delay(150);
    servo.write(180);                                               
  }

}
