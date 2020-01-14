#include <U8glib.h>
#include <Wire.h>
#include <DHT11.h>

int pin = 3;
DHT11 dht11(pin);

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
 
void setup() {
  Wire.begin();
}

void loop() {
  float temperature, humidity;

  getDHTData(&temperature, &humidity);
 
  u8g.firstPage();
  do {    
    u8g.setFont(u8g_font_9x18B);
    u8g.setPrintPos(5, 20);
    u8g.print("TEMP");
    u8g.setFont(u8g_font_fub14);
    
    u8g.print(": ");
    u8g.print(temperature);
    u8g.print("\xb0""C");

    u8g.setFont(u8g_font_9x18B); 
    u8g.setPrintPos(5, 50);
    u8g.print("HUMI");
    u8g.setFont(u8g_font_fub14); 
    
    u8g.print(": ");
    u8g.print(humidity);
    u8g.print("%");

    delay(1000);
  } while(u8g.nextPage());
}

void getDHTData(float *temperature, float *humidity) {
  int i;
  float temp, humi;
  if((i = dht11.read(humi,temp)) == 0){
      Serial.print(temp);
      Serial.println(humi);
       *temperature = temp;
       *humidity = humi;
    }
}
