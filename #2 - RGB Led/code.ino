// Define constants for all 3 colors

const int blueInputPin = A0;
const int blueOutputPin = 9;
const int greenInputPin = A1;
const int greenOutputPin = 10;
const int redInputPin = A2;
const int redOutputPin = 11;

void setup() {

  // Configure the pins to behave either as an input or an output. 
pinMode(blueInputPin, INPUT);
pinMode(blueOutputPin, OUTPUT);
pinMode(redInputPin, INPUT);
pinMode(redOutputPin, OUTPUT);
pinMode(greenInputPin, INPUT);
pinMode(greenOutputPin, OUTPUT);

}

// Periodically update analogWrite values.
void loop() {
	// The default analogRead() resolution is 10 bits (source: https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) so up to 1024 values,
  // while analogWrite takes a value modulo 256, so a transformation must be performed.
  // This also allows the LED to run 8 bit color, with 256 values for each RGB channel

analogWrite(blueOutputPin, 255.0*analogRead(blueInputPin)/1023);
analogWrite(redOutputPin, 255.0*analogRead(redInputPin)/1023);
analogWrite(greenOutputPin, 255.0*analogRead(greenInputPin)/1023);
}