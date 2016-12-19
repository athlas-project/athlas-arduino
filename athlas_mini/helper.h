#include "controller.h"
#include <Servo.h>

class ExecutionInterval{
  public:
    ExecutionInterval(unsigned int interval);
    bool testInterval();

  private:
    unsigned long lastExecution;
    unsigned int interval;
};


class Leg{
  public:

    //Attaches servo and sensor to corresponding pins
    void setupLeg(unsigned int servoPin, unsigned int forcePin, unsigned int servoDir);

    //moves leg to corresponding height
    //deactivates force controll
    //height [mm]
    void setHeight(double height);

    //Set reference Value for Force controller 
    //force [0-1024]
    void setForce(int force);

    //Activate Force Controll
    //void activateForceControll();

    //Updates Controll-Loop
    void updateControllLoop();

    //Returns position in rad
    int getPosition();

    //Returns force sensor value
    int getForce();

    //Returns height in mm
    double getHeight();

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
    static double heightToAngle(double *height_pointer,bool *windup);

    static int state;

    Controller pid;

    private:
      Servo servo;
      double height;
      int position;
      int forceValueReference;
      int analogPin;
      unsigned int servoDir;
};


