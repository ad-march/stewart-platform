#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {575,210,520,215,530,210,530};
int SERVOMEAN[] = {495,390,350,390,350,380,350};  //need to calibrate servo 0 drop location

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 40;
double current_angle [] = {0,0,0,0,0,0};
double target_angle [][servo_quantity] = {
{-3.33 , -2.86 , 2.79 , 3.28 , 0.49 , -0.48 }, 
{-6.73 , -5.79 , 5.51 , 6.52 , 0.98 , -0.96 }, 
{-10.20 , -8.81 , 8.18 , 9.73 , 1.47 , -1.43 }, 
{-13.76 , -11.93 , 10.80 , 12.92 , 1.97 , -1.90 }, 
{-17.43 , -15.14 , 13.37 , 16.08 , 2.47 , -2.36 }, 
{-13.76 , -11.93 , 10.80 , 12.92 , 1.97 , -1.90 }, 
{-10.20 , -8.81 , 8.18 , 9.73 , 1.47 , -1.43 }, 
{-6.73 , -5.79 , 5.51 , 6.52 , 0.98 , -0.96 }, 
{-3.33 , -2.86 , 2.79 , 3.28 , 0.49 , -0.48 }, 
{-0.00 , 0.00 , 0.00 , -0.00 , 0.00 , 0.00 }, 
{-1.36 , -2.19 , -2.19 , -1.36 , 3.50 , 3.50 }, 
{-2.75 , -4.40 , -4.40 , -2.75 , 6.93 , 6.93 }, 
{-4.16 , -6.61 , -6.61 , -4.16 , 10.31 , 10.31 }, 
{-5.60 , -8.83 , -8.83 , -5.60 , 13.64 , 13.64 }, 
{-7.07 , -11.07 , -11.07 , -7.07 , 16.94 , 16.94 }, 
{-5.60 , -8.83 , -8.83 , -5.60 , 13.64 , 13.64 }, 
{-4.16 , -6.61 , -6.61 , -4.16 , 10.31 , 10.31 }, 
{-2.75 , -4.40 , -4.40 , -2.75 , 6.93 , 6.93 }, 
{-1.36 , -2.19 , -2.19 , -1.36 , 3.50 , 3.50 }, 
{-0.00 , 0.00 , 0.00 , -0.00 , -0.00 , -0.00 }, 
{3.28 , 2.79 , -2.86 , -3.33 , -0.48 , 0.49 }, 
{6.52 , 5.51 , -5.79 , -6.73 , -0.96 , 0.98 }, 
{9.73 , 8.18 , -8.81 , -10.20 , -1.43 , 1.47 }, 
{12.92 , 10.80 , -11.93 , -13.76 , -1.90 , 1.97 }, 
{16.08 , 13.37 , -15.14 , -17.43 , -2.36 , 2.47 }, 
{12.92 , 10.80 , -11.93 , -13.76 , -1.90 , 1.97 }, 
{9.73 , 8.18 , -8.81 , -10.20 , -1.43 , 1.47 }, 
{6.52 , 5.51 , -5.79 , -6.73 , -0.96 , 0.98 }, 
{3.28 , 2.79 , -2.86 , -3.33 , -0.48 , 0.49 }, 
{-0.00 , 0.00 , 0.00 , -0.00 , -0.00 , -0.00 }, 
{-1.36 , -2.19 , -2.19 , -1.36 , 3.50 , 3.50 }, 
{-2.75 , -4.40 , -4.40 , -2.75 , 6.93 , 6.93 }, 
{-4.16 , -6.61 , -6.61 , -4.16 , 10.31 , 10.31 }, 
{-5.60 , -8.83 , -8.83 , -5.60 , 13.64 , 13.64 }, 
{-7.07 , -11.07 , -11.07 , -7.07 , 16.94 , 16.94 }, 
{-5.60 , -8.83 , -8.83 , -5.60 , 13.64 , 13.64 }, 
{-4.16 , -6.61 , -6.61 , -4.16 , 10.31 , 10.31 }, 
{-2.75 , -4.40 , -4.40 , -2.75 , 6.93 , 6.93 }, 
{-1.36 , -2.19 , -2.19 , -1.36 , 3.50 , 3.50 }, 
{-0.00 , 0.00 , 0.00 , -0.00 , -0.00 , -0.00 },  
};




void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

double tilt_angle[steps_quantity];
  for (int f = 0; f < steps_quantity; f++){
    tilt_angle[f]=SERVOMAX[0];  //initialize arry to zeros
  }

double pauses[steps_quantity];
  for (int d = 0; d < steps_quantity; d++){
    pauses[d]=0;  //initialize arry to zeros
  }

pauses[6]=1000;
pauses[11]=500;
pauses[16]=1000;
pauses[21]=500;
pauses[26]=1000;
pauses[31]=500;
pauses[36]=1000;


//pauses[6]=1000;   //must enter each location where a pause is required

double speed[steps_quantity];    //speed factor = number of degrees per step
  for (int e = 0; e < steps_quantity; e++){
    speed[e]=0.25;  //sets global speed factor
  }


  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a+1], SERVOMAX[a+1]);
    pwm.setPWM(a+1, 0, pulselen);
    Serial.flush();
  
  pwm.setPWM(0, 0, 550);
    Serial.flush();
    
  }

  delay(2500);

for (int b = 0; b < steps_quantity; b++){  

  //Finds servo having to move the most
  double max_diff = 0;
  int servonum_max;
  
    for (int i = 1; i < servo_quantity; i++) {  //start at i=1 since we do not want to consider top servo motion here
      double diff = abs(target_angle[b][i]-current_angle[i]);
      
      if (diff > max_diff){
        max_diff=diff;
        servonum_max = i;
      }
    }
  
  // Split into step sizes for same total move time
  double step_size [servo_quantity];
   for (int j = 0; j < servo_quantity; j++) {
    step_size[j] = speed[b]*(target_angle[b][j]-current_angle[j])/(max_diff+0.001); //+0.001 prevents divide by zero error
   }
  
  
  //makes stuff move

  
  if(current_angle[servonum_max]<target_angle[b][servonum_max]){
    
    while(current_angle[servonum_max] < target_angle[b][servonum_max]){
     
     for (int k = 0; k < servo_quantity; k++){
      
      current_angle[k] = current_angle[k] + step_size[k];
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k+1], SERVOMAX[k+1]);
      pwm.setPWM(k+1, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }
    }
  else {
    while(current_angle[servonum_max] > target_angle[b][servonum_max]){
     
     for (int k = 0; k < servo_quantity; k++){
      
      current_angle[k] = current_angle[k] + step_size[k];
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k+1], SERVOMAX[k+1]);
      pwm.setPWM(k+1, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }  
  }
//pwm.setPWM(0, 0, map (tilt_angle[b], 0, 80, SERVOMEAN[0], SERVOMAX[0]));
delay(pauses[b]);
} 
}

void loop() {}
