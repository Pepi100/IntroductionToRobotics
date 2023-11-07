#define DIRECTIONS 4
#define SEGMENTS 8 
#define DEBOUNCE_DELAY 25
#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023
#define BLINK_TIME 250
#define MOVE_TIME 700
#define PIN_DELTA 3 //delta between segment number and it's corresponding digital pin

const int movementMatrix[SEGMENTS][DIRECTIONS] =
{
  {-1, 6, 5, 1}, // a
  {0, 6, 5, -1}, // b
  {6, 3, 4, 7},  // c
  {6, -1, 4, 2}, // d
  {6, 3, -1, 2}, // e
  {0, 6, -1, 1}, // f
  {0, 3, -1, -1}, // g
  {-1, -1, 2, -1} // dp
};

const int clickPin = 2;
const int xPin = A0; 
const int yPin = A1;
int xValue, yValue;

//button debounce variables
int buttonReading;
int lastButtonState;
unsigned long lastDebounceTime;
int buttonState;
volatile int buttonPressed; // this will store the result of the debounce process


unsigned long lastInterruptTime = 0;

//variables for joystick reading
int lastValueX = 0, lastValueY=0;
int joystickMoved = 0;

int position=7;//current position
unsigned long lastMove = 0;

bool segmentValue[SEGMENTS] = {0,0,0,0,0,0,0,0};
unsigned long lastBlink = 0;
bool blinkState=0;

int index=0;

void setup() {
  pinMode(clickPin, INPUT_PULLUP);
  

  for(int i=0; i<SEGMENTS;i++)
  {
    pinMode(i+PIN_DELTA, OUTPUT);
  }


  attachInterrupt(digitalPinToInterrupt(clickPin), buttonISR, RISING); 


  Serial.begin(9600);


  // for(int i=0; i<=1023;i++){
  //   Serial.print(i);
  //   Serial.print(" = ");
  //   Serial.println(map(i, JOYSTICK_MIN, JOYSTICK_MAX+1, 1, -2));
  // }
}

void buttonDebounce(){
  buttonReading = digitalRead(clickPin);
    if (buttonReading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (buttonReading != buttonState) {
      buttonState = buttonReading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        //set state
        buttonPressed=1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = buttonReading;
}

int translateMovement(int x, int y){
  if(x == 1)
    return 3;
  if(x == -1)
    return 2;
  if(y == 1)
    return 1;
  if(y == -1)
    return 0;

  
  return -1;
}

//deprecated
void showSegmentsBasic(){
  for(int i=0; i<SEGMENTS;i++)
    if(i!= position)
    digitalWrite(i+PIN_DELTA, segmentValue[i]);

}

void showSegments(){

  if(index!= position)
    digitalWrite(index+PIN_DELTA, segmentValue[index]);
  index= (index+1)%SEGMENTS;
}


void blinkCurrent(){
  if(millis() > lastBlink + BLINK_TIME){
      blinkState= !blinkState;
      digitalWrite(position+PIN_DELTA, blinkState);
      lastBlink = millis();

    }
}


void buttonISR()
{
  
  buttonReading = digitalRead(clickPin);
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime >= DEBOUNCE_DELAY && buttonReading) 
  {
    Serial.println(1);
    buttonPressed = 1;
  }
  lastInterruptTime = interruptTime;
}


void loop() {
  showSegments();
  blinkCurrent();

  //reading inputs
  // buttonDebounce(); //sets value for buttonPressed
  xValue = map(analogRead(xPin), JOYSTICK_MIN, JOYSTICK_MAX+1, 1, -2);
  yValue = map(analogRead(yPin), JOYSTICK_MIN, JOYSTICK_MAX+1, 1, -2);

  if(xValue != lastValueX && xValue != 0){
    joystickMoved = 1;
  }
  if(yValue != lastValueY && yValue != 0){
    joystickMoved = 1;
  }

  lastValueX = xValue;
  lastValueY = yValue;
  //update position

  if( (xValue || yValue )  && millis() >= lastMove + MOVE_TIME )
  {
    position = (movementMatrix[position][translateMovement(xValue,yValue)] != -1 )?movementMatrix[position][translateMovement(xValue,yValue)]:position;
    joystickMoved = 0;
    lastMove = millis();

  }
    
  if(buttonPressed){
    segmentValue[position] = (segmentValue[position]+1)%2;
    buttonPressed = 0; 
  }


// debug 
//  char x='a' + position;
//  Serial.print(x);
//  Serial.print(" ");
//  Serial.print(xValue);
//  Serial.print(" ");
//  Serial.println(yValue);
//  delay(500);

}
