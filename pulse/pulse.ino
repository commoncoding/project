volatile int BPM;                   //심박수 저장하기 위한 변수 선언
volatile int Signal;
volatile int Pulse;
volatile int IBI;

void setup(){
  Serial.begin(115200);  
  interruptSetup();     //심박수를 측정하는 함수
  pinMode(2, INPUT);    //버튼을 아두이노 디지털2번핀에 연결하였고, 입력타입으로 사용한다.
  pinMode(4, OUTPUT);   //green led를 아두이노 디지털4번핀에 연결하였고, 출력타입으로 사용한다.
  pinMode(8, OUTPUT);   //red led를 아두이노 디지털8번핀에 연결하였고, 출력타입으로 사용한다.
}

void loop(){
  int x = digitalRead(2);  //버튼이 눌리는지 아닌지 값을 읽어온다. 눌러진다면 1, 아니라면 0이다.
  //Serial.println(x);   //버튼의 값을 출력한다
  
  int before = BPM;  //대답을 하기 전 심장박동 수
  
  if( x == 1)   //만약 버튼이 눌렸다면
  {
   delay(3000);    //3초 후
   int after = BPM;    //대답을 한 후 심장박동 수
    
   if(before == after)    //대답을 하기 전 심장박동 수 와 대답을 한 후 심장박동 수 가 같다면 
   {  
    //거짓말을 안했다는 뜻
    //green led를 깜빡인다
    digitalWrite(4, HIGH);   
    delay(100);
    digitalWrite(4, LOW);
    delay(100);

    }
    else
    {
    //거짓말을 했다는 뜻
    //red led를 깜빡인다
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(8, LOW);
    delay(100);
      }
  }
  delay(1000);
}
