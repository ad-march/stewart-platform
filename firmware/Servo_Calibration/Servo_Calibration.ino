#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
int SERVOMIN[] = {400,230,400,230,400,230};
int SERVOMAX[] = {170,470,170,475,175,470};
int SERVOMEAN[] = {330,300,335,300,340,305};


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  
//Mean position
/*
  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMEAN[i]);
      Serial.flush();
    }


//Max position
  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMAX[i]);
      Serial.flush();
    }
*/

//Min position
  for (int i = 0; i < 6; i++){
      pwm.setPWM(i+1, 0, SERVOMIN[i]);
      Serial.flush();
    }

}
