unsigned long currentTime, previousTime;
double passedTime;
double error;
double lastError;
double cumError, rateError,lastInput,rateInput, intTerm;
double SampleTime = 0.025;  // in ms
void IamPID2()
{
  
   currentTime = millis();                // current time
   //passedTime = double((currentTime - previousTime));        //time elapsed from previous computation
   passedTime = (double)(currentTime - previousTime);        //time elapsed from previous computation   

   if(passedTime>=SampleTime) //Sample time implementation
   {
    
    ///////        Pre PID Processing       ////////////////////////////////////////////////////////////
       mpu.Execute();
  Input = double(mpu.GetAngX()+90.00);
  //Serial.println("hello");
      Input +=3;
     //Serial.println(Input);
 
  if(Input>double(90))
    {
      //Input = double(double(180)-Input);
      //Input = -1*Input;
      tilt =-1;
    }
    else
    {
      tilt=1;
    }
    if(Input<double(92) & Input>double(88))
    {
      Stop();
    }
    else
      {
        //Serial.println(Input);

     ////////////// PID Implementation  //////////////////////////////////////////////////////////
     error = Setpoint - Input;                                //error
     /////  CHECK THIS FOR NEGATIVE ERROR???
     cumError += error;                // integral
     //rateError = (error - lastError);   // derivative
     rateInput = Input - lastInput;       //To fix derivative kick    

     // INtegral Windup below
     intTerm = Ki*cumError;
     if(intTerm> 200) 
      intTerm= 255;
     else if(intTerm< -200) 
      intTerm= -255;
     
     
     Output = Kp*error + intTerm - Kd*rateInput;                //PID output          
     if(Output> 200) 
      Output= 200;
     else if(Output< -200) 
      Output= -200; 
          
     lastError = error;                                //current error for future derivative
     previousTime = currentTime;   
     lastInput = Input;       
      
     /////////       POST PID     /////////////////
      
      //analogWrite(PIN_OUTPUT, Output);
      Serial.println(Output);
    //  Serial.println(myPID.GetDirection());
      //Serial.println(tilt);
    
    if(Output<0)
      Output=-1*Output;
    
      if(tilt == -1)
      {
         moveForward(Output);
      }
      else
      {
        moveBackward(Output);
      }
    }
    
  }
}
void SetSampleT()
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
   Ki = Ki * SampleTimeInSec;
   Kd = Kd / SampleTimeInSec;
}
