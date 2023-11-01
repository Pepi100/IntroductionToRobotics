// Declare all the joystick pins
const int pinSW = 2; // Digital pin connected to switch output
const int pinX = A0; // A0 - Analog pin connected to X output
const int pinY = A1; // A1 - Analog pin connected to Y output

// Declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;
int index = 0;

bool commonAnode = false; // Modify if you have common anode
const int noOfDigits = 10;

byte dpState = LOW;
byte swState = LOW;
byte lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;

int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // TODO: Initialize joystick pins and commonAnode
  Serial.begin(9600);
  // Initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }

  

  // TODO: Check if commonAnode should be modified here
}

int state =0;
void loop() {

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("  |  ");
  Serial.print("Y-axis: ");
  Serial.print(yValue);
  Serial.println("  |  ");

  // TODO: Implement the logic for joystick input and number display

  displayNumber(digit, HIGH);
  
  if(yValue > 700 && state ==0){
    state = 1;
    digit+=state;
  }
  if(yValue<=700 && yValue>=400)
    state = 0;
  if(yValue < 400 && state ==0){
    state = -1;
    digit +=state;
  }


  if(digit == -1)
  digit =9;
  digit= digit %10;

  // TODO: Control the timing for switching between numbers
}

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; ++i) {
  	digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}