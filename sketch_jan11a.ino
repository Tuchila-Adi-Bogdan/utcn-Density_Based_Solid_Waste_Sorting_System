#include <Arduino.h>
#include "HX711.h"

//Senzor Ultrasonic
const int trigPin = 7;
const int echoPin = 6;
float duration, distance1, distance2;
//Senzor Ultrasonic

//Senzor Greutate
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;
//Senzor Greutate

//Motoare

// Pins for Motor 1
const int motor1Dir1 = 10;  // Direction pin 1 for motor 1
const int motor1Dir2 = 11;  // Direction pin 2 for motor 1

// Pins for Motor 2
const int motor2Dir1 = 8;  // Direction pin 1 for motor 2
const int motor2Dir2 = 9;  // Direction pin 2 for motor 2
const int motor2Enable = 10; // Enable pin (PWM) for motor 2

//Motoare

void motorBazaRotatiePLUS(float valoare)
{
  digitalWrite(motor1Dir1, HIGH); 
  digitalWrite(motor1Dir2, LOW);
  delay(valoare);
}
void motorBazaRotatieMINUS(float valoare)
{
  digitalWrite(motor1Dir1, LOW); 
  digitalWrite(motor1Dir2, HIGH);
  delay(valoare);
}
void motorBazaSTOP()
{
  digitalWrite(motor1Dir1, LOW); 
  digitalWrite(motor1Dir2, LOW);
}

void motor2RotatiePLUS(float valoare)
{
  digitalWrite(motor2Dir1, HIGH); 
  digitalWrite(motor2Dir2, LOW);
  delay(valoare);
}
void motor2RotatieMINUS(float valoare)
{
  digitalWrite(motor2Dir1, LOW); 
  digitalWrite(motor2Dir2, HIGH);
  delay(valoare);
}
void motor2STOP()
{
  digitalWrite(motor2Dir1, LOW); 
  digitalWrite(motor2Dir2, LOW);
}


void setup() {
  //Senzor Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(57600);
  //Senzor Ultrasonic

  //Senzor Greutate
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(98.827);

  scale.tare();               // reset the scale to 0
  //Senzor Greutate

  //Motoare
   // Set all motor control pins as OUTPUT
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);

  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);
  //Motoare

  motorBazaSTOP();
  motor2STOP();  

}


void loop() {
  delay(500);
  //Volumul vasului este de 207 centimetri^2
  //Baza este 426.38, inaltimea 9
  //Senzor Ultrasonic
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
  //Senzor Ultrasonic

  Serial.println("Initializare Gata - Plaseaza greutatea pe cantar");
  delay(10000);
  float greutate;
  Serial.print("\t| average:\t");
  greutate = scale.get_units(10);
  greutate = 4.09948;
  Serial.println(greutate, 5);
  delay(1000);
  ///RIDICARE DE PE CANTAR
  Serial.println("Incepe ridicarea de pe cantar");
  bool ok = true;
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Introduceti valoare (durata pentru motor):");

    int valoare = -1; // Initialize to an invalid value
    while (valoare < 0) 
    { // Ensure we get a positive input
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      valoare = Serial.parseInt();
      if (valoare < 0) 
      {
        Serial.println("Valoare invalida. Introduceti o valoare pozitiva.");
      }
    }

    // Perform motor operation
    motor2RotatiePLUS(valoare);
    motor2STOP();

    Serial.print("Motorul 2 a urcat timp de ");
    Serial.print(valoare);
    Serial.println(" unitati");

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Treceti la urmatorul pas? 1-DA, 0-NU");

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
        Serial.println("Input invalid. Va rog introduceti 1 sau 0.");
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
  ///RIDICARE DE PE CANTAR GATA
  Serial.println("Ridicarea de pe cantar gata, incepe mutarea deasupra apei");
  ok=true;
  ///INVARTE PANA DEASUPRA LA APA
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Introduceti valoare (durata pentru motor):");

    int valoare = -1; // Initialize to an invalid value
    while (valoare < 0) { // Ensure we get a positive input
      while (Serial.available() == 0) {
        // Wait for input
      }
      valoare = Serial.parseInt();
      if (valoare < 0) {
        Serial.println("Valoare invalida. Introduceti o valoare pozitiva.");
      }
    }

    // Perform motor operation
    motorBazaRotatieMINUS(valoare);
    motorBazaSTOP();

    Serial.print("Motorul 2 a urcat timp de ");
    Serial.print(valoare);
    Serial.println(" unitati");

    // Flush the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Treceti la urmatorul pas? 1-DA, 0-NU");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) {
      while (Serial.available() == 0) {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) {
        Serial.println("Input invalid. Va rog introduceti 1 sau 0.");
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
  ///INVARTE PANA DEASUPRA LA APA GATA
  Serial.println("Mutarea deasupra apei gata, incepe coborarea in apa");
  ok=true;
  ///COBOARA IN APA
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Introduceti valoare (durata pentru motor):");

    int valoare = -1; // Initialize to an invalid value
    while (valoare < 0) { // Ensure we get a positive input
      while (Serial.available() == 0) {
        // Wait for input
      }
      valoare = Serial.parseInt();
      if (valoare < 0) {
        Serial.println("Valoare invalida. Introduceti o valoare pozitiva.");
      }
    }

    // Perform motor operation
    motor2RotatieMINUS(valoare);
    motor2STOP();

    Serial.print("Motorul 2 a urcat timp de ");
    Serial.print(valoare);
    Serial.println(" unitati");

    // Flush the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Treceti la urmatorul pas? 1-DA, 0-NU");

    int response = -1; // Initialize to an invalid value
    while (response != 0 && response != 1) {
      while (Serial.available() == 0) {
        // Wait for input
      }
      response = Serial.parseInt();
      if (response != 0 && response != 1) {
        Serial.println("Input invalid. Va rog introduceti 1 sau 0.");
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
  ///COBOARA IN APA GATA
  Serial.println("Coborarea in apa gata, masuram distanta si incepe ridicarea din apa");
  delay(1000);

  //Senzor Ultrasonic
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
  //Senzor Ultrasonic
  Serial.println("Incepe ridicarea din apa");
  ok=true;
  ///RIDICA DIN APA
  while (ok) {
    // Ask for the motor rotation value
    Serial.println("Introduceti valoare (durata pentru motor):");

    int valoare = -1; // Initialize to an invalid value
    while (valoare < 0) 
    { // Ensure we get a positive input
      while (Serial.available() == 0) 
      {
        // Wait for input
      }
      valoare = Serial.parseInt();
      if (valoare < 0) 
      {
        Serial.println("Valoare invalida. Introduceti o valoare pozitiva.");
      }
    }

    // Perform motor operation
    motor2RotatiePLUS(valoare);
    motor2STOP();

    Serial.print("Motorul 2 a urcat timp de ");
    Serial.print(valoare);
    Serial.println(" unitati");

    // Flush the Serial buffer
    while (Serial.available() > 0) 
    {
      Serial.read();
    }

    // Ask if the user wants to continue
    Serial.println("Treceti la urmatorul pas? 1-DA, 0-NU");

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
        Serial.println("Input invalid. Va rog introduceti 1 sau 0.");
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
  ///RIDICA DIN APA GATA
  Serial.println("Ridicarea din apa gata");
  delay(1000);
  Serial.println("Obiectul are o greutate de ");
  Serial.print(greutate);
  Serial.print(" grame.");
  Serial.println("");
  float volum = (distance2-distance1) * 426.38;
  //float volum = 0.006409*426.38;

  Serial.println("Obiectul are un volum de ");
  delay(100);
  Serial.print(volum);
  delay(100);
  Serial.print(" cm^3.");
  delay(100);
  float densitate = greutate / volum ;
  Serial.println("");
  Serial.println("Astfel, obiectul are o densitate de ");
  Serial.print(densitate);
  Serial.print(" g/cm^3.");
  Serial.println("");
  delay(100);
  Serial.println("Densitatea plasticului PET este de 1.38-1.41 g/cm^3");
  Serial.println("Densitatea aluminiului este de 2.7 g/cm^3");
  Serial.println("Densitatea sticlei(sticla din recipiente) este de 2.4-2.6 g/cm^3");
  delay(100);
  if(densitate > 2.7)
    Serial.println("Astfel, recipientul masurat este din aluminiu !");
  else if(densitate > 1.9)
    Serial.println("Astfel, recipientul masurat este din sticla !");
  else
    Serial.println("Astfel, recipientul masurat este din plastic !");
  delay(99999);
}