#include <Arduino_LSM9DS1.h>

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"



int IR_pin_1 = 2;
int IR_pin_2 = 4;
int IR_pin_3 = 7;
int IR_pin_4 = 8;

int LED_pin_1 = 9;
int LED_pin_2 = 10;
int LED_pin_3 = 11;

int LED_brightness = 0;

// IR inputs
int IR_input_1;
int IR_input_2;
int IR_input_3;
int IR_input_4;

// Saves IR input status (HIGH or LOW) each loop
int input[4];

int input_old[4];

// time elapsed when each IR sensor is triggered after the first
int IR_triggered_time[4];

int time_first_triggered_IR;

// true if any IR sensor is triggered within the time inverval TIME_EXPIRATION
bool triggered = false;

int current_time = 0;

int TIME_EXPIRATION = 1000;


int get_IR_time(int IR_new, int& IR_old, int& current_time) {
    if (IR_new == LOW && IR_old == HIGH) {
        IR_old = IR_new;
        return current_time;
    }
    IR_old = IR_new;
    return -1;
}

void reset() {
  current_time = 0;
  triggered = false;
  time_first_triggered_IR = -1;
  for (int i=0; i<4; i++) {
    input[i] = LOW;
    input_old[i] = HIGH;
    IR_triggered_time[i] = -1;
  }
}

bool check_triggered() {
  if (!triggered) {
    for (int i = 0; i < 4; i++) {
      if (input[i] == LOW) {
        return true;
      }
    }
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // set up pins
  pinMode(IR_pin_1, INPUT);
  pinMode(IR_pin_2, INPUT);
  pinMode(IR_pin_3, INPUT);
  pinMode(IR_pin_4, INPUT);

  pinMode(LED_pin_1, OUTPUT);
  pinMode(LED_pin_2, OUTPUT);
  pinMode(LED_pin_3, OUTPUT);

  reset();
}

void loop() {
  // put your main code here, to run repeatedly:
  input[0] = digitalRead(IR_pin_1);
  input[1] = digitalRead(IR_pin_2);
  input[2] = digitalRead(IR_pin_3);
  input[3] = digitalRead(IR_pin_4);

  if (check_triggered()) {
    // reset
    reset(); 
    triggered = true;
    // Serial.println("new round:");
  } 
  if (triggered) {
    for (int i=0; i < 4; i++) {
      int new_time = get_IR_time(input[i], input_old[i], current_time);
      if (new_time != -1) {
        IR_triggered_time[i] = new_time;
      }
    }
  }
  if (triggered && current_time >= TIME_EXPIRATION) {
    Serial.print(IR_triggered_time[0]);
    Serial.print(", ");
    Serial.print(IR_triggered_time[1]);
    Serial.print(", ");
    Serial.print(IR_triggered_time[2]);
    Serial.print(", ");
    Serial.print(IR_triggered_time[3]);
    Serial.print("\n");

    reset();
    
  }
  current_time ++;
  delay(1);
  
}
