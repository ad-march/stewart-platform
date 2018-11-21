#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {410,225,410,240,415,230};
int SERVOMAX[] = {190,460,185,465,190,460};
int SERVOMEAN[] = {330,305,330,315,340,315};

int servonum = 0;
const int servo_quantity = 6;
const int steps_quantity = 6;
double speed = 1;    //speed factor = number of degrees per step
double current_angle [] = {0,0,0,0,0,0};
double target_angle [][servo_quantity] = {{-3.453072574,-5.502042113,-5.502042113,-3.453072574,8.623984679,8.623984679},
                                          {-7.065621827,-11.06994714,-11.06994714,-7.065621827,16.9359821,16.9359821},
                                          {-10.82936654,-16.72205945,-16.72205945,-10.82936654,25.12353262,25.12353262},
                                          {-10.82936654,-16.72205945,-16.72205945,-10.82936654,25.12353262,25.12353262},
                                          {-18.75419332,-28.3878174,-28.3878174,-18.75419332,42.01272326,42.01272326},
                                          {-22.87108763,-34.4917331,-34.4917331,-22.87108763,51.45749229,51.45749229}};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  for (int a = 0; a < servo_quantity; a++){
    double pulselen = map (current_angle[a], 0, 80, SERVOMEAN[a], SERVOMAX[a]);
    pwm.setPWM(a+1, 0, pulselen);
    Serial.flush();
  
  pwm.setPWM(0, 0, 550);
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

}
for (int c = 550; c > 200; c--){
    pwm.setPWM(0, 0, c);
    Serial.flush();
    delay(20);
  
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
