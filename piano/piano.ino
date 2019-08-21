/* 
   방법 : 스케치 -> 라이브러리 포함하기 -> .ZIP라이브러리 추가 
           -> 다운로드 받은 zip 파일선택 -> CapacitiveSensor 클릭하면 
           #include <CapacitiveSensor.h> 코드가 자동으로 추가된다.
*/
#include <CapacitiveSensor.h>

//13번핀이 송신, 12번핀이 수신핀이다.(낮은 도)
//수신한 값을 a라는 변수에 저장한다.
CapacitiveSensor   a = CapacitiveSensor(13,12);  

//11번핀이 송신, 10번핀이 수신핀이다.(레)
//수신한 값을 b라는 변수에 저장한다.
CapacitiveSensor   b = CapacitiveSensor(11,10);

//9번핀이 송신, 8번핀이 수신핀이다.(미)
//수신한 값을 c라는 변수에 저장한다.
CapacitiveSensor   c = CapacitiveSensor(9,8);

//7번핀이 송신, 6번핀이 수신핀이다.(파)
//수신한 값을 d라는 변수에 저장한다.
CapacitiveSensor   d = CapacitiveSensor(7,6);

//5번핀이 송신, 4번핀이 수신핀이다.(솔)
//수신한 값을 e라는 변수에 저장한다.
CapacitiveSensor   e = CapacitiveSensor(5,4);

//3번핀이 송신, 2번핀이 수신핀이다.(라)
//수신한 값을 f라는 변수에 저장한다.
CapacitiveSensor   f = CapacitiveSensor(3,2);

//A0번핀이 송신, A1번핀이 수신핀이다.(시)
//수신한 값을 g라는 변수에 저장한다.
CapacitiveSensor   g = CapacitiveSensor(A0,A1);

//A2번핀이 송신, A3번핀이 수신핀이다.(높은 도)
//수신한 값을 h라는 변수에 저장한다.
CapacitiveSensor   h = CapacitiveSensor(A2, A3);

void setup() 
{
  Serial.begin(9600);    //시리얼통신을 시작한다. = 아두이노와 컴퓨터간 1:1통신을 시작한다. 
}

void loop() 
{
  //수신 한 a값은 200 이하의 값을 갖는데, 이를 ap라는 변수에 저장한다.
  long ap = a.capacitiveSensorRaw(200);   

  //수신 한 b값은 200 이하의 값을 갖는데, 이를 bp라는 변수에 저장한다.
  long bp = b.capacitiveSensorRaw(200);   

  //수신 한 c값은 200 이하의 값을 갖는데, 이를 cp라는 변수에 저장한다.
  long cp = c.capacitiveSensorRaw(200);   
  
  //수신 한 d값은 200 이하의 값을 갖는데, 이를 dp라는 변수에 저장한다.
  long dp = d.capacitiveSensorRaw(200); 
  
  //수신 한 e값은 200 이하의 값을 갖는데, 이를 ep라는 변수에 저장한다.
  long ep = e.capacitiveSensorRaw(200); 
  
  //수신 한 f값은 200 이하의 값을 갖는데, 이를 fp라는 변수에 저장한다.
  long fp = f.capacitiveSensorRaw(200); 
  
  //수신 한 g값은 200 이하의 값을 갖는데, 이를 gp라는 변수에 저장한다.
  long gp = g.capacitiveSensorRaw(200); 
  
  //수신 한 h값은 200 이하의 값을 갖는데, 이를 hp라는 변수에 저장한다.
  long hp = h.capacitiveSensorRaw(200); 

 //변수 ap~hp까지의 값을 시리얼 모니터에 출력한다 = 수신값을 확인하기 위한 과정이다.
  Serial.print(ap);   
  Serial.print(bp);
  Serial.print(cp);
  Serial.print(dp);
  Serial.print(ep);
  Serial.print(fp);
  Serial.print(gp);
  Serial.println(hp);

  //스피커는 A4핀에 연결되어있다.
  
  if(ap > 3)  //ap의 값이 3 이상이라면 = (낮은 도)건반에 터치를 했다면
  {
    tone(A4, 262, 100);    //스피커에 (낮은 도) 음계를 출력한다.
  }
  if(bp > 3)  //bp의 값이 3 이상이라면 = (레)건반에 터치를 했다면
  {
    tone(A4, 294, 100);       //스피커에 (레) 음계를 출력한다.
  }
  if(cp > 3)  //cp의 값이 3 이상이라면 = (미)건반에 터치를 했다면
  {
    tone(A4, 330, 100);       //스피커에 (미) 음계를 출력한다.//(미)의 값을 수신했다면 스피커에 (미) 음계를 출력한다.
  }
  if(dp > 3)  //dp의 값이 3 이상이라면 = (파)건반에 터치를 했다면
  {
    tone(A4, 349, 100);       //스피커에 (파) 음계를 출력한다.
  }
  if(ep > 3)  //ep의 값이 3 이상이라면 = (솔)건반에 터치를 했다면
  {
    tone(A4, 392, 100);      //스피커에 (솔) 음계를 출력한다.
  }
  if(fp > 3)  //fp의 값이 3 이상이라면 = (라)건반에 터치를 했다면
  {
    tone(A4, 440, 100);       //스피커에 (라) 음계를 출력한다.
  }
  if(gp > 3)  //gp의 값이 3 이상이라면 = (시)건반에 터치를 했다면
  {
    tone(A4, 494, 100);       //스피커에 (시) 음계를 출력한다.
  }
  if(hp > 3)  //hp의 값이 3 이상이라면 = (높은 도)건반에 터치를 했다면
  { 
    tone(A4, 523, 100);      //스피커에 (높은 도) 음계를 출력한다.
  }
}
