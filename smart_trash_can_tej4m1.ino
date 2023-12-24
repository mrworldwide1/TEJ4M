// include the servo library and make new servo objects
#include <Servo.h>
Servo servo1;
Servo servo2;

// pushbutton
bool lock = false;
bool buttonPressable = true;
const int buttonPin = 3; // button connected to digital pin 2
// servo activation distance
int distanceVal = 30;

// define ultrasonic distance sensor pins
const int trigPin1 = 9;
const int echoPin1 = 8;
// define variables used for distance sensor
long duration1;
int distance;

//////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); //use serial port with baud rate of 9600
  // first servo
  servo1.attach(7);
  servo1.write(0);
  delay(200);
  // second servo
  servo2.attach(6);
  servo2.write(0);
  delay(200);
  pinMode(trigPin1, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);   // Sets the echoPin as an Input
  pinMode(buttonPin, INPUT); //output button push status as variable
}

void loop() {
  int buttonState = digitalRead(buttonPin); //store button status as variable
  distanceReady();
  functionality();
  
  // change servo lock state
  if (buttonState == HIGH && buttonPressable == true){
    lock = !lock;
    }
    
  // this prevents holding the button down
  if (buttonState == HIGH && buttonPressable == true){
    buttonPressable = false;
  } else if (buttonState == LOW){
    buttonPressable = true;
  }
  
  // debug to serial monitor
    Serial.println(lock);
}

void distanceReady() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads echoPin, returns the sound wave travel time in ms
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating distance
  distance = duration1 * 0.034 / 2;
}

// main code that opens/closes the trash can
void functionality() {
  // open can when near
  if (distance <= distanceVal && lock == false) {
    servo1.write(90);
    servo2.write(90);
    delay(200);
    // close can when far
  } else if (distance > distanceVal && lock == false) {
    servo1.write(0);
    servo2.write(0);
    delay(200);
    // freeze servo
  } else if (lock == true){
    delay(200);
  }}
