/*
Bluetooth car

The Dabble application and library is used for this project.
See more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

const byte PIN_BLUE = 4;
const byte PIN_RED = 2;

const byte PIN_MOTOR_A1 = 12;
const byte PIN_MOTOR_A2 = 13;
const byte PIN_MOTOR_B1 = 14;
const byte PIN_MOTOR_B2 = 27;

const byte SPEED = 100;

void setup() {
  Serial.begin(115200);           // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("Auticko");        //set bluetooth name of your device
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_MOTOR_A1, OUTPUT);
  pinMode(PIN_MOTOR_A2, OUTPUT);
  pinMode(PIN_MOTOR_B1, OUTPUT);
  pinMode(PIN_MOTOR_B2, OUTPUT);
  
  // turn all pins OFF
  digitalWrite(PIN_BLUE, LOW);
  digitalWrite(PIN_RED, LOW);
  halt();

  // turn on the build-in LED (on PIN 5)
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
}


void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

  if (GamePad.isUpPressed())
  {
    Serial.print("KeyPressed: ");
    Serial.println("Up");
    digitalWrite(PIN_BLUE, HIGH);
    runForward();
    delay(100);
    digitalWrite(PIN_BLUE, LOW);
    halt();
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("KeyPressed: ");
    Serial.println("Down");
    digitalWrite(PIN_RED, HIGH);
    runBackward();
    delay(100);
    digitalWrite(PIN_RED, LOW);
    halt();
  }
  
  if (GamePad.isLeftPressed())
  {
    turnLeft();
    delay(100);
    halt();
  }

  
  if (GamePad.isRightPressed())
  {
    turnRight();
    delay(100);
    halt();
  }
}


void turnRight() {
  digitalWrite(PIN_MOTOR_A1, SPEED);
  digitalWrite(PIN_MOTOR_A2, LOW);
  digitalWrite(PIN_MOTOR_B1, LOW);
  digitalWrite(PIN_MOTOR_B2, SPEED);
}

void turnLeft() {
  digitalWrite(PIN_MOTOR_A1, LOW);
  digitalWrite(PIN_MOTOR_A2, SPEED);
  digitalWrite(PIN_MOTOR_B1, SPEED);
  digitalWrite(PIN_MOTOR_B2, LOW);
}

void runForward() {
  digitalWrite(PIN_MOTOR_A1, SPEED);
  digitalWrite(PIN_MOTOR_A2, LOW);
  digitalWrite(PIN_MOTOR_B1, SPEED);
  digitalWrite(PIN_MOTOR_B2, LOW);
}
void runBackward() {
  digitalWrite(PIN_MOTOR_A1, LOW);
  digitalWrite(PIN_MOTOR_A2, SPEED);
  digitalWrite(PIN_MOTOR_B1, LOW);
  digitalWrite(PIN_MOTOR_B2, SPEED);
}

void halt() {
  digitalWrite(PIN_MOTOR_A1, LOW);
  digitalWrite(PIN_MOTOR_A2, LOW);
  digitalWrite(PIN_MOTOR_B1, LOW);
  digitalWrite(PIN_MOTOR_B2, LOW);
}
