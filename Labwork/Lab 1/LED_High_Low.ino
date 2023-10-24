const int potPin = A0;
const int ledPin = 9;
int potValue = 0;
void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
// read the input on analog pin 0:
potValue = analogRead(potPin); // not the best practice
// print out the value you read:
 Serial.println(255.0*potValue/1023);
analogWrite(ledPin, 255.0*potValue/1023);

delay(10); // delay in between reads for stability
}