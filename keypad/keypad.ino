#include <Keypad.h>  // Keypad.h 라이브러리를 호출
#include <Servo.h>  // Servo.h 라이브러리를 호출

Servo servo;
char* password = "0317";  // 비밀번호 설정

int position = 0;   // 비밀번호 비교시 쓸 변수 선언
int wrong = 0;  // 비밀번호 비교시 쓸 변수 선언

// 키패드 버튼 위치 설정
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// 키패드에 연결된 핀번호 설정
byte rowPins[4] = {9,8,7,6};
byte colPins[4] = {5,4,3,2};

//키패드 라이브러리를 사용하기위해 keypad라는 변수 선언 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4); 

void setup(){
  Serial.begin(9600);
  setLocked(true); 
  servo.attach(10);    //서보모터를 디지털 10번핀에 연결
  servo.write(180);   //서보모터의 기본각도를 120도로 설정
}

void loop(){
  char key = keypad.getKey(); // 키패드에서 입력된 값을 가져온다

  Serial.println(key);
  // 키패드에서 입력된 값을 조사하여 맞게 입력된 값일 경우 비교
  if(('0' <= key && key <= '9') || ('A' <= key && key <='D') || (key == '*' || key == '#'))
  {                   
    if(key == '*' || key == '#')
    { 
      // *, # 버튼을 눌렀을 경우엔 문 닫힘
      position = 0; 
      wrong = 0; // 입력 초기화
      setLocked(true); // 잠금상태로 세팅
    } 
 
    else if(key == password[position])
    { 
      // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
      wrong = 0; // 비밀번호 오류 값을 0으로 만듦
    }
    
    else if(key != password[position])
    { 
      // 해당 자리에 맞지 않는 비밀번호가 입력됐을 경우
      position = 0; // 비밀번호를 맞았을 경우를 0으로 만듦
      setLocked(true); // 잠금상태로 세팅
      wrong++; // 비밀번호 오류 값을 늘려준다
    }
  
    if(position == 4)
    { 
      // 4자리 비밀번호가 모두 맞았을 경우
      setLocked(false); // 잠금상태를 해제 함
    }
    
  }
  delay(100);
}

void setLocked(int locked)
  { 
  // 잠금시와 해제시에 맞는 서보모터 각도를 설정해준다
  if(locked) 
  { 
    //잠금시에 서보모터 각도를 120도로 설정해준다 
    servo.write(180);
  }

  else
  {
    //해제시에 서보모터 각도를 180도로 설정해준다
    delay(500);
    servo.write(120);
    } 
}

 
