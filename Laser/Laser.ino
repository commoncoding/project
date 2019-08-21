#include <Servo.h>   //서보모터를 사용하기 위한 라이브러리를 추가해준다

const int joy_X = 0;   //조이스틱의 x좌표를 측정해주는 핀을 아날로그 A0번에 연결한다.
const int joy_Y = 1;  //조이스틱의 y좌표를 측정해주는 핀을 아날로그 A1번에 연결한다.

Servo horizontal, vertical;    //서보모터 라이브러리의 변수를 선언
#define LASER 11    //LASER라는 변수는 11의 값으로 지정.

void setup() {
  horizontal.attach(9);   //수평을 조작하는 서보모터를 9번핀에 연결한다.
  vertical.attach(10);   //수직을 조작하는 서보모터를 10번핀에 연결한다.
  pinMode(LASER, OUTPUT);   //11번핀은 출력모드로 사용한다.
  
  Serial.begin(9600);   //시리얼통신을 시작한다.
}

void loop(){

  int x = analogRead(joy_X);   //조이스틱의 x축 값을 읽어온 후, 변수 a에 저장한다.
  int y = analogRead(joy_Y);   //조이스틱의 y축 값을 읽어온 후, 변수 b에 저장한다.
  digitalWrite(LASER, HIGH);   //레이저에서 불빛이 나오도록 한다.

  if(x>600){   //조이스틱의 x축이 오른쪽으로 당겨졌다면
      horizontal.write(30);   //수평 서보모터의 각도를 30도로 설정한다.
    }
   if(x<200){   //조이스틱의 x축이 왼쪽으로 당겨졌다면
      horizontal.write(130);   //수평 서보모터의 각도를 130도로 설정한다.
    }
   if(y<200){   //조이스틱의 y축이 윗쪽으로 당겨졌다면
      vertical.write(80);   //수직 서보모터의 각도를 80도로 설정한다.
    }
   if(y>600){   //조이스틱의 y축이 아래쪽으로 당겨졌다면
      vertical.write(10);   //수직 서보모터의 각도를 10도로 설정한다.
    }
}
