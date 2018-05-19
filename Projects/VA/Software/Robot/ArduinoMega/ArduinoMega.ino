// 28.11.2017
// v0.0
// Alex Krieg

/*
Toppic

-> robot/motL  0.1
-> robot/motR  0.1
-> robot/master command
<- robot/sens1 23
<- robot/sens2 23
<- robot/sens3 23
<- robot/sens4 23
<- robot/sens5 23
<- robot/sens6 23

*/

#include <Ultrasonic.h>
#include <L298N.h>
#include "Timer.h"

const int timeoutTime   = 1000;

//------------------------Motoren------------------

int enableMotorLeft     = 3;
int data1MotorLeft      = 37;
int data2MotorLeft      = 36;
int speedLeft           = 0;
boolean directionLeft   = true;

int enableMotorRight    = 2;
int data1MotorRight     = 39;
int data2MotorRight     = 38;
int speedRight          = 0;
boolean directionRight  = true;

L298N motorLeft(enableMotorLeft, data1MotorLeft, data2MotorLeft);
L298N motorRight(enableMotorRight, data1MotorRight, data2MotorRight);

float motorDataLeft     = 0.0;
float motorDataRight    = 0.0;
Timer timeout;
Timer driveTimer;
int driveTime           = 100;

//-------------------------------------------------

//------------------------Sendoren-----------------

int Sensor1Trigg = 42;
int Sensot1Ech   = 43;

int Sensor2Trigg = 44;
int Sensot2Ech   = 45;

int Sensor3Trigg = 46;
int Sensot3Ech   = 47;

int Sensor4Trigg = 48;
int Sensot4Ech   = 49;

int Sensor5Trigg = 50;
int Sensot5Ech   = 51;

int Sensor6Trigg = 52;
int Sensot6Ech   = 53;

Ultrasonic sensor1(Sensor1Trigg, Sensot1Ech);
Ultrasonic sensor2(Sensor2Trigg, Sensot2Ech);
Ultrasonic sensor3(Sensor3Trigg, Sensot3Ech);
Ultrasonic sensor4(Sensor4Trigg, Sensot4Ech);
Ultrasonic sensor5(Sensor5Trigg, Sensot5Ech);
Ultrasonic sensor6(Sensor6Trigg, Sensot6Ech);

Timer sensorTimer;

//--------------------------------------------------

boolean sendData = false;
boolean enableMotor = false;








void setup()
{
  Serial.begin(19200);
  Serial1.begin(19200);
  
}

void loop()
{
  checkMQTT();
  if (Serial.available()>0) {
    String _buffer = Serial.readStringUntil('\n');
    Serial1.print(_buffer);
  }
  if(sendData)
  {
    if(sensorTimer.start(100))
    {
      float cm1 = sensor1.convert(sensor1.timing(10000),Ultrasonic::CM);
      float cm2 = sensor1.convert(sensor2.timing(10000),Ultrasonic::CM);
      float cm3 = sensor1.convert(sensor3.timing(10000),Ultrasonic::CM);
      float cm4 = sensor1.convert(sensor4.timing(10000),Ultrasonic::CM);
      float cm5 = sensor1.convert(sensor5.timing(10000),Ultrasonic::CM);
      float cm6 = sensor1.convert(sensor6.timing(10000),Ultrasonic::CM);
      float setNumber = 300;
      if(cm1 == 0){cm1 = setNumber;}    
      if(cm2 == 0){cm2 = setNumber;}   
      if(cm3 == 0){cm3 = setNumber;}   
      if(cm4 == 0){cm4 = setNumber;}   
      if(cm5 == 0){cm5 = setNumber;}   
      if(cm6 == 0){cm6 = setNumber;}   
      
      int __delay = 0;
      Serial1.print(("robot/sens1||"+(String)cm1+'\n').c_str());
      delay(__delay);
      Serial1.print(("robot/sens2||"+(String)cm2+'\n').c_str());
       delay(__delay);
      Serial1.print(("robot/sens3||"+(String)cm3+'\n').c_str());
       delay(__delay);
      Serial1.print(("robot/sens4||"+(String)cm4+'\n').c_str());
       delay(__delay);
      Serial1.print(("robot/sens5||"+(String)cm5+'\n').c_str());
       delay(__delay);
      Serial1.print(("robot/sens6||"+(String)cm6+'\n').c_str());
      delay(__delay);
     /* Serial.print(("robot/sens1||"+(String)cm1+'\n').c_str());
      delay(__delay);
      Serial.print(("robot/sens2||"+(String)cm2+'\n').c_str());
       delay(__delay);
      Serial.print(("robot/sens3||"+(String)cm3+'\n').c_str());
       delay(__delay);
      Serial.print(("robot/sens4||"+(String)cm4+'\n').c_str());
       delay(__delay);
      Serial.print(("robot/sens5||"+(String)cm5+'\n').c_str());
       delay(__delay);
       Serial.print(("robot/sens6||"+(String)cm6+'\n').c_str());*/
    }
  }
  checkMQTT();
  if(enableMotor)
  {
    if(timeout.start(timeoutTime))
    {
      enableMotor = false;
    }
  }
  if(enableMotor)
  {
    
    if(motorDataLeft <0)
    {
      if(motorDataLeft < -1.0){motorDataLeft = -1.0;}
      speedLeft     = map(abs(motorDataLeft*1000),0,1000,0,255);
      directionLeft = false;
    }
    else
    {
      if(motorDataLeft > 1.0){motorDataLeft = 1.0;}
      speedLeft     = map(motorDataLeft*1000,0,1000,0,255);
      directionLeft = true;
    }
    if(motorDataRight <0)
    {
      if(motorDataRight < -1.0){motorDataRight = -1.0;}
      speedRight     = map(abs(motorDataRight*1000),0,1000,0,255);
      directionRight = false;
    }
    else
    {
      if(motorDataRight > 1.0){motorDataRight = 1.0;}
      speedRight     = map(motorDataRight*1000,0,1000,0,255);
      directionRight = true;
    }
  }
  else
  {
    speedLeft       = 0;
    speedRight      = 0;
    directionLeft   = true;
    directionRight  = true;
    motorDataLeft   = 0.0;
    motorDataRight  = 0.0;
    
  }
  motor();
  if(driveTimer.start(driveTime))
  {
    speedLeft   = 0;
    speedRight  = 0;
  }
}
void motor()
{
  motorLeft.setSpeed(speedLeft);
  motorRight.setSpeed(speedRight);
  if(directionLeft){motorLeft.forward();}else{motorLeft.backward();}
  if(directionRight){motorRight.forward();}else{motorRight.backward();}
}
void checkMQTT()
{
  if (Serial1.available()>0) {
    String _buffer = Serial1.readStringUntil('\n');
    //Serial.println(_buffer);
    if(_buffer.indexOf("||") != -1)
    {
      String toppic  = _buffer.substring(0,_buffer.indexOf("||")); 
      String message = _buffer.substring(_buffer.indexOf("||")+2);
      //Serial.println("message: \""+message+"\"");
      if(toppic == "robot/master")
      {
       // Serial.println(message);
       toppicMaster(message); 
      }
      if(toppic == "robot/motL")
      {
       toppicMotorLeft(message); 
      }
      if(toppic == "robot/motR")
      {
       toppicMotorRight(message); 
      }
    }
  }
}
void toppicMaster(String message)
{
   if(message == "send1")//Erlauben, dass die Sensor Werte gesendet werden
   {
     sendData = true;
   }
   if(message == "send0")//Nicht erlauben, dass die Sensor Werte gesendet werden
   {
     sendData = false;
   }
   if(message == "motor1")//Erlauben, dass Motoren angesteuert werden dürfen
   {
     enableMotor = true;
   }
   if(message == "motor0")//Nicht erlauben, dass Motoren angesteuert werden dürfen
   {
     enableMotor = false;
   }
}
void toppicMotorLeft(String message)
{
  timeout.stop();
  motorDataLeft = message.toFloat();
}
void toppicMotorRight(String message)
{
  timeout.stop();
  motorDataRight = message.toFloat();
}
