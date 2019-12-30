#include <Servo.h>;
Servo myservo;
long duration, inches, cm, dist1 , dist2 , a;  //  function from datasheet of ultrasonic sensor
int set_length=4;
int servopin=9;

int LeftMotorForward = 7; 
int LeftMotorReverse = 6; 

int RightMotorForward = 5; 
int RightMotorReverse = 4; 

int trigPin =3;
int echoPin =2;

void off()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorReverse, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorReverse, LOW);
  delay(500);
  //return;
}

void setup()
{
  Serial.begin(9600);
  myservo.attach(servopin);
  pinMode(LeftMotorForward, OUTPUT);  
  pinMode(RightMotorForward, OUTPUT);  
  pinMode(LeftMotorReverse, OUTPUT);  
  pinMode(RightMotorReverse, OUTPUT);  
  pinMode(echoPin,INPUT);
  pinMode(7, OUTPUT); 
  pinMode(5, OUTPUT);
  analogWrite(7, 255); // Faster motor at 100% of its full speed
  analogWrite(5, 255); // Slower motor at 100% of its full speed
  delay(1000);
}
int ultra()
{
  //long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
    //pinMode(echoPin,INPUT);
  duration = pulseIn(echoPin, HIGH);
  

  inches = microsecondsToInches(duration);
  cm=microsecondsToCentimeters(duration);
  //delay
 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
  return round(inches);
}

void loop(){
  Driveforward();  // if nothing is wrong the go forward.
  int distance = ultra(); // us the ultra() function to see if anything is ahead.
  if (distance<= set_length){
    Reverse(); // If something is ahead, move back
    char turndirection = scan(); //Decide which direction to turn.
    switch (turndirection){
      case 'l':
        Leftturn();
        break;
      case 'r':
        Rightturn();
        break;
    }
  }
} 
  /* if(inches<=set_length) // if there is obstacle at 15 inches or below
 {
 Reverse(); 
Rightturn();
dist1=microsecondsToInches(a);
Leftcheck();
dist2=microsecondsToInches(a);
Rightturn();
if(dist1>dist2)
 {
  Rightturn();
  off();
 }
 if(dist1<dist2)
  {
  Leftturn();
  off();
  }
}
  else
  { 
  Driveforward();
  }
}*/
 
long microsecondsToInches(long microseconds)
{
return a=microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
 return microseconds / 29 / 2;
}

 void Reverse(){
  digitalWrite(RightMotorForward, LOW); 
  digitalWrite(RightMotorReverse, HIGH); 
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorReverse, HIGH);
  delay(2000);
  off();
  //return;
}
 void Rightturn(){
 digitalWrite(RightMotorForward, LOW );
 digitalWrite(LeftMotorForward, HIGH);
 digitalWrite(LeftMotorReverse, LOW );
 digitalWrite(RightMotorReverse, HIGH );
 delay(1500);
  off();
  //return;
 }
 
 void Leftturn(){
   digitalWrite(RightMotorForward, HIGH );
   digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorReverse, HIGH );
   digitalWrite(RightMotorReverse, LOW );
   delay(1250);
  off();
  //return;
 }
 
 void Leftcheck(){
   digitalWrite(RightMotorForward, HIGH );
   digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorReverse, HIGH );
   digitalWrite(RightMotorReverse, LOW );
   delay(8500);
   off();
   return;
 }

void Driveforward(){
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(RightMotorReverse, LOW);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(LeftMotorReverse, LOW);
delay(500);
//off();
//return;
   }

char scan(){
  int leftscanval, rightscanval;
  char choice;  
  myservo.writeMicroseconds(600);
  delay(1000);                           //  //Look left
  leftscanval = ultra();
  
  myservo.write(2500);
  delay(1000);                            //  //Look right
  rightscanval = ultra();
 
   myservo.writeMicroseconds(1500);
  delay(1000);
  myservo.detach();
  myservo.attach(9);
  
  if (leftscanval>rightscanval){
    choice = 'l';
  }
  if (rightscanval>leftscanval){
    choice = 'r';
  } 
  Serial.print("Choice:  ");
  Serial.println(choice);
  return choice;
}
   
