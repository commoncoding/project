#include <Wire.h>    
#define DS3231_I2C_ADDRESS 104

// SCL - pin A5, SDA - pin A4

byte seconds, minutes, hours, day, date, month, year;
char weekDay[4]; 

void setup()

{
  Wire.begin();
  Serial.begin(9600);
}
void loop()
{
  watchConsole();
  get3231Date();

  Serial.print(weekDay);
  Serial.print(", 20");
  Serial.print(year, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(date, DEC);
  Serial.print(" - ");
  Serial.print(hours, DEC); 
  Serial.print(":"); 
  Serial.print(minutes, DEC); 
  Serial.print(":"); 
  Serial.println(seconds, DEC);
  delay(1000);
}
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
void watchConsole()
{
  if (Serial.available()) {  
    if (Serial.read() == 84) { 
      set3231Date();
      get3231Date();
      Serial.println(" ");
    }
  }
}
void set3231Date()
{
  year    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  month   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  date    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  hours   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  minutes = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  seconds = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48));
  day     = (byte) (Serial.read() - 48);

  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(date));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void get3231Date()
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS); 
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7); 
  if(Wire.available()) {
    seconds = Wire.read(); 
    minutes = Wire.read(); 
    hours   = Wire.read();
    day     = Wire.read();
    date    = Wire.read();
    month   = Wire.read(); 
    year    = Wire.read();

    seconds = (((seconds & B11110000)>>4)*10 + (seconds & B00001111)); 
    minutes = (((minutes & B11110000)>>4)*10 + (minutes & B00001111)); 
    hours   = (((hours & B00110000)>>4)*10 + (hours & B00001111));
    day     = (day & B00000111); // 1-7
    date    = (((date & B00110000)>>4)*10 + (date & B00001111)); 
    month   = (((month & B00010000)>>4)*10 + (month & B00001111)); 
    year    = (((year & B11110000)>>4)*10 + (year & B00001111));
  }
  
  switch (day) {
    case 1:
      strcpy(weekDay, "Sun");
      break;
    case 2:
      strcpy(weekDay, "Mon");
      break;
    case 3:
      strcpy(weekDay, "Tue");
      break;
    case 4:
      strcpy(weekDay, "Wed");
      break;
    case 5:
      strcpy(weekDay, "Thu");
      break;
    case 6:
      strcpy(weekDay, "Fri");
      break;
    case 7:
      strcpy(weekDay, "Sat");
      break;
  }
}
