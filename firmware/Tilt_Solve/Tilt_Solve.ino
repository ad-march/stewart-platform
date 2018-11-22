#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {410,225,410,240,415,230};
int SERVOMAX[] = {210,520,215,530,210,530};
int SERVOMEAN[] = {390,350,390,350,380,350};  //need to calibrate servo 0 drop location

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 13;
//double tilt_angle[];
double current_angle [] = {0,0,0,0,0,0};
double target_angle [][servo_quantity] = {{-2.876305152,-5.028024071,-5.978480785,-4.031793332,8.546862028,8.701244442,},
                                          {-5.875942145,-10.0872343,-12.06476658,-8.265003037,16.76852736,17.10373608},
                                          {-8.987362856,-15.18078027,-18.29754001,-12.69771655,24.84846471,25.39864626},
                                          {-12.19560449,-20.31251615,-24.7311411,-17.32320941,32.98501674,33.7959864},
                                          {-15.48147183,-25.48750517,-31.44905169,-22.12787358,41.44064757,42.58160846},
                                          {-18.82067943,-30.71290372,-38.59372112,-27.08855944,50.65447697,52.2542404},
                                          {-15.48147183,-25.48750517,-31.44905169,-22.12787358,41.44064757,42.58160846},                                          
                                          {-12.19560449,-20.31251615,-24.7311411,-17.32320941,32.98501674,33.7959864},
                                          {-8.987362856,-15.18078027,-18.29754001,-12.69771655,24.84846471,25.39864626},
                                          {-5.875942145,-10.0872343,-12.06476658,-8.265003037,16.76852736,17.10373608},
                                          {-2.876305152,-5.028024071,-5.978480785,-4.031793332,8.546862028,8.701244442},
                                          {0,0,0,0,0,0}};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

double pauses[steps_quantity];
  for (int d = 0; d < steps_quantity; d++){
    pauses[d]=0;  //initialize arry to zeros
  }

//pauses[6]=1000;   //must enter each location where a pause is required

double speed[steps_quantity];    //speed factor = number of degrees per step
  for (int e = 0; e < steps_quantity; e++){
    speed[e]=0.25;  //sets global speed factor
  }


  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a], SERVOMAX[a]);
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
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k], SERVOMAX[k]);
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
      double pulselen = map (current_angle[k], 0, 80, SERVOMEAN[k], SERVOMAX[k]);
      pwm.setPWM(k+1, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }  
  }
delay(pauses[b]);
} 
}

void loop() {}
