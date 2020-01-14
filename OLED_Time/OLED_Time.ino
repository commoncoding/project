#include <Wire.h>

#include <U8glib.h>
#include "RTClib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

  RTC_DS3231 RTC;
  int  monthIndex[122] ={0,3,6,9,12,15,18,21,24,27,30,33};
  String thisMonth = "";
  String thisTime = "";
  String thisDay="";
  
void setup() {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
}

void loop() {
  u8g.firstPage();
  do {
    draw();
    
    delay(10);
  } while(u8g.nextPage());
}


void draw(void) {
  u8g.setFont(u8g_font_9x15B);

  DateTime now = RTC.now();
  thisDay= String(now.year() , DEC)+ "/" + String(now.month(), DEC) + "/" + String(now.day(), DEC);
  const char* newDay = (const char*) thisDay.c_str();
  u8g.drawStr(5,10, newDay);  
  thisTime="";
  
  u8g.setFont(u8g_font_9x18B);
  if (now.hour() < 10){ thisTime="0"+ thisTime;} 
  thisTime=thisTime + String(now.hour()) + ":";
  if (now.minute() < 10){ thisTime=thisTime + "0";} 
  thisTime=thisTime + String(now.minute()); 

  const char* newTime = (const char*) thisTime.c_str();
  u8g.drawStr(5,25, newTime); 
 }
