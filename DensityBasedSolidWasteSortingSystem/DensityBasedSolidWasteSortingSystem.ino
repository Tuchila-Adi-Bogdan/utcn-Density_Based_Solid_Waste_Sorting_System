#include <Arduino.h>
#include "HX711.h"

//Ultrasonic Sensor
const int trigPin = 7;
const int echoPin = 6;
float duration, distance1, distance2;
//Ultrasonic Sensor

//Weight Sensor
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;
//Weight Sensor

//DC Motors

// Pins for Motor 1
const int motor1Dir1 = 10;  // Direction pin 1 for motor 1
const int motor1Dir2 = 11;  // Direction pin 2 for motor 1

// Pins for Motor 2
const int motor2Dir1 = 8;  // Direction pin 1 for motor 2
const int motor2Dir2 = 9;  // Direction pin 2 for motor 2
const int motor2Enable = 10; // Enable pin (PWM) for motor 2

//DC Motors


void BaseMotorRotationPLUS(float value)
{
  digitalWrite(motor1Dir1, HIGH); 
  digitalWrite(motor1Dir2, LOW);
  delay(value);
}
void BaseMotorRotationMINUS(float value)
{
  digitalWrite(motor1Dir1, LOW); 
  digitalWrite(motor1Dir2, HIGH);
  delay(value);
}
void BaseMotorSTOP()
{
  digitalWrite(motor1Dir1, LOW); 
  digitalWrite(motor1Dir2, LOW);
}

void Motor2RotationPLUS(float value)
{
  digitalWrite(motor2Dir1, HIGH); 
  digitalWrite(motor2Dir2, LOW);
  delay(value);
}
void Motor2RotationMinus(float value)
{
  digitalWrite(motor2Dir1, LOW); 
  digitalWrite(motor2Dir2, HIGH);
  delay(value);
}
void motor2STOP()
{
  digitalWrite(motor2Dir1, LOW); 
  digitalWrite(motor2Dir2, LOW);
}


void setup() {
  //Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(57600);
  //Ultrasonic Sensor

  //Weight Sensor
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(98.827);

  scale.tare();               // reset the scale to 0
  //Weight Sensor

  //DC Motors
   // Set all motor control pins as OUTPUT
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);

  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);
  //DC Motors

  BaseMotorSTOP();
  motor2STOP();  

}


void loop() 
{
  delay(500);
  //volumee of the vase is 207 cm^2
  //Base is 426.38,  height is 9
  //Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH) / 1.0;
  distance1 = (duration*.0343)/2.0;
  Serial.print("Distance: ");
  Serial.println(distance1, 6);
  delay(100);
  //Ultrasonic Sensor

  Serial.println("Initialization Done -- Place Object on the Scale");
  delay(10000);
  float mass;
  Serial.print("\t| average:\t");
  mass = scale.get_units(10);
  mass = 4.09948;
  Serial.println(mass, 5);
  delay(1000);
  ///Lift from scale
  Serial.println("Lift from scale - beginning");
  bool ok = true;
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Add duration for motor spin");

    int value = -1; // Initialize to an invalid value
    while (value < 0) 
    { // Ensure we get a positive input
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      value = Serial.parseInt();
      if (value < 0) 
      {
        Serial.println("Invalid value. Input a positive value.");
      }
    }

    // Perform motor operation
    Motor2RotationPLUS(value);
    motor2STOP();

    Serial.print("Motor 2 movent for ");
    Serial.print(value);
    Serial.println(" units");

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Go to next step? 1 - Yes 0 - No");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) 
    {
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) 
      {
        Serial.println("Input invalid. Please input 1 or 0.");
      }
    }

    // Decide whether to continue
    if (response == 1) 
    {
      ok = false; // Exit the loop
    }

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

  }
  ///Lift from scale Done
  Serial.println("Lift from scale done, beggining movement above water.");
  ok=true;
// Spin until above water
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Add duration for motor spin");

    int value = -1; // Initialize to an invalid value
    while (value < 0) { // Ensure we get a positive input
      while (Serial.available() == 0) {
        // Wait for input
      }
      value = Serial.parseInt();
      if (value < 0) {
        Serial.println("Invalid value. Input a positive value.");
      }
    }

    // Perform motor operation
    BaseMotorRotationMINUS(value);
    BaseMotorSTOP();

    Serial.print("Motor 2 movent for ");
    Serial.print(value);
    Serial.println(" units");

    // Flush the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Go to next step? 1 - Yes 0 - No");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) {
      while (Serial.available() == 0) {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) {
        Serial.println("Input invalid. Please input 1 or 0.");
      }
    }

    // Decide whether to continue
    if (response == 1) {
      ok = false; // Exit the loop
    }
    while (Serial.available() > 0) 
    {
      Serial.read();
    }
  }
// Spin until above water DONE
  Serial.println("Moving above water done, begginnig lowering in water.");
  ok=true;
  ///COBOARA IN APA
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Add duration for motor spin");

    int value = -1; // Initialize to an invalid value
    while (value < 0) { // Ensure we get a positive input
      while (Serial.available() == 0) {
        // Wait for input
      }
      value = Serial.parseInt();
      if (value < 0) {
        Serial.println("Invalid value. Input a positive value.");
      }
    }

    // Perform motor operation
    Motor2RotationMinus(value);
    motor2STOP();

    Serial.print("Motor 2 movent for ");
    Serial.print(value);
    Serial.println(" units");

    // Flush the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Go to next step? 1 - Yes 0 - No");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) {
      while (Serial.available() == 0) {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) {
        Serial.println("Input invalid. Please input 1 or 0.");
      }
    }

    // Decide whether to continue
    if (response == 1) {
      ok = false; // Exit the loop
    }

    // Flush the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }

  }
//Lowering in water done.
  Serial.println("Lowering in water done, begin lifting out of water.");
  delay(1000);

  //Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH) / 1.0;
  distance2 = (duration*.0343)/2.0;
  //distance2 = distance1 + 0.00647499;
  Serial.print("Distance: ");
  Serial.println(distance2, 6);
  delay(100);
  //Ultrasonic Sensor
  Serial.println("Beggining lifting out of water.");
  ok=true;
  ///Lifting out of water.
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Add duration for motor spin");

    int value = -1; // Initialize to an invalid value
    while (value < 0) 
    { // Ensure we get a positive input
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      value = Serial.parseInt();
      if (value < 0) 
      {
        Serial.println("Invalid value. Input a positive value.");
      }
    }

    // Perform motor operation
    Motor2RotationPLUS(value);
    motor2STOP();

    Serial.print("Motor 2 movent for ");
    Serial.print(value);
    Serial.println(" units");

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Go to next step? 1 - Yes 0 - No");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) 
    {
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) 
      {
        Serial.println("Input invalid. Please input 1 or 0.");
      }
    }

    // Decide whether to continue
    if (response == 1) 
    {
      ok = false; // Exit the loop
    }

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

  }
  ///Lifting out of water Done
  Serial.println("Lifting out of water Done");
  delay(1000);
  Serial.println("Object's mass is ");
  Serial.print(mass);
  Serial.print(" grams.");
  Serial.println("");
  float volume = (distance2-distance1) * 426.38;
  //float volume = 0.006409*426.38;

  Serial.println("Object's volume is  ");
  delay(100);
  Serial.print(volume);
  delay(100);
  Serial.print(" cm^3.");
  delay(100);
  float density = mass / volume ;
  Serial.println("");
  Serial.println("Object's density is  ");
  Serial.print(density);
  Serial.print(" g/cm^3.");
  Serial.println("");
  delay(100);
  Serial.println("Plastic PET density is 1.38-1.41 g/cm^3");
  Serial.println("Aluminium denisty is 2.7 g/cm^3");
  Serial.println("Glass denisty is 2.4-2.6 g/cm^3");
  delay(100);
  if(density > 2.7)
    Serial.println("So, the object is made of aluminium !");
  else if(density > 1.9)
    Serial.println("So, the object is made of glass !");
  else
    Serial.println("So, the object is made of plastic !");
  delay(99999);
}