#include <IRremote.h> // thư viện hỗ trợ IR remote
#define ir 8
#define inA1 13
#define inA2 12
#define inB1 11
#define inB2 10

char t;
IRrecv irrecv(ir);
decode_results results;
 
void setup() {
irrecv.enableIRIn();
pinMode(inA1,OUTPUT);   
pinMode(inA2,OUTPUT);   
pinMode(inB1,OUTPUT);   
pinMode(inB2,OUTPUT);   

Serial.begin(9600);
 
}

void translateIR()
{
  switch(results.value)
  {
    case 0xFFA857: //Nhấn nút + thì tiến
    robotMove(1);
    break;
    case 0xFF6897: //Nhấn nút 0 thì dừng
    robotMove(0); 
    break;
    case 0xFFE01F: //Nhấn nút - thì lùi
    robotMove(2);
    break;
    case 0xFF02FD: //Nhấn nút >>| thì rẽ phải
    robotMove(3);
    break;
    case 0xFF22DD: //Nhấn nút |<< thì rẽ trái
    robotMove(4);
    break;
  }
}
void robotMove(int chedo)
{
  switch(chedo)
  {
    case 0: //Dừng
    motorMove(inA1,inA2,0);
    motorMove(inB1,inB2,0);
    break;
    case 1: //Tiến
    motorMove(inA1,inA2,1);
    motorMove(inB1,inB2,1);
    break;
    case 2: //Lùi
    motorMove(inA1,inA2,2);
    motorMove(inB1,inB2,2);
    break;
    case 3: //Rẽ phải
    motorMove(inA1,inA2,0);
    motorMove(inB1,inB2,1);
    break;
    case 4: //Rẽ trái
    motorMove(inA1,inA2,1);
    motorMove(inB1,inB2,0);
    break;
  }
}
void motorMove(int in1,int in2, byte action)
{
  switch(action)
  {
    case 0: //Dừng
    digitalWrite(in1,0);
    digitalWrite(in2,0);
    break;
    case 1: //Chiều thứ 1
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    break;
    case 2: //Chiều thứ 2
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    break;
  }
}


void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //Tiến
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'B'){      //Lùi
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
 
else if(t == 'L'){      //Rẽ phải
  digitalWrite(13,HIGH);
}
 
else if(t == 'R'){      //Rẻ trái
  digitalWrite(11,HIGH);
}

 
else if(t == 'S'){      //Dừng
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
delay(20);

if (irrecv.decode(&results))
 {
  translateIR();
  delay(200);
  irrecv.resume();
 }
}
