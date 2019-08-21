#include <SPI.h>   //rfid 사용하는데에 필요한 라이브러리 포함
#include <MFRC522.h>   //rfid 사용하는데에 필요한 라이브러리 포함
#include <Servo.h>   //서보모터 라이브러리 포함

Servo servo;   //서보모터 라이브러리를 사용하기 위한 변수 선언

int flag=1;   //servo의 열림/닫힘을 관리하기 위한 변수 선언

#define SDA_PIN 10   //rfid의 SDA핀을 아두이노의 디지털10번핀에 연결하였다
#define RST_PIN 9   //rfid의 RST핀을 아두이노의 디지털9번핀에 연결하였다

MFRC522 mfrc522(SDA_PIN, RST_PIN);   //MFRC522라이브러리를 사용하기위해 mfrc522라는 변수를 생성한다.
 
void setup() 
{
  Serial.begin(9600); 
  SPI.begin();  //SPI 초기화
  mfrc522.PCD_Init();   // MFRC522 초기화

  servo.attach(3);    //서보모터를 디지털 3번핀에 연결
  servo.write(180);   //서보모터의 기본각도를 180도로 설정(잠금)
}
void loop() 
{
  //새로운 카드가 접촉되었다면 if문을 빠져나간다.
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    Serial.println("no card");
    return;
  }
  //새로운 카드의 데이터를 성공적으로 읽었다면 if문을 빠져나간다.
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //찍은 카드번호를 시리얼모니터에서 확인
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "2B 3C C9 23") //자신의 카드 번호에 맞춰 변경해야 함
  {
    if(flag%2 == 1)   //금고 문이 잠금상태였다면
    {
      servo.write(120);   //서보모터의 각도를 120도로 설정(열림)
      flag++;   //flag변수를 1 증가시킴
      delay(1000);   
      }
    else    //금고 문이 열림상태였다면
    { 
      servo.write(180);
      flag++;    //flag변수를 1 증가시킴
      delay(1000);
      }
  }
 
 else   {      //카드번호가 틀렸을 때
    servo.write(180);  //서보모터의 각도를 180도로 설정(잠금)
    delay(500);
  }
} 
