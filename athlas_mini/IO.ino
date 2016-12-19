// Controll loop  -------------------------------------------

void controllLoop(){
  //test if all have nearly same force value
  int f1 = frontRight.getForce();
  //int mittelwert = (int) (f1+MINIMUM_LOCK_FORCE)/2;

  if(frontRight.state == LEG_STATE_FORCE_CONTROLL){
    if(frontRight.getForce()>FORCE_THRESHOLD && frontLeft.getForce()>FORCE_THRESHOLD && backRight.getForce()>FORCE_THRESHOLD && backLeft.getForce()>FORCE_THRESHOLD){
      DPRINTLN("Force Threshold reached, legs locked");
      frontRight.state = LEG_STATE_LOCKED;
      return;
    }
    
    frontRight.updateControllLoop();
    frontLeft.updateControllLoop();
    backRight.updateControllLoop();
    backLeft.updateControllLoop();
    
  }else if(frontRight.state == LEG_STATE_LOCKED){
    int mittelwert = (int) (frontRight.getForce()+frontLeft.getForce()+backRight.getForce()+backLeft.getForce())/4;
    if(mittelwert < FORCE_THRESHOLD*2/3){
      frontRight.state = LEG_STATE_FORCE_CONTROLL;
    }
  }
}

// Read PWM input -------------------------------------------
void setupPwm(int pin){
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), measurePwm, CHANGE);
}

void measurePwm(){  
  if(digitalRead(PWM_PIN)){
    pwmTime = micros();
  }else{
    pwmValue = micros()-pwmTime;
    //DPRINTLN(pwmValue);
    if(pwmValue > PWM_THRESHOLD){
      
    }
  }
}

/* calculate servo angle to reach height of leg
 *  Masstab 1:5.5
 *  INPUT:
 *  double height [mm] 
 *    0        => 26.58 mm unter Helikopter (höchste Position)
 *    -93.438  => 120 mm unter Helikopter (unterste Position)
 *    
 *   bool windup  , is set to true if height out of boundries (to prevent windup)
 *  
 *  OUTPUT:
 *  double angle [rad]  (45.98° - 106.192°) 0.8026-1.8534
 */
/*
double height_to_angle(double height,bool *windup){
  //correct height if too big or too small

  if (height > 0){
    height = 0;
    *windup = true;
  }else if(height < -93.438){
    height = -93.438;
    *windup = true;
  }else{
    *windup = false;
  }

  height -= 26.58;            //set Zero to -26.58mm

  //calculate angle in rad 
  return 503.7-2.0448*height*5.5; //Set scale to 5.5
}
*/


/*
void setupIO(){
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}

void setHeight(Servo outServo,double height,bool *windup){
  int pos = (int)height_to_angle(height,windup);
  int pos_micros = map(pos,802,1853,1000,1600);
  outServo.writeMicroseconds(pos_micros);
}
*/
