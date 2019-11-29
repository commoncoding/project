#include <Servo.h>   //서보모터 라이브러리 추가

const int trigPin = 10;   //초음파센서의 trig핀을 아두이노 디지털 10번핀에 연결한다.
const int echoPin = 11;   //초음파센서의 echo핀을 아두이노 디지털 11번핀에 연결한다.
long duration;
int distance;
Servo servo;    //서보모터 라이브러리의 변수를 선언

void setup() {
  pinMode(trigPin, OUTPUT);  //아두이노 디지털 10번핀을 결과모드로 정한다.
  pinMode(echoPin, INPUT);   //아두이노 디지털 11번핀을 입력모드로 정한다.
  Serial.begin(9600);
  servo.attach(12);    //서보모터를 아두이노의 디지털 12번핀에 연결한다.
}

void loop() {
  for (int i=14; i<=166; i=i+2){    //변수 i가 14부터 166이 될때까지 i를 2씩 증가한다.
      servo.write(i);     //서보모터의 각도를 변수 i로 설정한다.
      delay(30);
      distance = calculateDistance();     //초음파센서로 물체와의 거리를 측정한다.
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);     //시리얼모니터에 초음파센서로 측정된 물체와의 거리를 출력한다.
      Serial.print(".");
    }
  for (int i=166; 14<=i; i=i-2){    //변수 i가 166부터 14가 될때까지 i를 2씩 감소한다.
      servo.write(i);     //서보모터의 각도를 변수 i로 설정한다.
      delay(30);
      distance = calculateDistance();     //초음파센서로 물체와의 거리를 측정한다.
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);     //시리얼모니터에 초음파센서로 측정된 물체와의 거리를 출력한다.
      Serial.print(".");
    }
}

int calculateDistance(){    //초음파센서가 물체와의 거리를 측정하게 해주는 함수
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);   //trig핀에서 echo핀으로 신호를 보낸다.
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);    //trig핀에서 echo핀으로 신호를 보내지 않도록 한다.
  duration = pulseIn(echoPin, HIGH);    //trig핀에서 신호를 보내고 echo핀까지 전달되기까지 소요되는 시간을 측정하여 변수 duration에 저장한다.
  distance = duration*0.034/2;    //duration에 저장된 값을 cm단위로 변환시켜주고, 변수 distance에 저장한다.
  return distance;
}
