const int buttonPin = 2;
const int ledPin = 13;
byte buttonState = 0;
byte ledState = 0;
void setup() {
pinMode(buttonPin, INPUT_PULLUP);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}
void loop() {
buttonState = digitalRead(buttonPin);
ledState = !buttonState;
digitalWrite(ledPin, ledState);
Serial.println(buttonState);
}