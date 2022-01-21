//Voltage = 11
#include <Arduino.h>
#include <TinyMPU6050.h>
#include <PID_v1.h>
#define PIN_OUTPUT 3
double Setpoint, Input, Output;
double Kp=24, Ki=0, Kd=0.02;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
MPU6050 mpu (Wire);
int M1A=7;
int M1B=8;
int M2A=12; 
int M2B=13;
int M1in=5; 
int M2in=6;
int mod = 0;
ISR(TIMER1_COMPA_vect) // timer compare interrupt serviceroutine
{
 // IamPID(algo);
}
void setup()
{
  mpu.Initialize();
//  Calibration
  Serial.begin(9600);
 //mpu.Calibrate();
 Serial.println("done");
  Input = double(mpu.GetAngX()+90.00);
  Setpoint = 90;
  myPID.SetMode(AUTOMATIC);
  //mpu.setGyroXOffset(90)
  myPID.SetSampleTime(0.025);     //set sample time
  myPID.SetOutputLimits(-200,200);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M1in, OUTPUT);
  pinMode(M2in, OUTPUT);

  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
/*
  TCCR1A =0;
  TCCR1B=0;
  TCCR1A =0;
  TCCR1B=10;
  OCR1A = 50;  //micros delay/0.5
  TIMSK1 =2;*/
  SetSampleT();
}
int tilt = 0;
void loop()
{
  IamPID2();
/*  if(mod == 0)
  {
    IamPID(); 
  }
  else
  {*/  
    //IamPID2();
  //}
}
