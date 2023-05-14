
// power level signal consist of 4 leds
int led0 = 7;
int led1 = 8;
int led2 = 12;
int led3 = 13;

// analog led to display continueous power level
int ledAnalog = 3;

// input
int potentiometer = A0;
int inputReadings;


void led_control(int readings) {
    // level 0
    if (readings > 200) {
      digitalWrite(led0, HIGH);
      // level 1
      if (readings > 400) {
        digitalWrite(led1, HIGH);
        // level 2
        if (readings > 600) {
          digitalWrite(led2, HIGH);
          // level 3
          if (readings > 800) {
            digitalWrite(led3, HIGH);
          } else {
            digitalWrite(led3, LOW);
          }
        } else {
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
        }
      } else {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
      }
    } else {
      digitalWrite(led0, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
}


void setup() {
  // set pin model of all i/o
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(ledAnalog, OUTPUT);

  pinMode(potentiometer, INPUT);
}

void loop() {
  // get input readings
  inputReadings = analogRead(potentiometer);

  // turn on led according to input level
  led_control(inputReadings);

  // analog led
  analogWrite(ledAnalog, inputReadings / 5);
  
  delay(30);
}
