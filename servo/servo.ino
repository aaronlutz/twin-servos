//www.elegoo.com
//2018.12.19
#include <Servo.h>
#include <Keypad.h>

// servo setup
Servo upper_servo;
Servo lower_servo;
Servo focus_servo;

// numberpad setup
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// char keypad_input[1];
int keypad_input;
int keypad_integer;


bool valid_servo_selected = false;
bool valid_servo_pos_selected = false;

// hold keypad input
// char keypad_message[1600];
String keypad_message = "";
// int message_length = 0;

void setup(){
  Serial.begin(9600);
  lower_servo.attach(53);
  upper_servo.attach(49);

  // be polite
  WelcomeMessage();

  // ServoPositionPrompt();
}

void loop(){

  valid_servo_selected = false;
  valid_servo_pos_selected = false;
  Servo focus_servo;
  int new_position;

  focus_servo = SelectServo();
  new_position = SelectServoPosition();
  focus_servo.write(keypad_integer);

}

void KeypadLogAppendDigit(char _append_me) {
  if (isDigit(_append_me)) {
    // convert the incoming byte to a char and add it to the string:
    keypad_message += (char)_append_me;
  }
}

void PromptResponseAppend(char append_to_prompt) {
  // append input to current line
  if (append_to_prompt != '#') {
    Serial.print(append_to_prompt);
  }
}

bool ValidServoPosition(int potential_position) {
  // a valid servo position is between 0 and 180
  if (potential_position <= 180 && potential_position >= 0) {
    return true;
  } else {
    return false;
  }
}

int SelectServoPosition() {
  Serial.println("-- Select a Position ----------");
  Serial.println("-- min: 0");
  Serial.println("-- max: 180");
  Serial.println("");
  Serial.print("-- Your Selection: ");
  valid_servo_pos_selected = false;

  while (valid_servo_pos_selected == false) {
    char keypad_number = customKeypad.getKey();
    if (keypad_number) {
      if (keypad_number == '#') {

        keypad_integer = keypad_message.toInt();

        if (ValidServoPosition(keypad_integer)) {
          Serial.println(keypad_integer);
          Serial.println("");
          keypad_message = "";
          valid_servo_pos_selected = true;
        } else {
          // invalid Selection
          Serial.print("INVALID (");
          Serial.print(keypad_integer);
          Serial.println(")");
          Serial.print("-- Your Selection: ");
          keypad_message = "";
        };
      } else {
        KeypadLogAppendDigit(keypad_number);
      }
    }
  }
}

Servo SelectServo() {
  // promput user to enter new servo position
  Serial.println("-- Select a Servo -------------");
  Serial.println("-- A: lower_servo");
  Serial.println("-- B: upper_servo");
  Serial.println("");
  Serial.print("-- Your Selection: ");
  char keypad_letter;
  valid_servo_selected = false;

  while (valid_servo_selected == false) {
    keypad_letter = customKeypad.getKey();
    if (keypad_letter) {
      if (keypad_letter == 'A' || keypad_letter == 'B') {
        // valid servo selected
        Serial.println(keypad_letter);
        Serial.println("");

        valid_servo_selected = true;

        if (keypad_letter == 'A') {
          return lower_servo;
        } else if (keypad_letter == 'B') {
          return upper_servo;
        }

      } else {
        // invalid Selection
        Serial.println("INVALID");
        Serial.print("-- Your Selection: ");
      }
    }
  }
}

void ServoPositionPrompt() {
  // promput user to enter new servo position
  Serial.println("");
  Serial.println("");
  Serial.print("Enter New Servo Position: ");
}

void WelcomeMessage() {
  Serial.println("-------------------------------");
  Serial.println("----------- WELCOME -----------");
  Serial.println("-------------------------------");
  Serial.println("");
  Serial.println("");

}
