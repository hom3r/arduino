#include "LedControl.h"

const int FRAME = 80;
const int BUTTON = 2;

// DIN 4, CLK = 5, CS = 6, 1 matrix connected
LedControl matrix = LedControl(4, 5, 6, 1);

void drawRectangle(int size);
void wink(int duration);
void blink();

void setup() {
  Serial.begin(9600);

  //wake up the MAX72XX from power-saving mode
  matrix.shutdown(0, false);  // enable the matrix
  //set a medium brightness for the Leds
  matrix.setIntensity(0,8); 

  animation();
  animation();
  animation();

  Serial.println("Init complete");
}

void loop() {
  Serial.println("Looping...");

  drawFace();
  delay(2000);
  blink();
  delay(200);
  blink();
  delay(3000);

  wink(2000);
  delay(1000);
}

void animation() {
  // matrix.clearDisplay(0); 
  drawRectangle(1);
  delay(FRAME);
  drawRectangle(2);
  delay(FRAME);
  drawRectangle(3);
  delay(FRAME);
  drawRectangle(4);
  delay(FRAME);
  drawRectangle(3);
  delay(FRAME);
  drawRectangle(2);
  delay(FRAME);
  drawRectangle(1);
  delay(FRAME);
  drawRectangle(0);
  delay(FRAME);
}

void drawFace() {
  // matrix.clearDisplay(0); 
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00100100); 
  matrix.setRow(0,2,B00100100); 
  matrix.setRow(0,3,B00100100);
  matrix.setRow(0,4,B00000000); 
  matrix.setRow(0,5,B01000010); 
  matrix.setRow(0,6,B00111100); 
  matrix.setRow(0,7,B00000000); 
}

void blink() {
  drawFace();
  delay(FRAME);

  // half-closed eyes
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000000); 
  matrix.setRow(0,2,B00100100); 
  matrix.setRow(0,3,B00000000);

  delay(FRAME);

  // closed eyes
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000000); 
  matrix.setRow(0,2,B00000000); 
  matrix.setRow(0,3,B00000000);
  delay(FRAME);

  // half-closed eyes
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000000); 
  matrix.setRow(0,2,B00100100); 
  matrix.setRow(0,3,B00000000);

  delay(FRAME);

  drawFace();
  delay(FRAME);
}


void wink(int duration = FRAME) {
  drawFace();
  delay(FRAME);

  // half-closed eye
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000100); 
  matrix.setRow(0,2,B00100100); 
  matrix.setRow(0,3,B00000100);
  delay(FRAME);

  // closed eye
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000100); 
  matrix.setRow(0,2,B01100100); 
  matrix.setRow(0,3,B00000100);

  delay(duration);

  // half-closed eye
  matrix.setRow(0,0,B00000000);  
  matrix.setRow(0,1,B00000100); 
  matrix.setRow(0,2,B00100100); 
  matrix.setRow(0,3,B00000100);

  delay(FRAME);

  drawFace();
  delay(FRAME);
}

void drawRectangle(int size) {
  matrix.clearDisplay(0); 

  switch (size) {
    case 0:
      break;
    case 1:
      matrix.setRow(0,1,B00000000); 
      matrix.setRow(0,2,B00000000); 
      matrix.setRow(0,3,B00011000); 
      matrix.setRow(0,4,B00011000); 
      matrix.setRow(0,5,B00000000); 
      matrix.setRow(0,6,B00000000); 
      break;
    case 2:
      matrix.setRow(0,1,B00000000); 
      matrix.setRow(0,2,B00111100); 
      matrix.setRow(0,3,B00100100); 
      matrix.setRow(0,4,B00100100); 
      matrix.setRow(0,5,B00111100); 
      matrix.setRow(0,6,B00000000); 
      break;
    case 3:
      matrix.setRow(0,1,B01111110); 
      matrix.setRow(0,2,B01000010); 
      matrix.setRow(0,3,B01000010); 
      matrix.setRow(0,4,B01000010); 
      matrix.setRow(0,5,B01000010); 
      matrix.setRow(0,6,B01111110); 
      break;
    case 4:
      matrix.setRow(0,0,B11111111); 
      matrix.setRow(0,1,B10000001); 
      matrix.setRow(0,2,B10000001); 
      matrix.setRow(0,3,B10000001); 
      matrix.setRow(0,4,B10000001); 
      matrix.setRow(0,5,B10000001); 
      matrix.setRow(0,6,B10000001); 
      matrix.setRow(0,7,B11111111); 
      break;
    default:
      Serial.println("Unknown size: " + size);
      break;
  }  
}
