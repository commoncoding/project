#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

#define BAUD 9600
//#define BAUD 57600

String NAME="tttt";

void setup()
{
  Serial.begin(BAUD);
  Serial.println("Enter AT commands:");
  BTSerial.begin(BAUD);

  if(BAUD==9600){
    BTSerial.print("AT+NAME:"+NAME);
    BTSerial.print("\r\n");
    delay(100);
   
    BTSerial.print("AT+UART=57600,0,0");
    BTSerial.print("\r\n");
  } else {
    BTSerial.print("AT+VERSION");
    BTSerial.print("\r\n");
  }

}
void loop()
{
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available())
    BTSerial.write(Serial.read());
}
