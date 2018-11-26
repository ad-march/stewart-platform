#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {440,210,530,215,530,210,530};
int SERVOMEAN[] = {585,390,350,370,350,370,360};


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  
//Mean position
   pwm.setPWM(0, 0, SERVOMAX[0]);
      Serial.flush();


  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMAX[i+1]);
      Serial.flush();
    }
/*
delay(1000);

//Max position
  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMAX[i]);
      Serial.flush();
    }

delay(1000);

//Min position
  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMIN[i]);
      Serial.flush();

    }
 */ 
delay(1000);
}
