#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {575,210,520,215,530,210,530};
int SERVOMEAN[] = {445,390,350,390,350,430,330};  //need to calibrate servo 0 drop location

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 16;
double current_angle [] = {0,0,0,0,0,0};
double target_angle [][servo_quantity] = {
{1.65 , 1.40 , -1.42 , -1.66 , -0.24 , 0.24 }, 
{3.28 , 2.79 , -2.86 , -3.33 , -0.48 , 0.49 }, 
{4.91 , 4.16 , -4.31 , -5.02 , -0.72 , 0.73 }, 
{6.52 , 5.51 , -5.79 , -6.73 , -0.96 , 0.98 }, 
{8.13 , 6.85 , -7.29 , -8.46 , -1.20 , 1.23 }, 
{5.02 , 1.38 , -12.93 , -12.37 , 7.48 , 9.80 }, 
{1.74 , -4.15 , -18.66 , -16.43 , 15.83 , 18.08 }, 
{-1.72 , -9.74 , -24.52 , -20.61 , 24.02 , 26.26 }, 
{-5.34 , -15.42 , -30.56 , -24.88 , 32.26 , 34.56 }, 
{-9.13 , -21.21 , -36.83 , -29.21 , 40.81 , 43.26 }, 
{-4.60 , -14.28 , -29.33 , -24.02 , 30.60 , 32.88 }, 
{-0.31 , -7.50 , -22.16 , -18.93 , 20.75 , 22.99 }, 
{3.73 , -0.83 , -15.21 , -13.98 , 10.85 , 13.13 }, 
{7.52 , 5.76 , -8.41 , -9.23 , 0.57 , 2.97 }, 
{11.07 , 12.29 , -1.73 , -4.70 , -10.43 , -7.83 },  
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

tilt_angle[5]=40;
tilt_angle[6]=80;
tilt_angle[7]=90;
tilt_angle[8]=95;
tilt_angle[9]=100;

  for (int f = 10; f < steps_quantity; f++){
    tilt_angle[f]=120;  //initialize arry to zeros
  }

double pauses[steps_quantity];
  for (int d = 0; d < steps_quantity; d++){
    pauses[d]=75;  //initialize arry to zeros
  }

pauses[0]=4000;
pauses[6]=100;
pauses[7]=175;
pauses[8]=175;
pauses[9]=175;

//pauses[11]=2000;   //must enter each location where a pause is required

double speed[steps_quantity];    //speed factor = number of degrees per step
  for (int e = 0; e < steps_quantity; e++){
    speed[e]=0.5;  //sets global speed factor
  }


  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a+1], SERVOMAX[a+1]);
    pwm.setPWM(a+1, 0, pulselen);
    Serial.flush();
  
  pwm.setPWM(0, 0, SERVOMAX[0]);
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
delay(pauses[b]);
pwm.setPWM(0, 0, map (tilt_angle[b], 0, 100, SERVOMAX[0], SERVOMEAN[0]));

} 
}

void loop() {}
