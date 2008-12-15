

void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop(){
  if(Serial.available() > 0){
     int inByte = Serial.read();
     punchMe(inByte);
     Serial.println(inByte);
  }
  
  
}

void punchMe(int number){
  int oneOut = 2;
  int oneIn = 3;
  
  int twoOut = 5; 
  int twoIn = 4;
  
  int threeOut = 6;
  int threeIn = 7;

  int punchDelay = 1000;
  
  
  if(number == 49){
    toggle(oneOut);
    delay(punchDelay * 3.0);
    toggle(oneIn);
    //delay(punchDelay * 3.0);
  }
   
   if(number == 50){
    toggle(twoOut);
    delay(punchDelay * 3.0 );
    toggle(twoIn);
    //delay(punchDelay * 3.0 );
  }
  
  if(number == 51){
    toggle(threeOut);
    delay(punchDelay * 1.43);
    toggle(threeIn);
    //delay(punchDelay * 1.43);
  }
  
}

void toggle(int pin){
  digitalWrite(13, HIGH);
   digitalWrite(pin, HIGH);
   delay(50); 
   digitalWrite(pin, LOW);
   digitalWrite(13, LOW);
   //debugging
     //digitalWrite(13, HIGH);
     //delay(10);
     //digitalWrite(13, LOW);
}
