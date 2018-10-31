#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
#define SERVOMIN  132
#define SERVOMAX  535

int servonum = 0;
int servo_quantity = 2;
int speed = 5;
double current_angle [servo_quantity] = {150,150};
double target_angle [servo_quantity] = {300, 500};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {

//Finds servo having to move the most
int max_diff = 0;
int servonum_max = 0;
  
  for (int i = 0; i < servo_quantity; i++) {
    int diff = abs(target_angle[i]-current angle[i]);
    
    if (diff > max_diff){
      max_diff=diff;
      servonum_max = i;
    }
  }

// Split into step sizes for same total move time
double step_size [servo_quantity];
 for (int j = 0; j < servo_quantity; i++) {
  step_size[j] = (abs(target_angle[j]-current_angle[j]))/max_diff;
 }


//makes stuff move

for (int k = 0, k < servo quantity, k++){

  double pulselen = current_angle[k] + step_size[k];
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
