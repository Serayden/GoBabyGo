// input constants
#define xDeadZone = 30  //joystick zero and deadzone
#define xZero = 508
#define yDeadZone = 30
#define yZero = 508
#define joyMin = 0
#define joyMax = 1023

// motor limits
#define LEFT_REVERSE_MAX = 122 //left motor max reverse
#define LEFT_REVERSE_MIN = 179 //left motor min reverse
#define LEFT_FORWARD_MIN = 197 //left forward min
#define LEFT_FORWARD_MAX = 254 //left forward max

#define RIGHT_REVERSE_MAX = 122 //right motor max reverse
#define RIGHT_REVERSE_MIN = 179 //right motor min reverse
#define RIGHT_FORWARD_MIN = 197 //right forward min
#define RIGHT_FORWARD_MAX = 254 //right forward max

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

    // map left out from a scale of [0, 100] to a scale of [left forward min, left forward max] (power output)
    // map right out from a scale of [0, 100] to a scale of [right forward min, right forward max] (power output)
    lSpeed = map(lOut, 0, 100, LEFT_FORWARD_MIN, LEFT_FORWARD_MAX);  //percent to analog movement
    rSpeed = map(rOut, 0, 100, RIGHT_FORWARD_MIN, RIGHT_FORWARD_MAX);
  }

  // if yCont is in the negative direction
  if (yCont < yZero - yDeadZone) {  //negative direction
    // change the yCont value from a scale of [yMin, beginning of "deadzone"]
    // to a scale of 0 to the max value each size can have
    // and set the power output percent to the new value
    lOut = map(yCont, joyMin, yZero - yDeadZone, lMax, 0) * -1; //Map speed in percent
    rOut = map(yCont, joyMin, yZero - yDeadZone, rMax, 0) * -1;

    // map left out from a scale of [0, 100] to a scale of [left reverse min, left reverse max] (power output)
    // map right out from a scale of [0, 100] to a scale of [right reverse min, right reverse max] (power output)
    lSpeed = map(lOut, 0, 100, LEFT_REVERSE_MIN, LEFT_REVERSE_MAX);  //percent to analog movement
    rSpeed = map(rOut, 0, 100, RIGHT_REVERSE_MIN, RIGHT_REVERSE_MAX);
  }

  // write power outputs to the motors
  analogWrite(lMotor, lSpeed); 
  analogWrite(rMotor, rSpeed);

  // lSpeed should be on the range [122, 254]
  // rSpeed should be on the range [122, 254]

  // debug stuff
  Serial.print("Input x: ");
  Serial.print(xCont);
  Serial.print(" y: ");
  Serial.print(yCont);
  Serial.print(", Output Power Percent: Left: ");
  Serial.print(lOut);
  Serial.print(" Right: ");
  Serial.print(rOut);
  Serial.print(", Output Left Power: ");
  Serial.print(lSpeed);
  Serial.print(" Right Power: ");
  Serial.println(rSpeed);
  //delay(00);
}
