#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
#define SERVOMIN  132
#define SERVOMAX  535

int servonum = 0;
int servo_quantity = 2;
int speed = 5;
int step_size = 1;
double current_angle [] = {150,150};
double target_angle [] = {300, 500};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {

int max_diff = 0;
int servonum_max = 0;

  for (int i = 1; i <= servo_quantity; i++) {
    //find maxx difference start to taget
    int diff = abs(target_angle[i]-current angle[i]);
    
    if (diff > max_diff){
      max_diff=diff;
      servonum_max = i;
    }
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
