#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {400,230,400,230,400,230};
int SERVOMAX[] = {170,470,170,475,175,470};
int SERVOMEAN[] = {330,300,335,300,340,305};

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 7;
double speed = 0.5;    //speed factor = number of degrees per step
double current_angle [] = {0,0,0,0,0,0};
double target_angle [][servo_quantity] = {{10, 20, 30, 40, -50, 60},
                                          {40, 20, 20, 40, 50, 45},
                                          {20, 30, 50, 50, -50, 35},
                                          {-30, 60, 85, 20, 30, 25},
                                          {-50, 0, 0, 15, 32, 45},
                                          {-20, -10, 20, 50, -30, 35},
                                          {0, -30, -50, 35, -34, 15}};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], -57, 90, SERVOMIN[a], SERVOMAX[a]);
    pwm.setPWM(a+1, 0, pulselen);
    Serial.flush();
  }

  delay(2000);

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
    step_size[j] = speed*(target_angle[b][j]-current_angle[j])/(max_diff+0.001); //+0.001 prevents divide by zero error
   }
  
  
  //makes stuff move

  if(current_angle[servonum_max]<target_angle[b][servonum_max]){
    
    while(current_angle[servonum_max] < target_angle[b][servonum_max]){
     
     for (int k = 0; k < servo_quantity; k++){
      
      current_angle[k] = current_angle[k] + step_size[k];
      double pulselen = map (current_angle[k], -57, 90, SERVOMIN[k], SERVOMAX[k]);
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
      double pulselen = map (current_angle[k], -57, 90, SERVOMIN[k], SERVOMAX[k]);
      pwm.setPWM(k+1, 0, pulselen);
     // pwm.setPWM(k+1, 0, current_angle[k]);
    
      Serial.flush();
     }
    }  
  }

}
  
}

void loop() {}

/*for (int b = 0; b < steps_quantity; b++){  

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
    step_size[j] = speed*(target_angle[b][j]-current_angle[j])/max_diff;
   }
  
  
  //makes stuff move
  
  while(current_angle[servonum_max] < target_angle[b][servonum_max]){
   
   for (int k = 0; k < servo_quantity; k++){
    
    current_angle[k] = current_angle[k] + step_size[k];
    double pulselen = map (current_angle[k], -70, 90, SERVOMIN[k], SERVOMAX[k]);
    pwm.setPWM(k+1, 0, pulselen);
   // pwm.setPWM(k+1, 0, current_angle[k]);
  
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
