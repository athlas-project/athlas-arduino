

#include "helper.h"


#define DPRINT(...)    Serial.print(__VA_ARGS__)     
#define DPRINTLN(...)  Serial.println(__VA_ARGS__) 

#define PWM_PIN 2 //interrupt only on pin 1 and 2
#define SERVO_PIN 9
#define PWM_THRESHOLD 1400
#define FORCE_THRESHOLD 200

#define LEG_STATE_UP 0
#define LEG_STATE_FORCE_CONTROLL 1
#define LEG_STATE_LOCKED 2

#define SERVO_RIGHT 1
#define SERVO_LEFT  0

ExecutionInterval ctrl_interval(10);

Leg frontRight;
Leg frontLeft;
Leg backRight;
Leg backLeft;


// Read PWM input -------------------------------------------
volatile unsigned long pwmTime = 0;
volatile unsigned long pwmValue = 0;



void setup() {
  Serial.begin(250000);
  
  frontRight.setupLeg(4,A3,SERVO_LEFT);
  frontLeft.setupLeg(A5,A2,SERVO_RIGHT);
  backRight.setupLeg(5,A0,SERVO_RIGHT);
  backLeft.setupLeg(A4,A1,SERVO_LEFT);

  setupPwm(PWM_PIN);
}

void loop() {  
  if(ctrl_interval.testInterval()){
    controllLoop();
  }
}
