// input constants
#define xDeadZone = 30  //joystick zero and deadzone
#define xZero = 508
#define yDeadZone = 30
#define yZero = 508
#define joyMin = 0
#define joyMax = 1023

// motor limits
#define lRMax = 122 //left motor max reverse
#define lRMin = 179 //left motor min reverse
#define lFMin = 197 //left forward min
#define lFMax = 254 //left forward max

#define rRMax = 122 //right motor max reverse
#define rRMin = 179 //right motor min reverse
#define rFMin = 197 //right forward min
#define rFMax = 254 //right forward max

// motor locations
#define lMotor 3
#define rMotor 5


void setup() {
  Serial.begin(9600);
  pinMode(lMotor, OUTPUT);
  pinMode(rMotor, OUTPUT);


}

void loop() {

  int lMax = 0;  //max scale
  int rMax = 0;
  int rOut = 0;  //motor output in percent
  int lOut = 0;
  int lSpeed = 0; //motor speed in pwm
  int rSpeed = 0;

  // get joystick values
  int yCont = analogRead(A1);
  int xCont = analogRead(A0);

  // if xCont is in the positive direction
  if (xCont > xZero + xDeadZone) {  //turn right
    // change the xCont value from a scale of the end of the joystick "deadzone" to joyMax
    // to a scale of 0 to 100 (a power percent value)
    // and set the max right motor speed to the new value
    rMax = map(xCont, xZero + xDeadZone, joyMax, 100, 0);
    lMax = 100;
  }
  // if xCont is in the negative direction
  if (xCont <= xZero - xDeadZone ) {  //turn left
    // change the xCont value from a scale of joyMin to the start of the joystick "deadzone"
    // to a scale of 0 to 100 (a power percent value)
    // and set the max left motor speed to the new value
    lMax = map(xCont, xZero - xDeadZone, joyMin, 100, 0);
    rMax = 100;
  }

  // if yCont is in the positive direction
  if (yCont > yZero + yDeadZone) {   // positive direction
    // change the yCont value from a scale of the end of the "deadzone" to joyMax
    // to a scale of 0 to the max value each size can have
    // and set the power output percent to the new value
    lOut = map(yCont, yZero + yDeadZone, joyMax, 0, lMax); //Map speed in percent
    rOut = map(yCont, yZero + yDeadZone, joyMax, 0, rMax);

    lSpeed = map(lOut, 0, 100, lFMin, lFMax);  //percent to analog movement
    rSpeed = map(rOut, 0, 100, rFMin, rFMax);
  }

  // if yCont is in the negative direction
  if (yCont < yZero - yDeadZone) {  //negative direction
    // change the yCont value from a scale of [yMin, beginning of "deadzone"]
    // to a scale of 0 to the max value each size can have
    // and set the power output percent to the new value
    lOut = map(yCont, joyMin, yZero - yDeadZone, lMax, 0) * -1; //Map speed in percent
    rOut = map(yCont, joyMin, yZero - yDeadZone, rMax, 0) * -1;

    lSpeed = map(lOut, 0, 100, lRMin, lRMax);  //percent to analog movement
    rSpeed = map(rOut, 0, 100, rRMin, rRMax);



  }
  analogWrite(lMotor, lSpeed); //Write speed to motor
  analogWrite(rMotor, rSpeed);

  Serial.print("input x:");
  Serial.print(xCont);
  Serial.print(" y: ");
  Serial.print(yCont);
  Serial.print(" output lSpeed: ");
  Serial.print(lOut);
  Serial.print(" rSpeed: ");
  Serial.print(rOut);
  Serial.println("");
  //delay(00);
}
