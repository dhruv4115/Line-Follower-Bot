//Define IR sensors pins
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

//Define ultrasonic sensors pins
#define trigPin1 9
#define echoPin1 3

//Define motor control pins 
#define leftMotorFwd 5
#define leftMotorBwd 6
#define rightMotorFwd 11
#define rightMotorBwd 10

//Define variables
int distance1 = 0;
int distance2 = 0;
int IR1_val = 0;
int IR2_val = 0;
int IR3_val = 0;
int IR4_val = 0;
int IR5_val = 0;
int threshold = 500;
int speed = 40;
int state = 0;
long duration;
int distance;



void setup() {
  // put your setup code here, to run once:
  //  Initialize IR sensors
pinMode(IR1,INPUT);
pinMode(IR2,INPUT);
pinMode(IR3,INPUT);
pinMode(IR4,INPUT);
pinMode(IR5,INPUT);

//Initialize ultrasonic sensors
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);

//Initialize motor control pins
pinMode(leftMotorFwd, OUTPUT);
pinMode(leftMotorBwd, OUTPUT);
pinMode(rightMotorFwd, OUTPUT);
pinMode(rightMotorBwd, OUTPUT);

//Initialize Serial communication
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Read IR sensor values
int  I1 = digitalRead(IR1);
int  I2 = digitalRead(IR2);
int  I3 = digitalRead(IR3);
int  I4 = digitalRead(IR4);
int  I5 = digitalRead(IR5);

//  Read ultrasonic sensor values
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  int distance1 = (duration1 / 2) * 0.034;

  //stop on ultrasonic value
  if(distance1 < 15){
  //  Stop
   analogWrite(leftMotorFwd,0);
   analogWrite(leftMotorBwd,0);
   analogWrite(rightMotorFwd,0);
   analogWrite(rightMotorBwd,0);
}

  //  Follow line
  if(I1==1 && I2==1 && I3==1 && I4==1 && I5==1){
  //  Move forward
    analogWrite(leftMotorFwd,40);
    analogWrite(leftMotorBwd,0);
    analogWrite(rightMotorFwd,0);
    analogWrite(rightMotorBwd,50);
  }else if(I1==1 && I2==1 && I3==0 && I4==1 && I5==1){
  //  Move forward
    analogWrite(leftMotorFwd,0);
    analogWrite(leftMotorBwd,40);
    analogWrite(rightMotorFwd,50);
    analogWrite(rightMotorBwd,0);
}else if((I1==1 && I2==1 && I3==0 && (I4==0 || I5==0)) || (I1==1 && I2==1 && I3== 1&& (I4==0|| I5==0))){
  //    Turn right
    analogWrite(leftMotorFwd,0);
    analogWrite(leftMotorBwd,60);
    analogWrite(rightMotorFwd,30); 
    analogWrite(rightMotorBwd,0);
}else if(((I1==0 || I2==0) && I3==0 && I4==1 && I5==1) || ((I1==0 || I2==0) && I3==1 && I4==1 && I5==1)){
  //    Turn left
    analogWrite(leftMotorFwd,30);
    analogWrite(leftMotorBwd,0);
    analogWrite(rightMotorFwd,0); 
    analogWrite(rightMotorBwd,60);
}else if(I1==0 && I2==0 && I3==0 && I4==0 && I5==0){
//  turn left
  analogWrite(leftMotorFwd,40);
  analogWrite(leftMotorBwd,0);
  analogWrite(rightMotorFwd,0);
  analogWrite(rightMotorBwd,50);
}else if(I1==1 && I2==1 && I3==0 && I4==0 && I5==0){
  //  Move forward
    analogWrite(leftMotorFwd,0);
    analogWrite(leftMotorBwd,40);
    analogWrite(rightMotorFwd,40);
    analogWrite(rightMotorBwd,0);
}else if(I1==0 && I2==0 && I3==1 && I4==0 && I5==0){
  //  turn left
  analogWrite(leftMotorFwd,40);
  analogWrite(leftMotorBwd,0);
  analogWrite(rightMotorFwd,0);
  analogWrite(rightMotorBwd,50);
}
delay(10);

}
