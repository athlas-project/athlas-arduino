/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */

String inputString = "";

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      inputString.remove(inputString.length() - 1); // remove '\n'
      DPRINT("Command recived: ");
      DPRINTLN(inputString);
      
      //Switch trough the different commands
      switch (inputString[0]){
        case 'r':
          inputString.remove(0, 2);
          DPRINT("updated reference value to: ");
          DPRINTLN(inputString.toInt());
          frontRight.setForce(inputString.toInt());
          backRight.setForce(inputString.toInt());
          
          break;
        case 'p':
          inputString.remove(0, 2);
          //pid_ctrl.set_Kp(inputString.toFloat());
          DPRINT ("updated Kp to: ");
          DPRINTLN(inputString.toFloat());
          
          frontRight.pid.setKp(inputString.toFloat());
          backRight.pid.setKp(inputString.toFloat());
          
          break;
        case 'i':
          inputString.remove(0, 2);
          DPRINT ("updated Ki to: ");
          DPRINTLN(inputString.toFloat());

          frontRight.pid.setKi(inputString.toFloat());
          break;
        case 'd':
          inputString.remove(0, 2);
          DPRINT ("updated Kd to: ");
          DPRINTLN(inputString.toFloat());

          frontRight.pid.setKd(inputString.toFloat());
          backRight.pid.setKd(inputString.toFloat());
          break;
        case 'h':
          inputString.remove(0, 2);
          DPRINT ("moved servos to: ");
          DPRINTLN(inputString.toInt());
          
          frontRight.setHeight(inputString.toInt());
          frontLeft.setHeight(inputString.toInt());
          backRight.setHeight(inputString.toInt());
          backLeft.setHeight(inputString.toInt());
          
          break;
        case 'f':
          DPRINT("front right: ");
          DPRINTLN(frontRight.getForce());
          DPRINT("back right: ");
          DPRINTLN(backRight.getForce());
          DPRINT("front left: ");
          DPRINTLN(frontRight.getForce());
          DPRINT("back right: ");
          DPRINTLN(backRight.getForce());
          
          break;
        case 's':
          inputString.remove(0, 2);
          if(inputString.indexOf("up") != -1){
            frontRight.state = LEG_STATE_UP;
          }else if(inputString.indexOf("force") != -1){
            frontRight.state = LEG_STATE_FORCE_CONTROLL;
          }else if(inputString.indexOf("lock") != -1){
            frontRight.state = LEG_STATE_LOCKED;
          }else{
            DPRINTLN("unknown command");
          }
      }
      inputString = "";
    }
  }
}




