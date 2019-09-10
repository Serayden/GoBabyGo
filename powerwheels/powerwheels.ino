int xDeadZone = 30;  //joystick zero and deadzone
int xZero = 508;
int yDeadZone = 30;
int yZero = 508;
int joyMin = 0;
int joyMax = 1023;

int lRMax = 122; //left motor max reverse
int lRMin = 179; //left motor min reverse
int lFMin = 197; //left forward min
int lFMax = 254; //left forward max

int rRMax = 122; //right motor max reverse
int rRMin = 179; //right motor min reverse
int rFMin = 197; //right forward min
int rFMax = 254; //right forward max

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

  int yCont = analogRead(A1);
  int xCont = analogRead(A0);

  if (xCont > xZero) {  //turn right
    rMax = map(xCont, xZero + xDeadZone, joyMax, 100, 0);
    lMax = 100;
  }

  if (xCont <= xZero) {  //turn left
    lMax = map(xCont, xZero - xDeadZone, joyMin, 100, 0);
    rMax = 100;
  }


  if (yCont > yZero + yDeadZone) {   //posative direction
    lOut = map(yCont, yZero + yDeadZone, joyMax, 0, lMax); //Map speed in percent
    rOut = map(yCont, yZero + yDeadZone, joyMax, 0, rMax);

    lSpeed = map(lOut, 0, 100, lFMin, lFMax);  //percent to analog movement
    rSpeed = map(rOut, 0, 100, rFMin, rFMax);
  }

  if (yCont < yZero - yDeadZone) {  //negative direction
    lOut = map(yCont, yZero - yDeadZone, joyMin, 0, lMax); //Map speed in percent
    rOut = map(yCont, yZero - yDeadZone, joyMin, 0, rMax);

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
