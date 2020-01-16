#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "commoncoding";    //your wifi network
const char* password = "coding0317";     //yout wifi pasword
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;

const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";
String GAS_ID = "AKfycbxqUGFUjVfQjUEvUNgtTocXtUMUOPS50o3zGv4kZX5HjEt0VRa3";     //spreadsheet id

void setup() 
{
  
  Serial.begin(115200); 
  Serial.println();

  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure();
}

void loop() 
{
  int CDS = analogRead(A0);
  
  sendData(CDS);
}

void sendData(int cds)
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
  Serial.println("certificate matches");
  } else {
  Serial.println("certificate doesn't match");
  }
  //String string_temperature =  String(tem, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?CDS=" + cds;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
  }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
  Serial.println("esp8266/Arduino CI successfull!");
  } else {
  Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
} 
