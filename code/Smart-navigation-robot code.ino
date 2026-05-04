#include <Servo.h>

#define trigPin 9
#define echoPin 10

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define servoPin 6

Servo myServo;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(90); // center

  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  if (distance > 25) {
    moveForward();
  } else {
    stopMotors();
    delay(300);

    int rightDist = scanRight();
    int leftDist = scanLeft();

    if (rightDist > leftDist) {
      turnRight();
      delay(500);
    } else {
      turnLeft();
      delay(500);
    }
  }
}

// Distance Function
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

// Scanning
int scanRight() {
  myServo.write(30);
  delay(500);
  int d = getDistance();
  myServo.write(90);
  return d;
}

int scanLeft() {
  myServo.write(150);
  delay(500);
  int d = getDistance();
  myServo.write(90);
  return d;
}

// Movement
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}