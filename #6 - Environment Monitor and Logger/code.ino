#include <EEPROM.h> 
#define RESET 0
#define BAUD_RATE 9600
#define MENUS 5
#define MAX_MENU_OPTIONS 5

#define BLUE_PIN 9
#define GREEN_PIN 10
#define RED_PIN 11

#define ECHO_PIN 6
#define TRIG_PIN 5

#define PHOTOCELL_PIN A0

int distance;
int lightLevel;

bool wrongOption = false;
short currentMenu;
short samplingInterval; //between 0 and 10000
short ultrasonicAlert; //between 2 and
short LDRAlert; //between 0 and 1023
short LEDColor[3];
bool autoLED;
bool autosave;

unsigned long lastSample = 0;
unsigned long lastPrint = 0;

//this matrix is used to traverse the multiple menu options
short movementMatrix[MENUS][MAX_MENU_OPTIONS]={
  {-1,1,2,3,4},
  {-1,11,12,13,0},
  {-1,21,22,23,0},
  {-1,31,32,33,0},
  {-1,41,42,0,-1},
};

void updateEEPROM(){
  EEPROM.put(0, samplingInterval); //takes up 2 bytes
  EEPROM.put(2, ultrasonicAlert); //takes up 2 bytes
  EEPROM.put(4, LDRAlert); //takes up 2 bytes
  EEPROM.put(6, LEDColor[0]); //takes up 2 bytes
  EEPROM.put(8, LEDColor[1]); //takes up 2 bytes
  EEPROM.put(10, LEDColor[2]); //takes up 2 bytes
  EEPROM.put(11, autoLED); //needs 1 bit, we are allowing 1 byte because it`s the night before deadline :P
  EEPROM.put(12, autosave); //same
}

void readEEPROM(){
  EEPROM.get(0, samplingInterval); //takes up 2 bytes
  EEPROM.get(2, ultrasonicAlert); //takes up 2 bytes
  EEPROM.get(4, LDRAlert); //takes up 2 bytes
  EEPROM.get(6, LEDColor[0]); //takes up 2 bytes
  EEPROM.get(8, LEDColor[1]); //takes up 2 bytes
  EEPROM.get(10, LEDColor[2]); //takes up 2 bytes
  EEPROM.get(11, autoLED); //needs 1 bit, we are allowing 1 byte because it`s the night before deadline :P
  EEPROM.get(12, autosave); //same
}

void setup() {

  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 

  Serial.begin(BAUD_RATE);
  if(RESET){
    currentMenu = 0;
    samplingInterval = 2000;
    ultrasonicAlert =  50 * 2 / 0.034;
    LDRAlert = 300;
    LEDColor[0] = 255;
    LEDColor[1] = 255;
    LEDColor[2] = 255;
    autoLED = 1;
    autosave = 0;
    updateEEPROM();
  }else{
    readEEPROM();
  }
  

  // Display the initial menu interface to the Serial Monitor upon startup
  screenFlush();
  printMenu();
}



void loop() {
  
  currentMenuAction();
  readSensors();
  // triggerAlerts();
  

  // Continuously checks for incoming serial data
  if (Serial.available()) {
    screenFlush();
    // Reads an integer value from the serial buffer (user's menu choice)
    int choice = Serial.parseInt(SKIP_WHITESPACE, '\n');


    advanceMenu(choice);
    // Re-displays the menu after executing the chosen action

    notAnOption();
    printMenu();
  }

}
// Function to display a menu of options to the user
void printMenu() {
  switch (currentMenu) {
    case 0:
        Serial.print("Select an option:\n");
        Serial.print("1. Sensor Settings\n");
        Serial.print("2. Logging Settings\n");
        Serial.print("3. System Status\n");
        Serial.print("4. RGB LED Control\n");
        break;
    case 1:
        Serial.print("Select an option:\n");
        Serial.print("1.1 Sensors Sampling Interval\n");
        Serial.print("1.2 Ultrasonic Alert Threshold\n");
        Serial.print("1.3 LDR Alert Threshold\n");
        Serial.print("1.4 Back\n");
        break;
    case 2:
        Serial.print("Select an option:\n");
        Serial.print("2.1 Currently Saved Settings\n");
        Serial.print("2.2 Autosave Settings\n");
        Serial.print("2.3 Save current settings\n");
        Serial.print("2.4 Back\n");
        break; 
    case 3:
        Serial.print("Select an option:\n");
        Serial.print("3.1 Current Sensor Readings\n");
        Serial.print("3.2 Current Sensor Settings\n");
        Serial.print("3.3 Display Logged Data\n");
        Serial.print("3.4 Back\n");
        break;
    case 4:
        Serial.print("Select an option:\n");
        Serial.print("4.1 Manual Color Control\n");
        Serial.print("4.2 Automatic Color Control\n");
        Serial.print("4.3 Back\n");
        break;
    case 11:
        Serial.print("Sensors Sampling Interval\n");
        Serial.print("Current value: ");
        Serial.print(1.0 * samplingInterval / 1000);
        Serial.print(" seconds\n");
        Serial.print("Select a value between 1 and 10 seconds or -1 to go back: \n");
        break;
    case 12:
        Serial.print("Ultrasonic Alert Threshold\n");
        Serial.print("Current value: ");
        Serial.print(ultrasonicAlert* 0.034 / 2);
        Serial.print(" centimeters\n");
        Serial.print("Select a value between 2 and 200 centimeters or -1 to go back: \n");
        break;
    case 13:
        Serial.print("LDR Alert Threshold\n");
        Serial.print("Current value: ");
        Serial.print(LDRAlert);
        Serial.print("\n");
        Serial.print("Select a value between 0 and 1023 or -1 to go back: \n");
        break;
    case 21:
        short _samplingInterval, _ultrasonicAlert, _LDRAlert, _LEDColor[3];
        bool _autoLED, _autosave;

        EEPROM.get(0, _samplingInterval); //takes up 2 bytes
        EEPROM.get(2, _ultrasonicAlert); //takes up 2 bytes
        EEPROM.get(4, _LDRAlert); //takes up 2 bytes
        EEPROM.get(6, _LEDColor[0]); //takes up 2 bytes
        EEPROM.get(8, _LEDColor[1]); //takes up 2 bytes
        EEPROM.get(10, _LEDColor[2]); //takes up 2 bytes
        EEPROM.get(11, _autoLED); //needs 1 bit, we are allowing 1 byte because it`s the night before deadline :P
        EEPROM.get(12, _autosave); //same


        Serial.print("Settings saved in EEPROM: \n");

        Serial.print("Sampling interval: ");
        Serial.print(_samplingInterval / 1000);
        Serial.print(" seconds\n");

        Serial.print("Ultrasonic Alert Threshold: ");
        Serial.print(_ultrasonicAlert* 0.034 / 2);
        Serial.print(" centimeters\n");

        Serial.print("LDR Alert Threshold: ");
        Serial.print(_LDRAlert);
        Serial.print(" units\n");

        Serial.print("LED Auto Color: ");
        Serial.print((_autoLED)?("ON"):("OFF"));
        Serial.print("\n");

        Serial.print("Last saved LED Color: ");
        // Serial.print((_autoLED)?("ON"):("OFF"));
        Serial.print("\n");

        Serial.print("Autosave to EEPROM: ");
        Serial.print((_autosave)?("ON"):("OFF"));
        Serial.print("\n");

        Serial.print("Enter -1 to go back: \n");

        break;
    case 22:
        Serial.print("Autosave settings to EEPROM\n");
        Serial.print("Current value: ");
        Serial.print((autosave)?("ON"):("OFF"));
        Serial.print("\n");
        Serial.print("Select 1 - ON, 2 - OFF or -1 to go back: \n");
        break;
    case 23:
        updateEEPROM();
        Serial.print("Current settings have been saved to EEPROM\n");
        Serial.print("Enter -1 to go back: \n");
        break;
    case 31:
        Serial.print("Current readings\n");

        Serial.print("Ultrasonic Sensor: ");
        Serial.print(currentDistance());
        Serial.print(" centimeters\n");

        Serial.print("Photorezistor: ");
        Serial.print(currentLightLevel());
        Serial.print(" units\n");

        Serial.print("Sampling interval: ");
        Serial.print(samplingInterval / 1000);
        Serial.print(" seconds\n");
        break;
    case 32:
        Serial.print("Current settings\n");

        Serial.print("Sampling interval: ");
        Serial.print(samplingInterval / 1000);
        Serial.print(" seconds\n");

        Serial.print("Ultrasonic Alert Threshold: ");
        Serial.print(ultrasonicAlert* 0.034 / 2);
        Serial.print(" centimeters\n");

        Serial.print("LDR Alert Threshold: ");
        Serial.print(LDRAlert);
        Serial.print(" units\n");

        Serial.print("Enter -1 to go back: \n");
        break;
    case 33:
        //saved settings (EEPROM)

        break;
    case 41:
        break;
    case 42:
        //toggle auto led
        Serial.print("Toggle Automatic LED Color\n");
        Serial.print("Current value: ");
        Serial.print((autoLED)?("ON"):("OFF"));
        Serial.print("\n");
        Serial.print("Select 1 - ON, 2 - OFF or -1 to go back: \n");
        break;

    default:
    // Handles any choices outside the defined options
    Serial.print("The selected option is outside the scope of the menu\n");
  }
}

void currentMenuAction(){
  switch(currentMenu){
    case 31:
        if( millis() >= lastPrint + samplingInterval ){
          lastPrint = millis();
          screenFlush();
          printMenu();
          
        }
        
        break;

    default:
        break;
  }
}

// Function to print different messages based on the user's selection
void advanceMenu(int option) {

  if(currentMenu < MENUS){
    if(movementMatrix[currentMenu][option] != -1){
        currentMenu = movementMatrix[currentMenu][option];
    }else{
      notAnOption();
    }
    
  }
    
  else{
    switch(currentMenu){
      case 11: 
          if(option == -1){
            currentMenu = 1;
          }else{
            if(option >= 1 && option <= 10){
              samplingInterval = option * 1000;
              //TODO SAVE
            }else{
              wrongOption = true;
            }
          }
          break;
      case 12:
          if(option == -1){
            currentMenu = 1;
          }else{
            if(option >= 2 && option <= 200 ){
              //option = distance
              ultrasonicAlert = option * 2 / 0.034;
              //TODO SAVE
            }else{
              wrongOption = true;
            }
          }
          break;
      case 13:
          if(option == -1){
            currentMenu = 1;
          }else{
            if(option >= 0 && option <= 1023){
              LDRAlert = option;
              //TODO SAVE
            }else{
              wrongOption = true;
            }
          }
          break;
      case 21:
          if(option == -1){
            currentMenu = 2;
          }else{
            wrongOption = true;
          }
          break;
      case 22:
          //autosave
          if(option == -1){
            currentMenu = 2;
          }else{
            if(option == 1 || option == 2){
              autosave = option % 2; //turn 2 into 0(False) and 1 to 1(True)
            }else{
              wrongOption = true;
            }
          }
          break;
      case 23:
          if(option == -1){
            currentMenu = 2;
          }else{
            wrongOption = true;
          }
          break;
      case 31:
          break;
      case 32:
          currentMenu = 3;
          break;
      case 33:
          break;
      case 41:
          break;
      case 42:
          if(option == -1){
            currentMenu = 4;
          }else{
            if(option == 1 || option == 2){
              autoLED = option % 2; //turn 2 into 0(False) and 1 to 1(True)
            }else{
              wrongOption = true;
            }
          }
          break;
     
    }

    if(autosave){
      updateEEPROM();
    }
  }   
}

void notAnOption(){
  if(wrongOption){
    Serial.print("The selected option is outside the scope of the menu!\n");
    wrongOption = false;
  }
  
}

void screenFlush(){
  Serial.print("\n\n\n\n\n\n\n\n\n\n");
}

void readSensors(){
  if( millis() > lastSample + samplingInterval ){
          distance = currentDistance();
          lightLevel = currentLightLevel();  
          lastSample = millis();
        }
}

int currentDistance(){
  //returns current distance in cm

  //sper sa nu ma injuri pentru delayMicroseconds
  // Clears the trigPin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

int currentLightLevel(){
  return analogRead(PHOTOCELL_PIN);
}