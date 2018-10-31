#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Servo calibration:
#define SERVOMIN  135
#define SERVOMAX  535

int servonum = 0;
int speed = 1000;
int step_size = 1;
const int numpos = 6;
double pulselen;

double angle[]={0,90,45,120,90,180};

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {

  for (int i=0; i< numpos; i++){
    pulselen = map(angle[i], 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum, 0, pulselen);
    delay(speed);
  }
  delay(200);

}


  //servonum ++;
 // if (servonum > 7) servonum = 0;
