#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
#define SERVOMIN  200
#define SERVOMAX  550



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  // put your main code here, to run repeatedly:

   delay(2000);
   pwm.setPWM(6, 0, SERVOMAX);
   Serial.flush();

  delay(2000);
     
  for (int j = SERVOMAX; j > SERVOMIN; j--){
      pwm.setPWM(6, 0, j);
      Serial.flush();
      delay(10);
    }
    
  for (int i = SERVOMIN; i < SERVOMAX; i++){
    pwm.setPWM(6, 0, i);
    Serial.flush();
  }

  
  

}
