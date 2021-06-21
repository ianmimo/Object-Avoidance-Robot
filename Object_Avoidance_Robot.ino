/*
# Author: Papuatronics
# Course: Ultrasonic Robot Car 
# Sensor: The input is an Ultrasonic Sensor.
# Purpose: To create a four Wheeled obstacle avoidance Robot.
#          The robot will move forward and as soon as it detects an obstacle that is infront of it,
#          it will scan the surrounding and rotate to the way where there is no obstacle.
*/

// Setup the library needed for the servo and ultrasonic sensor. 
#include<Servo.h>
#include <NewPing.h> 

// Declare variables for motor 1.
// If you use either pin 9 or pin 10 for servo motor, you cannot use pin 9 or 10 for the ENA or ENB 
// Otherwise the motor only run one of your motors.
#define ENA 11
#define IN1 8
#define IN2 7

// Declare variables for motor 2.
#define ENB 3
#define IN3 5
#define IN4 4

// Declare servo motor.
#define SERVOPIN 10
Servo MYSERVO;

// Declare ultrasonic sensor variable.
#define TRIGPIN A0
#define ECHOPIN A1

// Declare some variables that will be used for calculation later in the code.
int DURATION;
int DISTANCE;
int DISTANCELEFT;
int DISTANCERIGHT;

// Setup the motors and sensor and it will only run once.
void setup() {

  // To see the result in the serial monitor.
  Serial.begin(9600);
  
  // Setup the ultrasonic sensor.
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  // Setup the servo motor and initialisation of the servo motor.
  MYSERVO.attach(SERVOPIN);
  MYSERVO.write(90);
  
  // Setup the motor A and B as OUTPUT.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
   
  // The motor will not move for 5 seconds so you have time to put it down.
  // Always remember that 1 second = 1000 milliseconds.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(5000);
  
}

// This is where your main code will be in.
// The main loop that will run continuously.
void loop() {

  // Set the ultrasonic sersor to LOW first to clean the input before it starts read data.
  digitalWrite(TRIGPIN, LOW);
  delay(5);
  digitalWrite(TRIGPIN, HIGH);
  delay(8);
  digitalWrite(TRIGPIN, LOW);


  // Use the variables declared above to save data.
  // The DISTANCE formula is the speed of sound 0.0343 is in cm/microsecond multiply by the duration.
  // since the duration is the total distance(Out to the object and bounces of the object and come back), 
  // thats why we need to devide it by 2 to get the distance.  
  DURATION = pulseIn(ECHOPIN, HIGH);
  DISTANCE = (DURATION*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(DISTANCE);
  delay(5);

  // This following loop is when the ultrasonic detects the distance to be 30cm it will stop robot from moving.
  // The robot will stop and look left and right.
  // If the robot detects that the left or right distance is larger that the other,
  // The robot will turn to the direction of the larger distance.
  // The delay time is just a preference. Remember the delay is in millisecond. 
   
  if (DISTANCE <= 25){
  
    MOVEBACKWARD();
    delay(100);
    STOPMOVE();
    delay(100);
  
    LOOKLEFT();
    delay(500);
    LOOKRIGHT();
    delay(500);

    if (DISTANCELEFT >= DISTANCE){
      
     TURNLEFT();
     delay(400);
      
      }
      
    else{
      
      TURNRIGHT();
      delay(400);
     
      }

   }
    
    else{
      MOVEFORWARD();
      delay(100);
    
    }
    
 }


// This library is for moving the motors forward
// The speed of the motor stars from (0-255).
// I purposely set the speed of the motor to be 150 so it is not too fast.

void MOVEFORWARD(){
  
  analogWrite(ENA, 90);
  analogWrite(ENB, 90);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(10);
  }
  
// This library is to make the robot stop moving
void STOPMOVE(){

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(10);
  }

// This library is to make the robot moving backward.
void MOVEBACKWARD(){
  
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(10);
  }

// This library is to make the robot looking to left.
void LOOKLEFT(){
  
  MYSERVO.write(155);
  delay(500);
  MYSERVO.write(90);
  }
  
// This library is to make the robot looking to the right.
void LOOKRIGHT(){
  
  MYSERVO.write(30);
  delay(500);
  MYSERVO.write(90);
  }

// This library is to make the robot to turn left.  
void TURNLEFT(){
  
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(10);
  }
  
// This library is to make the  robot to turn right.
void TURNRIGHT(){
  
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(10);
  }
