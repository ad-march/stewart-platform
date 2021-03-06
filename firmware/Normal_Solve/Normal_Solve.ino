#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {440,210,530,215,530,210,530};
int SERVOMEAN[] = {585,390,350,370,350,370,360};  //need to calibrate servo 0 drop location

int servonum = 0;
const int servo_quantity = 7;
const int steps_quantity = 48;
double current_angle [] = {0,0,0,0,0,0,0};
double target_angle [][servo_quantity - 1] = {
{-2.68 , -1.99 , 3.30 , 3.48 , -0.65 , -1.57 }, 
{-5.39 , -4.02 , 6.52 , 6.90 , -1.31 , -3.13 }, 
{-8.14 , -6.10 , 9.69 , 10.28 , -1.98 , -4.69 }, 
{-10.91 , -8.23 , 12.81 , 13.62 , -2.66 , -6.25 }, 
{-13.73 , -10.40 , 15.90 , 16.93 , -3.34 , -7.80 }, 
{-16.59 , -12.63 , 18.95 , 20.23 , -4.04 , -9.35 }, 
{-19.51 , -14.90 , 21.99 , 23.53 , -4.74 , -10.89 }, 
{-22.49 , -17.23 , 25.01 , 26.84 , -5.45 , -12.43 }, 
{-22.53 , -18.18 , 20.63 , 23.55 , -1.20 , -7.44 }, 
{-22.49 , -19.07 , 16.27 , 20.23 , 2.89 , -2.61 }, 
{-22.38 , -19.90 , 11.90 , 16.85 , 6.86 , 2.09 }, 
{-22.19 , -20.67 , 7.50 , 13.41 , 10.72 , 6.69 }, 
{-21.94 , -21.37 , 3.04 , 9.89 , 14.49 , 11.22 }, 
{-21.62 , -22.00 , -1.48 , 6.27 , 18.20 , 15.71 }, 
{-21.24 , -22.55 , -6.11 , 2.53 , 21.85 , 20.17 }, 
{-20.80 , -23.03 , -10.85 , -1.32 , 25.46 , 24.65 }, 
{-18.82 , -20.22 , -7.95 , 0.51 , 21.37 , 20.56 }, 
{-16.86 , -17.44 , -5.07 , 2.30 , 17.27 , 16.47 }, 
{-14.93 , -14.68 , -2.21 , 4.04 , 13.15 , 12.33 }, 
{-13.02 , -11.93 , 0.64 , 5.74 , 8.98 , 8.14 }, 
{-11.14 , -9.21 , 3.46 , 7.39 , 4.73 , 3.86 }, 
{-9.30 , -6.50 , 6.28 , 9.00 , 0.39 , -0.53 }, 
{-7.48 , -3.81 , 9.08 , 10.55 , -4.07 , -5.06 }, 
{-5.70 , -1.12 , 11.88 , 12.07 , -8.68 , -9.76 }, 
{-1.47 , 2.43 , 8.65 , 8.10 , -9.30 , -9.36 }, 
{2.69 , 5.89 , 5.34 , 4.09 , -9.89 , -8.94 }, 
{6.77 , 9.25 , 1.95 , 0.01 , -10.45 , -8.49 }, 
{10.80 , 12.53 , -1.54 , -4.14 , -10.99 , -8.01 }, 
{14.80 , 15.74 , -5.14 , -8.40 , -11.49 , -7.51 }, 
{18.78 , 18.90 , -8.86 , -12.78 , -11.97 , -6.99 }, 
{22.76 , 22.02 , -12.73 , -17.32 , -12.41 , -6.45 }, 
{26.77 , 25.11 , -16.76 , -22.06 , -12.82 , -5.89 }, 
{24.13 , 22.15 , -16.21 , -20.87 , -10.19 , -3.88 }, 
{21.49 , 19.20 , -15.65 , -19.67 , -7.60 , -1.92 }, 
{18.84 , 16.24 , -15.08 , -18.45 , -5.05 , 0.01 }, 
{16.17 , 13.28 , -14.50 , -17.22 , -2.52 , 1.90 }, 
{13.47 , 10.29 , -13.92 , -15.97 , -0.01 , 3.75 }, 
{10.75 , 7.29 , -13.32 , -14.72 , 2.47 , 5.57 }, 
{7.99 , 4.24 , -12.72 , -13.45 , 4.93 , 7.35 }, 
{5.18 , 1.16 , -12.12 , -12.18 , 7.38 , 9.11 }, 
{4.58 , 0.99 , -10.42 , -10.59 , 6.48 , 7.86 }, 
{3.99 , 0.81 , -8.75 , -9.02 , 5.58 , 6.62 }, 
{3.39 , 0.64 , -7.10 , -7.47 , 4.66 , 5.37 }, 
{2.80 , 0.46 , -5.47 , -5.94 , 3.73 , 4.12 }, 
{2.20 , 0.29 , -3.85 , -4.44 , 2.80 , 2.86 }, 
{1.61 , 0.11 , -2.26 , -2.95 , 1.85 , 1.60 }, 
{1.02 , -0.07 , -0.68 , -1.48 , 0.90 , 0.33 }, 
{0.42 , -0.25 , 0.89 , -0.03 , -0.06 , -0.94 },          
};




void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pinMode(53, INPUT);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

double tilt_angle[steps_quantity];
  for (int f = 0; f < steps_quantity; f++){
    tilt_angle[f]=0;  //initialize arry to zeros
  }

/*
tilt_angle[3]=20;
tilt_angle[4]=40;
tilt_angle[5]=60;
tilt_angle[6]=70;
tilt_angle[7]=80;

  for (int f = 8; f < steps_quantity; f++){
    tilt_angle[f]=100;  //initialize array to zeros
  }
*/

double pauses[steps_quantity];
  for (int d = 0; d < steps_quantity; d++){
    pauses[d]=0;  //initialize arry to zeros
  }
  
  for (int d = 0; d < steps_quantity; d=d+8){
    pauses[d]=400;  //pauses every 4 moves
  }


pauses[0]=5000;
pauses[16]=700;
pauses[24]=0;
pauses[32]=1000;

//pauses[11]=2000;   //must enter each location where a pause is required

double speed[steps_quantity];    //speed factor = number of degrees per step
  for (int e = 0; e < steps_quantity; e++){
    speed[e]=1;  //sets global speed factor
  }

  //for (int e = 8; e < steps_quantity; e++){
   // speed[e]=0.5;  //sets global speed factor
  //}



  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a], SERVOMAX[a]);
    pwm.setPWM(a, 0, pulselen);
    Serial.flush();
    
  }


for (int b = 0; b < steps_quantity; b++){  

/*
  if(b=0){    //Wait for switch
    while(digitalRead(53)==LOW){
      delay(10);
    }
  }
*/

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
