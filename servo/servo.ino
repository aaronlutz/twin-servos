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

// max joystick positions
int js_max = 1023;

// max servo positions
int sv_max = 180;

// raw joystick readings
int js_raw_x;
int js_raw_y;
// mapped joystick readings
int js_x;
int js_y;
int js_s;
// previous mapped joystick readings
int js_prev_x = 0;
int js_prev_y = 0;
int js_prev_s;


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

  // raw reading from joystick
  js_raw_x = analogRead(joystick_x_pin);
  js_raw_y = analogRead(joystick_y_pin);

  // mapped readings from joystick
  js_x = map(js_raw_x, 0, js_max, 0, sv_max);
  js_y = map(js_raw_y, 0, js_max, 0, sv_max);

  // button
  js_s = digitalRead(joystick_switch_pin);

  int suff_x_delta = SufficientDelta(js_prev_x, 2, js_x);
  int suff_y_delta = SufficientDelta(js_prev_y, 2, js_y);

  // if this reading is different than the previous
  if (suff_x_delta || suff_y_delta) {
    // print it
    PrintJoystick(js_x, js_y, js_s, suff_x_delta, suff_y_delta);
    lower_servo.write(js_y);
    upper_servo.write(js_x);
  }

  delay(50);

  // previous joystick readings
  js_prev_s = js_s;
  js_prev_x = js_x;
  js_prev_y = js_y;
}

bool ValidServoPosition(int potential_position) {
  // a valid servo position is between 0 and 180
  if (potential_position <= 180 && potential_position >= 0) {
    return true;
  } else {
    return false;
  }
}

void PrintJoystick(int x, int y, int s, bool bool_1, bool bool_2) {
  Serial.print("(X, Y, S) (Suff X, Suff Y):  (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(s);
  Serial.print(") ... (");
  Serial.print(bool_1);
  Serial.print(", ");
  Serial.print(bool_2);
  Serial.print(")\n\n");
}

bool SufficientDelta(int base, int delta, int candidate) {
  int this_delta = abs(candidate - base);
  return (this_delta >= delta);
}

void WelcomeMessage() {
  Serial.println("-------------------------------");
  Serial.println("----------- WELCOME -----------");
  Serial.println("-------------------------------");
  Serial.println("");
  Serial.println("");

}
