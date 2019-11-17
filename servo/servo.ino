//www.elegoo.com
//2018.12.19
#include <Servo.h>
#include <Keypad.h>

// servo setup
Servo upper_servo;
Servo lower_servo;
const int lower_servo_pin = 53; // digital pin connected to lower servo
const int upper_servo_pin = 49; // digital pin connected to upper servo

// joystick setup
const int joystick_switch_pin = 45; // digital pin connected to switch output
const int joystick_x_pin = 0; // analog pin connected to X output
const int joystick_y_pin = 1; // analog pin connected to Y output


void setup(){

  // set up Serial
  Serial.begin(9600);

  // attach servos
  lower_servo.attach(lower_servo_pin);
  upper_servo.attach(upper_servo_pin);

  // setup joystick switch
  pinMode(joystick_switch_pin, INPUT);
  digitalWrite(joystick_switch_pin, HIGH);
  Serial.begin(9600);

  // be polite
  WelcomeMessage();

  // ServoPositionPrompt();
}

void loop(){

  Serial.print("Switch:  ");
  Serial.print(digitalRead(joystick_switch_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(joystick_x_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(joystick_y_pin));
  Serial.print("\n\n");
  delay(500);

}

bool ValidServoPosition(int potential_position) {
  // a valid servo position is between 0 and 180
  if (potential_position <= 180 && potential_position >= 0) {
    return true;
  } else {
    return false;
  }
}

void WelcomeMessage() {
  Serial.println("-------------------------------");
  Serial.println("----------- WELCOME -----------");
  Serial.println("-------------------------------");
  Serial.println("");
  Serial.println("");

}
