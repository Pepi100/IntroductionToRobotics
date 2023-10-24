const int buttonPin = 2;
const int ledPin = 13;
int buttonPushCounter = 0;
byte ledState = LOW;

int buttonState = 0, previousButtonState=0;

void setup() {
pinMode(buttonPin, INPUT_PULLUP);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}
void loop() {
// read the input pin:
buttonState = digitalRead(buttonPin);

if(buttonState == LOW && buttonState!=previousButtonState){
  ledState= !ledState;
}


digitalWrite(ledPin, ledState);

// if (buttonState == LOW) {
// buttonPushCounter++;
// }
// Serial.println(buttonPushCounter);

previousButtonState=buttonState;


}