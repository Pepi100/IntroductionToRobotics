#define FLOOR_NUMBER 4
#define START_FLOOR 0

// values in miliseconds
#define DEBOUNCE_DELAY 25
#define TRAVEL_TIME 1500
#define BLINK_TIME 150
#define DOORS_TIME 500
#define WAIT_TIME 2000

#define FIRST_NOTE 120
#define SECOND_NOTE 150


//buzzer
const int buzzerPin = 8;

// blinking
const int blinkLedPin =13;
unsigned long lastBlink;
bool blinkState=0;

struct floor{
  int ledPin;
  int buttonPin;
  bool buttonPressed;
  
  // debounce variables
  int reading;
  int buttonState;
  unsigned long lastButtonState;
  unsigned long lastDebounceTime;

}floors[FLOOR_NUMBER];

int floorIndex=0;

//current elevator position
int elevator = START_FLOOR;

int doors = 1; //doors are intially opened;
// 0 closed
//-1 opening
//-2 closing
unsigned long doorTime;
unsigned long doorOpenTime=0;

//direction the elevator is moving
//-2 is moving down, 2 is moving up
//-1 has just moved down but is now stopped
// 1 has just mooved up
int state = 0; 
unsigned long travelStartTime;



void setup() {

  //initialize pins
  for(int i=0; i<FLOOR_NUMBER; i++){
    floors[i].buttonPin=i+2;
    floors[i].ledPin=12-i;
    pinMode(floors[i].buttonPin, INPUT_PULLUP);
    pinMode(floors[i].ledPin, OUTPUT);
  }

  digitalWrite(floors[elevator].ledPin, HIGH);
  pinMode(blinkLedPin, OUTPUT);
  Serial.begin(9600);//debug



  // tone(buzzerPin, FIRST_NOTE);

}


void blinkUpdate(){

  if( abs(state) == 2){ //elevator is going up or down
    if(millis() > lastBlink + BLINK_TIME){
      blinkState= !blinkState;
      digitalWrite(blinkLedPin, blinkState);
      lastBlink = millis();

    }

  }
}

void takePassangers(){
  
}

void doorSound(){
  if(doors == -1){
    if(millis() >= doorTime+ DOORS_TIME/2){
      noTone(buzzerPin);
      tone(buzzerPin, SECOND_NOTE);
    }
    if(millis() >= doorTime+ DOORS_TIME){
      noTone(buzzerPin);
      doors =1;
    }
  }

}

void loop() {

  //with every iteration, current position LED;
    // showCurrentFloor();
    blinkUpdate();

  //read each button value

    floors[floorIndex].reading = digitalRead(floors[floorIndex].buttonPin);
    if (floors[floorIndex].reading != floors[floorIndex].lastButtonState) {
      // reset the debouncing timer
      floors[floorIndex].lastDebounceTime = millis();
    }

    if ((millis() - floors[floorIndex].lastDebounceTime) > 25) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (floors[floorIndex].reading != floors[floorIndex].buttonState) {
      floors[floorIndex].buttonState = floors[floorIndex].reading;
      // only toggle the LED if the new button state is HIGH
      if (floors[floorIndex].buttonState == LOW) {
        //set state
        floors[floorIndex].buttonPressed=1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  floors[floorIndex].lastButtonState = floors[floorIndex].reading;
  


// at this point, after all that effort, we can properly read button input


if(doors == -2){
    //closing
    if(millis() >= doorTime+ DOORS_TIME){
      noTone(buzzerPin);
      doors =0;
      travelStartTime= millis();
    }else{
      if(millis() >= doorTime+ DOORS_TIME/2 ){
      tone(buzzerPin, FIRST_NOTE);
    }
    }

}else if(doors == -1){
  //opening
  if(millis() >= doorTime+ DOORS_TIME){
      noTone(buzzerPin);
      doors =1;
      //doors should stay open at least 2 seconds
      doorOpenTime=millis();
      
    }else{
      if(millis() >= doorTime+ DOORS_TIME/2 ){
      tone(buzzerPin, SECOND_NOTE);
    }
    }
    


}
else
  if(doorOpenTime + WAIT_TIME <= millis())
  switch(state){
  // daca stam degeaba, acceptam sa mergem in orice directie
  case 0:
        //scan for a new level to go to;
        for(int i=0; i<FLOOR_NUMBER;i++){
          if(floors[i].buttonPressed==1){
             
                
             
             if(i>elevator){
              state=2; // start ascending state
              //check if doors are open
              if(doors == 1){
                //start doors closing action
                doors=-2;
                doorTime = millis();
                tone(buzzerPin, SECOND_NOTE);
              }else{
                travelStartTime= millis();
              }
              
             }else{
              state=-2;// start descending state
              if(doors == 1){
                //start doors closing action
                doors=-2;
                doorTime = millis();
                tone(buzzerPin, SECOND_NOTE);
              }else{
                travelStartTime= millis();
              }
             }
             
             i=FLOOR_NUMBER;
          }
        }
        break;
//daca am urcat anterior, vom incerca prima data sa continuam urcarea
// daca nu este nimic deasupra revenim in starea de repaus
  case 1:
        // we delay state change until the doors are open
        // if(doors == 0){
        //   doors = -1; //-1 = opening
        //   doorTime= millis();
        //   tone(buzzerPin, FIRST_NOTE);
        // }
        //scan for a new level to go to;
        for(int i=elevator+1; i<FLOOR_NUMBER;i++){
          if(floors[i].buttonPressed==1){
             
              
              state=2; // start ascending state
            
              //check if doors are open
              if(doors == 1){
                //start doors closing action
                doors=-2;
                doorTime = millis();
                tone(buzzerPin, SECOND_NOTE);
              }else{
                travelStartTime= millis();
              }
      
             i=FLOOR_NUMBER;
          }
        }
        if(state == 1)
          state=0;
        break;

  case -1:
        //scan for a new level to go to;
        for(int i=elevator-1; i>=0;i--){
          if(floors[i].buttonPressed==1){
            
              state=-2;// start descending state
              if(doors == 1){
                //start doors closing action
                doors=-2;
                doorTime = millis();
                tone(buzzerPin, SECOND_NOTE);
              }else{
                travelStartTime= millis();
              }
              
             
             i=-1;
          }
        }
        if(state == -1)
          state=0;
        break;

  case 2:
        if(millis() >= travelStartTime + TRAVEL_TIME){
          digitalWrite(floors[elevator].ledPin, LOW);
          elevator++;
          digitalWrite(floors[elevator].ledPin, HIGH);
        
          state=1;
          //we arrive, now we open the doors
          //we should first check for passangers and open the doors if there are any
          if(floors[elevator].buttonPressed == 1){
          doors=-1;
          doorTime = millis();
          tone(buzzerPin, FIRST_NOTE);
          }

          
        }
       
        break;

  case -2:
      if(millis() >= travelStartTime +TRAVEL_TIME){
        digitalWrite(floors[elevator].ledPin, LOW);
        elevator --;
        digitalWrite(floors[elevator].ledPin, HIGH);


        state=-1;

        //we arrive, now we open the doors
        //we should first check for passangers and open the doors if there are any
        if(floors[elevator].buttonPressed == 1){
        doors=-1;
        doorTime = millis();
        tone(buzzerPin, FIRST_NOTE);
        }
      }
      break;


}

//if doors are open, take passangers from current floor
if(doors == 1){
  floors[elevator].buttonPressed = 0;
}

floorIndex= (floorIndex +1 )% FLOOR_NUMBER;
// Serial.print(state);
// Serial.print(" ");
// Serial.println(doors);



}
