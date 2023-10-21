// define constants for all 3 colors

const int blueInputPin = A0;
const int blueOutputPin = 9;
const int greenInputPin = A1;
const int greenOutputPin = 10;
const int redInputPin = A2;
const int redOutputPin = 11;

void setup() {
pinMode(blueInputPin, INPUT);
pinMode(blueOutputPin, OUTPUT);
pinMode(redInputPin, INPUT);
pinMode(redOutputPin, OUTPUT);
pinMode(greenInputPin, INPUT);
pinMode(greenOutputPin, OUTPUT);
}

//periodically update analogWrite values.
void loop() {
	// analog input is read on a scale from 0 to 1023, while analogWrite takes a value modulo 256, so a transformation must be performed.
analogWrite(blueOutputPin, 255.0*analogRead(blueInputPin)/1023);
analogWrite(redOutputPin, 255.0*analogRead(redInputPin)/1023);
analogWrite(greenOutputPin, 255.0*analogRead(greenInputPin)/1023);
}