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

   delay(2000);
   pwm.setPWM(0, 0, SERVOMAX);
   Serial.flush();

  delay(2000);
    
    
for (int c = 550; c > 200; c--){
    pwm.setPWM(0, 0, c);
    Serial.flush();
    delay(20);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:



  
  

}
