#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {440,210,530,215,530,210,530};
int SERVOMEAN[] = {585,390,350,370,350,370,360};  //need to calibrate servo 0 drop location

int servonum = 0;
const int servo_quantity = 7;
const int steps_quantity = 12;
double current_angle [] = {0,0,0,0,0,0,0};
double target_angle [][servo_quantity - 1] = {
{1.24 , 1.05 , -1.06 , -1.24 , -0.18 , 0.18 }, 
{2.47 , 2.10 , -2.14 , -2.50 , -0.36 , 0.37 }, 
{3.69 , 3.13 , -3.22 , -3.76 , -0.54 , 0.55 }, 
{4.91 , 4.16 , -4.31 , -5.02 , -0.72 , 0.73 }, 
{3.31 , 1.43 , -7.09 , -6.86 , 3.66 , 5.08 }, 
{1.67 , -1.32 , -9.88 , -8.74 , 7.94 , 9.32 }, 
{-0.01 , -4.08 , -12.70 , -10.65 , 12.13 , 13.50 }, 
{-1.73 , -6.85 , -15.53 , -12.60 , 16.27 , 17.62 }, 
{-6.82 , -11.43 , -20.72 , -18.19 , 7.50 , 8.88 }, 
{-12.14 , -16.21 , -26.24 , -24.18 , -1.55 , -0.11 }, 
{-17.79 , -21.25 , -32.21 , -30.74 , -11.20 , -9.64 }, 
{-23.87 , -26.61 , -38.81 , -38.12 , -21.89 , -20.12 },   
};




void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

double tilt_angle[steps_quantity];
  for (int f = 0; f < steps_quantity; f++){
    tilt_angle[f]=0;  //initialize arry to zeros
  }

tilt_angle[3]=20;
tilt_angle[4]=40;
tilt_angle[5]=60;
tilt_angle[6]=70;
tilt_angle[7]=80;

  for (int f = 8; f < steps_quantity; f++){
    tilt_angle[f]=100;  //initialize array to zeros
  }

double pauses[steps_quantity];
  for (int d = 0; d < steps_quantity; d++){
    pauses[d]=0;  //initialize arry to zeros
  }

pauses[0]=4000;
pauses[6]=200;

//pauses[11]=2000;   //must enter each location where a pause is required

double speed[steps_quantity];    //speed factor = number of degrees per step
  for (int e = 0; e < steps_quantity; e++){
    speed[e]=0.20;  //sets global speed factor
  }

  for (int e = 8; e < steps_quantity; e++){
    speed[e]=0.5;  //sets global speed factor
  }



  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a], SERVOMAX[a]);
    pwm.setPWM(a, 0, pulselen);
    Serial.flush();
    
  }


for (int b = 0; b < steps_quantity; b++){  

  //Finds servo having to move the most
  double max_diff = 0;
  int servonum_max;
  
    for (int i = 1; i < servo_quantity; i++) {  //start at i=1 since we do not want to consider top servo motion here
      double diff = abs(target_angle[b][i-1]-current_angle[i]);
      
      if (diff > max_diff){
        max_diff=diff;
        servonum_max = i;
      }
    }
  
  // Split into step sizes for same total move time
  double step_size [servo_quantity+1];
   for (int j = 0; j < servo_quantity; j++) {
    if(j==0){
      step_size[j] = speed[b]*(tilt_angle[b]-current_angle[j])/(max_diff+0.001);
    }
    else{
      step_size[j] = speed[b]*(target_angle[b][j-1]-current_angle[j])/(max_diff+0.001);//+0.001 prevents divide by zero error
    }
   }
  
  
  //makes stuff move

  
  if(current_angle[servonum_max]<target_angle[b][servonum_max-1]){
    
    while(current_angle[servonum_max] < target_angle[b][servonum_max-1]){


     
     for (int k = 0; k < servo_quantity; k++){
      
      current_angle[k] = current_angle[k] + step_size[k];
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k], SERVOMAX[k]);
      pwm.setPWM(k, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }
    }
  else {
    while(current_angle[servonum_max] > target_angle[b][servonum_max-1]){
     
     for (int k = 0; k < servo_quantity; k++){
      
      current_angle[k] = current_angle[k] + step_size[k];
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k], SERVOMAX[k]);
      pwm.setPWM(k, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }  
  }
delay(pauses[b]);
//pwm.setPWM(0, 0, map (tilt_angle[b], 0, 100, SERVOMAX[0], SERVOMEAN[0]));

} 
}

void loop() {}
