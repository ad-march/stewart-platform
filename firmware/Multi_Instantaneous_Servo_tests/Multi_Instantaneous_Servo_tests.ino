#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
#define SERVOMIN  132
#define SERVOMAX  535

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 3;
double speed = 0.5;
double current_angle [] = {150,150,150,535,535,535};
double target_angle [][servo_quantity] = {{250, 500, 490, 400, 200, 300},
                                          {210, 400, 150, 400, 500, 425},
                                          {500, 300, 350, 500, 300, 350}};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  for (int a = 0; a < servo_quantity; a++){
    pwm.setPWM(a, 0, current_angle[a]);
    Serial.flush();
  }

  delay(500);
}

void loop() {

for (int b = 0; b < steps_quantity; b++){  

  //Finds servo having to move the most
  double max_diff = 0;
  int servonum_max;
    
    for (int i = 0; i < servo_quantity; i++) {
      double diff = abs(target_angle[b][i]-current_angle[i]);
      
      if (diff > max_diff){
        max_diff=diff;
        servonum_max = i;
      }
    }
  
  // Split into step sizes for same total move time
  double step_size [servo_quantity];
   for (int j = 0; j < servo_quantity; j++) {
    step_size[j] = (target_angle[b][j]-current_angle[j])/max_diff;
   }
  
  
  //makes stuff move
  
  while(current_angle[servonum_max] < target_angle[b][servonum_max]){
   
   for (int k = 0; k < servo_quantity; k++){
    
    current_angle[k] = current_angle[k] + step_size[k];
    //double pulselen = map (current_angle[k], 0, 180, SERVOMIN, SERVOMAX);
    //pwm.setPWM(k, 0, pulselen);
    pwm.setPWM(k, 0, current_angle[k]);
    delay(speed);
  
    Serial.flush();
   }
  }
  }
}





/*
}



for (double pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen=pulselen+step_size) {
    
    pwm.setPWM(servonum, 0, pulselen);
    delay(speed);
  }


  
  
  
  
  // Drive each servo one at a time
  Serial.println(servonum);
  for (double pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen=pulselen+step_size) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(speed);
  }

  delay(200);
  for (double pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen=pulselen-step_size) {
    pwm.setPWM(servonum, 0, pulselen);
    //delay(speed);
  }

  delay(200);

}


  //servonum ++;
 // if (servonum > 7) servonum = 0;
 */
