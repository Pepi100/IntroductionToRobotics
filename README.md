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

 This repo will contain all materials related to the course.

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

[Demo link](https://youtu.be/U9Ul7x-ILts)

#### Technical Task
>This assignment involves simulating a 3-floor elevator control system using
LEDs, buttons, and a buzzer with Arduino. By the end of this task, you will gain
experience in using button state change, implementing debouncing techniques,
and coordinating multiple components to represent real-world scenarios.


</br>
</br>

### Resources
1. :triangular_ruler: [Wokwi](https://wokwi.com/) - Project diagram application.
2. :clubs: [Arduino Style Guide](https://github.com/Irikos/arduino-style-guide) - Style guided started by Andrei Dumitriu.
3. :blue_book: [Arduino Language Reference](https://www.arduino.cc/reference/en/) - Arduino Documentation.

### Credits
- All courses, laboratories and homework assignments were provided by Ph. D candidate [Andrei Dumitriu](https://github.com/Irikos).
-  Lab tutor, friendly face and always there to answer questions: [Vlad Toader](https://github.com/vladfxstoader) 
