//www.elegoo.com
//2018.12.19
#include <Servo.h>
#include <Keypad.h>

// servo setup
Servo myservo;

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

char keypad_input[1];

// hold keypad input
char keypad_message[1600];
int message_length = 0;

void setup(){
  Serial.begin(9600);
  myservo.attach(9);

}
void loop(){
  // myservo.write(0);// move servos to center position -> 90°
  // delay(1000);

  // myservo.write(30);
  // delay(1000);
  //
  // myservo.write(60);
  // delay(1000);
  //
  // myservo.write(90);
  // delay(1000);
  //
  // myservo.write(120);
  // delay(1000);
  //
  // myservo.write(150);
  // delay(1000);

  // myservo.write(180);
  // delay(1000);

  char keypad_input = customKeypad.getKey();

  if (keypad_input){
    KeypadLog(keypad_input);
    }


}

void KeypadLog(char _keypad_input) {
  if (_keypad_input == '#') {
    // display contents of keypad_message
    // // prefix printed log
    // Serial.println("");
    // Serial.print("you typed: ");
    //
    // // loop through the relevant portion of keypad_message
    // for (int i; i < message_length; i++) {
    //   Serial.print(keypad_message[i]);
    // }
    //
    // // padding
    // Serial.println("");
    // Serial.println("");
    KeypadLogDisplay();

    // reset the message length
    KeypadLogReset();

  } else {
    KeypadLogAppend(_keypad_input);

    // print this keyboard input
    Serial.print(_keypad_input);
  }
}

void KeypadLogReset() {
  // flush keypad_messages
  for (int i = 0; i < 1600; i++) {
    keypad_message[i] = NULL;
  }
  // reset the position control varaible
  message_length = 0;
}

void KeypadLogAppend(char _append_me) {
  // slot input and increment position control variable
  keypad_message[message_length] = _append_me;
  message_length++;
}

void KeypadLogDisplay() {
  // prefix printed log
  Serial.println("");
  Serial.print("you typed: ");

  // loop through the relevant portion of keypad_message
  for (int i; i < message_length; i++) {
    Serial.print(keypad_message[i]);
  }

  // padding
  Serial.println("");
  Serial.println("");
}
