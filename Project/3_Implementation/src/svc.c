#define Trig 8
#define Echo 9


const int in21 = 4;    // L298N-2 pin 4
const int in22 = 5;    // L298N-2 pin 5
const int in23 = 6;    // L298N-2 pin 6
const int in24 = 7;    // L298N-2 pin 7
const int enA = 10;    // L298N-2 pin 10
const int enB = 11;    // L298N-2 pin 11

void setup() 
{  
  pinMode(Trig, OUTPUT);  
  pinMode(Echo, INPUT);  

    
  pinMode(in21, OUTPUT);      
  pinMode(in22, OUTPUT);      
  pinMode(in23, OUTPUT);      
  pinMode(in24, OUTPUT);      

} 
unsigned int impulseTime=0; 
unsigned int distance_sm=0; 

void loop() 
{  
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);
  impulseTime=pulseIn(Echo, HIGH);  
  distance_sm=impulseTime/58;  

  if (distance_sm>25)  
  {     

      digitalWrite(in21, LOW);
      digitalWrite(in22, HIGH);
      analogWrite(enA, 60);

      analogWrite(enB, 60);
      digitalWrite(in23, HIGH);
      digitalWrite(in24, LOW);
  }  
  else 
  {   

      digitalWrite(in21, HIGH);
      digitalWrite(in22, LOW);

      analogWrite(enA, 100);

      analogWrite(enB, 100);
      
      digitalWrite(in23, HIGH);
      digitalWrite(in24, LOW); 
    delay(1100); 

  }   

  delay(50); 
  
}