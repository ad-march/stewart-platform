#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {410,225,410,240,415,230};
int SERVOMAX[] = {190,460,185,465,190,460};
int SERVOMEAN[] = {330,305,330,315,340,315};


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  
//Mean position

  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMEAN[i]);
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
