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
    if (keypad_input == '#') {

      // prefeace the pringing of keypad message
      Serial.println("");
      Serial.print("you typed: ");

      // loop through the relevant portion of keypad_message
      for (int i; i < message_length; i++) {
        Serial.print(keypad_message[i]);
      }
      Serial.println("");

      // reset the message length
      message_length = 0;

    } else {

      // add keyboard input to keyboard message
      keypad_message[message_length] = keypad_input;
      message_length++;

      // print this keyboard input
      Serial.print(keypad_input);
    }
  }

}
