// Define constants for all 3 colors

#define BLUE_INPUT_PIN A0
#define BLUE_OUTPUT_PIN  9
#define GREEN_INPUT_PIN  A1
#define GREEN_OUTPUT_PIN  10
#define RED_INPUT_PIN  A2
#define RED_OUTPUT_PIN  11

const int maxOutput=255;
const int minOutput=0;
const int maxInput=1023;
const int minInput=0;

const bool noiseFiltering = true;
const int readingNr = 10;

void setup() {

  // Configure the pins to behave either as an input or an output. 
pinMode(BLUE_INPUT_PIN, INPUT);
pinMode(BLUE_OUTPUT_PIN, OUTPUT);
pinMode(RED_INPUT_PIN, INPUT);
pinMode(RED_OUTPUT_PIN, OUTPUT);
pinMode(GREEN_INPUT_PIN, INPUT);
pinMode(GREEN_OUTPUT_PIN, OUTPUT);

Serial.begin(9600);

}

// Periodically update analogWrite values.
void loop() {
	// The default analogRead() resolution is 10 bits (source: https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) so up to 1024 values,
  // while analogWrite takes a value modulo 256, so a transformation must be performed.
  // This also allows the LED to run 8 bit color, with 256 values for each RGB channel
  Serial.println(analogRead(GREEN_INPUT_PIN)); //debug
  int greenOutput, redOutput, blueOutput;

  if(noiseFiltering ==  true){
    int greenAvg = 0, redAvg = 0, blueAvg = 0;
    for (int i = 0; i < readingNr; i++) {
      greenAvg+=analogRead(GREEN_INPUT_PIN);
      redAvg+=analogRead(RED_INPUT_PIN);
      blueAvg+=analogRead(BLUE_INPUT_PIN);
      delay(1);
    }
    greenOutput=1.0*greenAvg/readingNr;
    redOutput=1.0*redAvg/readingNr;
    blueOutput=1.0*blueAvg/readingNr;
  }else{
    greenOutput=analogRead(GREEN_INPUT_PIN);
    redOutput=analogRead(RED_INPUT_PIN);
    blueOutput=analogRead(BLUE_INPUT_PIN);
  }



analogWrite(BLUE_OUTPUT_PIN,map (blueOutput, minInput, maxInput, minOutput, maxOutput) );
analogWrite(RED_OUTPUT_PIN,map (redOutput, minInput, maxInput, minOutput, maxOutput) );
analogWrite(GREEN_OUTPUT_PIN,map (greenOutput, minInput, maxInput, minOutput, maxOutput) );
// delay(10);
}