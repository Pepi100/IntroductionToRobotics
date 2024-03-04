<h1 align="center" style="font-size:20">
Introduction to Robotics Course
</h1>

<p align="center">
Everything related to the course.
</p>

<p align="center">
  :microscope: <a href="#about">About</a>&#160;
  :pencil: <a href="#content">Content</a>&#160;
  :paperclip:<a href="#resources">Others</a>
</p>

## About

#### Course Objectives:
1. Development of POC (Proof of Concept) and Final Product Development Skills
2. Encouragement of Critical Thinking and Problem Solving
3. Programming Skills Development
4. Understanding Basic Robotics Concepts
5. Understanding and Using Microcontrollers

 This repo will contain all materials related to the laboratory.
 The code for each project is available in it's specific folder.

</br>

## Content

### Homework #2 : RGB Led
 
<img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%232%20-%20RGB%20Led/FinalDiagram.png" align="right"
     alt="Diagram" width="600">

#### Components Used

* 1x RGB Led
* 3x Potentiometers
* 1x Arduino Uno
* 1x Half breadboard
* 1x 220&#8486; rezistor
* 2x 100&#8486; rezistors
* many colorful wires

[Wokwi Implementation](https://wokwi.com/projects/379141484912992257)

[Demo link](https://youtu.be/U9Ul7x-ILts)



</br>
</br>
</br>

#### Technical Task

> This assignment focuses on controlling each channel (Red, Green, and Blue) of an RGB LED using individual potentiometers. By the end of this task, you will gain experience in interfacing potentiometers with the Arduino and controlling RGB LEDs based on the analog readings.

<details>
  <summary> Development process</summary>

  <h4>Version 1</h4>
  <img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%232%20-%20RGB%20Led/V1Diagram.png" align="right"
     alt="Diagram" width="500">
  <p style='color: crimson;'>1x 220&#8486; rezistor</p>
  
  
  <p>This initial version used only ore resistor for the entire circuit. It did work, however, the red LED was significantly brighter than the others. According to <a href="https://os.mbed.com/users/4180_1/notebook/rgb-leds/#:~:text=Resistor%20values%20are%20typically%20around,of%20the%20light%20wave%20increases.">this</a> article, the voltage drop of the LED tends to rise as the frequency of the light wave increases. Therefore, it is suitable to use different resistors for each color of the RGB LED.
  </p>
<!--   </br> -->
  <p>With the available choices, I've selected 2x 100&#8486; resistors for the blue and green LEDs.</p>

</br>
</br>
   <h4>Version 2</h4>
   
  <p style='color: crimson;'>Filtering signal</p>
  
  
  <p>
    This second version brings modifications to the code. The main flaw of version 1 was the flickering of the green LED when adjusting the other knobs. I`ve manually implemented a high pass filter such that values below a certain threshold would not register.
  </p>
    <p>
    LED values are now updated every 10 mills, attempting to reduce flickering and provide a smoother output.
  </p>
<!--   </br> -->
</details>



</br>
</br>

### Homework #3 : Elevator
 
<img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%233%20-%20Elevator/Diagram.png" align="right"
     alt="Diagram" width="500">

#### Components Used

* 5x LEDs
* 4x Buttons
* 1x Active Buzzer
* 1x Arduino Uno
* 1x Full breadboard
* 1x Mini breadboard
* 4x 220&#8486; rezistor
* 2x 100&#8486; rezistors
* many colorful wires

[Wokwi Implementation](https://wokwi.com/projects/380099046031760385)

[Demo link](https://youtu.be/kjwKA3ZZ8L0)

#### Technical Task
>This assignment involves simulating a 3-floor elevator control system using
LEDs, buttons, and a buzzer with Arduino. By the end of this task, you will gain
experience in using button state change, implementing debouncing techniques,
and coordinating multiple components to represent real-world scenarios.

<details>
  <summary> How it works:</summary>

  <p>
    The first part of the main loop is dedicated to deboucing the 4 buttons. Each iteration of loop() checks whether button _#indexButton_ has been pressed and starts the debouncing proccess.
  </p>

  <p>
    The elevator is controlled in a 5 stage system:
  </p>

| Stage | Meaning           |
| ------------- |:-------------:|
| -2     | descending | 
| -1 | has descended, is now stopped|
| 0 | completedly stopped      |
| 1 | has descended, is now stopped|
| 2 | ascending      |

Stages -1 and 1 are used to keep a smoother operation of the elevator. A real evelator tends to keep the direction of movement unless there are no floors to visit in that direction.
For example:
```
  Elevator is at floor 2;
  Buttons on floors 3, 1 and 4 are pressed in this order;
  The common order we would want the elevator to travel is: 3 -> 4 -> 1, despite the actual pressing order.
```
This is implemented by keeping track of the last direction of travel and prioritizing the visit of floors in that direction.

<p>
    Similarly, a stage system is used to keep track of the functionality of the doors:
  </p>

| Stage | Meaning           |
| ------------- |:-------------:|
| -2     | opening | 
| -1 | closing |
| 0 | closed|
| 1 | open|

Every time a new floor is reached, the elevator checks whether the button for that floor has been pressed and only opens the doors if that is the case.
During closing and opening of the doors, a 2-note sound is played.


</details>


</br>
</br>

### Homework #4 : 7 - Segment Display
 
<img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%234%20-%207%20Segment/Diagram.png" align="right"
     alt="Diagram" width="500">

#### Components Used

* 1x 7-Segment Display
* 1x Joystick
* 1x Arduino Uno
* 1x Half breadboard
* 1x Mini breadboard
* 8x 330&#8486; rezistors
* many colorful wires

[Wokwi Implementation](https://wokwi.com/projects/380141001565991937)

[Wokwi Implementation](https://wokwi.com/projects/380383384120190977) - using [interrupts](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/).

[Demo link](https://youtu.be/Je8YQQhEayg)

#### Technical Task
>The task involves using the joystick to control the position of the segment and "draw" on the display. The objective is to ensure that the movement between segments is natural, allowing jumps only to neighboring positions without passing through "walls."
>The initial position should be on the DP. The current
position always blinks (irrespective of the fact that the segment is on or
off). Use the joystick to move from one position to neighbors (see table for
corresponding movement). Short pressing the button toggles the segment
state from ON to OFF or from OFF to ON. Long pressing the button
resets the entire display by turning all the segments OFF and moving the
current position to the decimal point.

<details>
  <summary> How it works:</summary>

  <p>
    In the first part of the program we declare the movement matrix that keeps track of the possible moves from each position on the 7-segment display.
  </p>

Current| UP | DOWN | LEFT | RIGHT
| ----- |  ----- |  ----- |  ----- |  ----- |
a | N/A | g | f | b
b | a | g | f | N/A
c | g | d | e | dp
d | g | N/A | e | c
e | g | d | N/A | c
f | a | g | N/A | b
g | a | d | N/A | N/A
dp | N/A | N/A | c | N/A



</details>

</br>
</br>

### Homework #5 : Stopwatch
 
<img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%235%20-%20Stopwatch/Diagram.png" align="right"
     alt="Diagram" width="500">

#### Components Used

* 1x 4 digit 7 Segment Display
* 3x Buttons
* 1x Arduino Uno
* 2x Half breadboards
* 1x 74HC595shift register
* many 330&#8486; rezistors 
* many colorful wires

[Wokwi Implementation](https://wokwi.com/projects/381129895179259905)

[Demo link](https://youtu.be/vy33fhZronc)

#### Technical Task
>Using the 4-digit 7-segment display and three buttons, the task is implementing a stopwatch timer capable of counting in tenths of a second. Additionally, the design should incorporate a save lap functionality, akin to the basic stopwatch features commonly found on most phones.

<details>
  <summary> How it works:</summary>




</details>


</br>
</br>

### Homework #6 : 7 - Environment Monitor
 
<img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%236%20-%20Environment%20Monitor%20and%20Logger/Diagram.png" align="right"
     alt="Diagram" width="500">

#### Components Used

* 1x RGB Led
* 1x Ultrasonic Sensor (HC-SR04)
* 1x Light-Dependent Resistor
* 1x Arduino Uno
* 1x Half breadboard
* 1x Mini breadboard
* 1x 220&#8486; rezistor
* 1x 10K&#8486; rezistor
* 2x 100&#8486; rezistors
* many colorful wires

[Wokwi Implementation](https://wokwi.com/projects/381915594073211905) - code only.



[Demo link]() - TBA

#### Technical Task
>The task involves developing a "Smart Environment Monitor and Logger" using Arduino. This system aims to utilize various sensors for gathering environmental data, logging this information into EEPROM, and offering visual feedback through an RGB LED. Additionally, it should provide user interaction via a Serial Menu. The project emphasizes the integration of sensor readings, memory management, Serial Communication, and the overall goal of constructing a menu.

>In order to prevent wear on the EEPROM, the system should avoid excessive writing. It is recommended to refrain from using EEPROM.write and instead utilize EEPROM.update() or EEPROM.put() for more efficient write cycles.

>Calibration of sensors is crucial for obtaining accurate readings. It is imperative to ensure that sensors are correctly calibrated, and their interval values are well-known and accounted for in the system.

>To enhance the robustness of Serial Communication, the system should implement error handling mechanisms. This includes the ability to manage and respond to incorrect inputs, ensuring a more reliable and resilient communication interface.


<details>
  <summary> How it works:</summary>

  #### Main Loop
  <img src="https://github.com/Pepi100/IntroductionToRobotics/blob/master/%236%20-%20Environment%20Monitor%20and%20Logger/Loop.png" align="right"
     alt="Diagram" width="500">
  
  The main loop constantly reads data form the sensors and triggers the alert if necessary. It is also responsible for reading input from [serial](https://www.arduino.cc/reference/en/language/functions/communication/serial/), which it than passes to:

  ```cpp
    void advanceMenu(int option);
  ```
  This function takes over the main functionality of the program. It takes the input from the user and uses it to perform the required action, according to the number of the current menu. This function implements a giant switch.



  ```cpp
    void printMenu();
  ```
  Works identical to advanceMenu(), but is only responsible for printing the options available in the current menu.



  ```cpp
  short movementMatrix[MENUS][MAX_MENU_OPTIONS]={
    {-1,1,2,3,4},
    {-1,11,12,13,0},
    {-1,21,22,23,0},
    {-1,31,32,33,0},
    {-1,41,42,0,-1},
  };
  ```
  In order to traverse faster between menus, I've implemented this movement matrix that keeps track of what menu (or submenu) the program should switch to next.




</details>

</br>
</br>

### Resources
1. :triangular_ruler: [Wokwi](https://wokwi.com/) - Project diagram application.
2. :clubs: [Arduino Style Guide](https://github.com/Irikos/arduino-style-guide) - Style guided started by Andrei Dumitriu.
3. :blue_book: [Arduino Language Reference](https://www.arduino.cc/reference/en/) - Arduino Documentation.

### Credits
- All courses, laboratories and homework assignments were provided by Ph. D candidate [Andrei Dumitriu](https://github.com/Irikos).
-  Lab tutor, friendly face and always there to answer questions: [Vlad Toader](https://github.com/vladfxstoader) 
