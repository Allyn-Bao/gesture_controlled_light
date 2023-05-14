int ledPin = 9;
int ledPin2 = 2;
int buttonPin = 8;
int potentiometerPin = A0;

int MAX_BRIGHTNESS = 225;

int brightness = 0;
int fadeAmount = 5;
int direction = 1;

int potentiometerReading;
bool buttonState; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // declare pin 9 to be an output
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(potentiometerPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  /* button */
  // read button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }

  /* analog leds */
  // set the brightness of LED
  analogWrite(ledPin, brightness);

  // adjust brightness
  brightness += direction * fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    direction *= -1;
  }


  /* potentiometer */
  potentiometerReading = analogRead(potentiometerPin);

  Serial.println(potentiometerReading);

  delay(30);

}
