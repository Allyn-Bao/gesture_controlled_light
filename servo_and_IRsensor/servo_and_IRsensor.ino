#include <Servo.h>

// Servo motor
Servo servoMotor;

// Pin numbers
int led = 8;
int potentiometer = A0;
int irSensor = 7;
int servoPin = 9;

// input
int potentioInput;
int irInput;

// output
int servoAngle;

void setup() {
  // init pins
  pinMode(led, OUTPUT);
  pinMode(potentiometer, INPUT);
  pinMode(irSensor, INPUT);
  servoMotor.attach(servoPin);

  Serial.begin(9600);
}

void loop() {
  // read potentiometer input
  potentioInput = analogRead(potentiometer);
  // read IR sensor
  irInput = digitalRead(irSensor);

  // led
  if (irInput == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  // servo motor
  // map(input, input_range_min, input_range_max, servo_angle_min, servo_angle_max)
  servoAngle = map(potentioInput, 0, 1023, 50, 150);
  servoMotor.write(servoAngle);

  Serial.println(servoAngle);

  delay(30);
}
