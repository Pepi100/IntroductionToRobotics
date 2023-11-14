#define DEBOUNCE_TIME 30
#define LAP_NUMBER 4

// Define connections to the shift register
const int latchPin = 11; // Connects to STCP (latch pin) on the shift register
const int clockPin = 10; // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12; // Connects to DS (data pin) on the shift register

// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

// Store the digits in an array for easy access
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; // Number of digits in the display

// Define the number of unique encodings (0-9, A-F for hexadecimal)
const int encodingsNumber = 16;
// Define byte encodings for the hexadecimal characters 0-F
byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};
// Variables for controlling the display update timing
unsigned long lastIncrement = 0;
unsigned long delayCount = 100; // Delay between updates (milliseconds)
unsigned long currentTime = 0; // The number being displayed

const int startButtonPin = 3;
const int resetButtonPin = 2;
const int saveButtonPin = 8;

bool startButtonPressed = 0;
bool resetButtonPressed = 0;
bool saveButtonPressed = 0;

// debounce variables
int startReading;
int resetReading;
int saveReading;

int startButtonState;
int resetButtonState;
int saveButtonState;

int startLastState;
int resetLastState;
int saveLastState;

unsigned long startLastTime;
unsigned long resetLastTime;
unsigned long saveLastTime;


byte debounceIndex = 0;

bool isPaused = 1;
bool isViewing = 0;

int laps[LAP_NUMBER];
byte savedLaps;
byte savedLapsIndex;
byte viewIndex;
void setup() {
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(saveButtonPin, INPUT_PULLUP);
  // Initialize digit control pins and set them to LOW (off)
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }  
  // Begin serial communication for debugging purposes
  Serial.begin(9600);

  isPaused = 1;
  isViewing = 0;

  for(int i = 0; i < LAP_NUMBER; i++){
    laps[i] = 0;
  }
  currentTime = 0;
  savedLaps = 0;
  savedLapsIndex = 0;
  viewIndex = 0;
}


void  startButtonDebounce(){


  startReading = digitalRead(startButtonPin);
    if (startReading != startLastState) {
      // reset the debouncing timer
      startLastTime = millis();
    }

    if ((millis() - startLastTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (startReading != startButtonState) {
      startButtonState = startReading;
      // only toggle the LED if the new button state is HIGH
      if (startButtonState == LOW) {
        //set state
        startButtonPressed = 1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  startLastState = startReading;
  
}



void  resetButtonDebounce(){


  resetReading = digitalRead(resetButtonPin);
    if (resetReading != resetLastState) {
      // reset the debouncing timer
      resetLastTime = millis();
    }

    if ((millis() - resetLastTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (resetReading != resetButtonState) {
      resetButtonState = resetReading;
      // only toggle the LED if the new button state is HIGH
      if (resetButtonState == LOW) {
        //set state
        resetButtonPressed = 1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  resetLastState = resetReading;
  
}

unsigned long holdTime = 700;
unsigned long startHold;
bool isHolding = 0;

void  saveButtonDebounce(){


  saveReading = digitalRead(saveButtonPin);
    if (saveReading != saveLastState) {
      // reset the debouncing timer
      saveLastTime = millis();
    }

    if ((millis() - saveLastTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (saveReading != saveButtonState) {
      saveButtonState = saveReading;
      // only toggle the LED if the new button state is HIGH
      if (saveButtonState == LOW) {
        //set state
        saveButtonPressed = 1;
        startHold = millis();
        isHolding = 1;
      }else{
        isHolding = 0;
      }

      
    }
    if(isHolding && startHold + holdTime < millis()){
        saveButtonPressed = 1;
        startHold = millis();

    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  saveLastState = saveReading;
  Serial.println(isHolding);
}

void display(){
  if (isPaused){
    if(isViewing){
      writeNumber(laps[viewIndex]);
    }else{
      writeNumber(currentTime);
    }
  }else{
    writeNumber(currentTime);
  }
}


void loop() {

  startButtonDebounce();
  resetButtonDebounce();
  saveButtonDebounce();

  if (isPaused == 0)
    if (millis() - lastIncrement > delayCount) {
      currentTime++;
      currentTime %= 10000;
      lastIncrement = millis();
    }
  
  if (startButtonPressed == 1){
    isPaused = !isPaused;
    startButtonPressed = 0;

    if( !isPaused ){
      isViewing = 0;
    }

  }

  if (resetButtonPressed == 1){
    
    resetButtonPressed = 0;
    if(isPaused == 1){
      setup();
    }

  }

  if(saveButtonPressed){

    if(isPaused){
      if(isViewing){
        //advance viewing
        viewIndex ++;
        viewIndex %= savedLaps;
      }else{
        //enter viewing
        isViewing = 1;
      }

    }else{
      //save current time in lap
      laps[savedLapsIndex] = currentTime;
      savedLaps = min(savedLaps + 1, LAP_NUMBER);
      savedLapsIndex++;
      savedLapsIndex %= LAP_NUMBER;
      

    }

    saveButtonPressed = 0;
  }




  display();
} 

void writeReg(int digit) {
    // Prepare to shift data by setting the latch pin low
    digitalWrite(latchPin, LOW);
    // Shift out the byte representing the current digit to the shift register
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // Latch the data onto the output pins by setting the latch pin high
    digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {

  int currentNumber = number;
  int displayDigit = displayCount - 1;
  
  while (displayDigit >= 0) {
  	activateDisplay(displayDigit);
    if (displayDigit == 2){
      writeReg(byteEncodings[currentNumber % 10] + 1);
    }else{
      writeReg(byteEncodings[currentNumber % 10]);
    }
    
    displayDigit--;
    currentNumber = currentNumber/10;
    writeReg(B00000000); //used to reduce ghosting
    // delay(1000);
  }
}