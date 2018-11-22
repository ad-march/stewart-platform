#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {300,410,225,410,240,415,230};
int SERVOMAX[] = {575,210,520,215,530,210,530};
int SERVOMEAN[] = {445,390,350,390,350,400,360};


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  
//Mean position
  // pwm.setPWM(0, 0, SERVOMEAN[0]);
    //  Serial.flush();


  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMEAN[i+1]);
      Serial.flush();
    }

delay(1000);
/*
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
