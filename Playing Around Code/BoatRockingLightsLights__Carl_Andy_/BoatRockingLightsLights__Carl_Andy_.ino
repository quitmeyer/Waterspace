// I2C interface by default
//
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

 #define DEBUG 1 in SparkFunLSM303C.h turns on debugging statements.
// Redefine to 0 to turn them off.

LSM303C myIMU;


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const int numReadings = 50;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int readings2[numReadings];      // the readings from the analog input
int readIndex2 = 0;              // the index of the current reading
int total2 = 0;                  // the running total
int readings3[numReadings];      // the readings from the analog input
int readIndex3 = 0;              // the index of the current reading
int total3 = 0;                  // the running total

void setup()
{
  Serial.begin(9600);
  if (myIMU.begin() != IMU_SUCCESS)
  {
    Serial.println("Failed setup.");
    while(1);
  }
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}





void loop()
{
  //Get all parameters
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  Serial.println(myIMU.readAccelX(), 4);
  Serial.print(" Y = ");
  Serial.println(myIMU.readAccelY(), 4);
  Serial.print(" Z = ");
  Serial.println(myIMU.readAccelZ(), 4);


    //colorWipe(strip.Color(myIMU.readAccelX(), myIMU.readAccelY(), myIMU.readAccelZ()), 0); // Red
//drawLine(150,0,strip.Color(myIMU.readAccelX(), myIMU.readAccelY(), myIMU.readAccelZ()));



int r= myIMU.readAccelX();
r = map(r,0,1100,0,255);
r = constrain(r,20,255);
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = r;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
r = total / numReadings;

int g= myIMU.readAccelY();
g = map(g,0,1100,0,255);
g = constrain(g,20,255);
  // subtract the last reading:
  total2 = total2 - readings2[readIndex2];
  // read from the sensor:
  readings2[readIndex2] = g;
  // add the reading to the total:
  total2 = total2 + readings2[readIndex2];
  // advance to the next position in the array:
  readIndex2 = readIndex2 + 1;

  // if we're at the end of the array...
  if (readIndex2 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex2 = 0;
  }
g = total2 / numReadings;

int b= myIMU.readAccelZ();
b = map(b,0,1100,0,255);
b = constrain(b,20,255);
  // subtract the last reading:
  total3 = total3 - readings3[readIndex3];
  // read from the sensor:
  readings3[readIndex3] = b;
  // add the reading to the total:
  total3 = total3 + readings3[readIndex3];
  // advance to the next position in the array:
  readIndex3 = readIndex3 + 1;

  // if we're at the end of the array...
  if (readIndex3 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex3 = 0;
  }
b = total / numReadings;

 

 for(uint16_t i=0; i<strip.numPixels(); i++) {
  
    strip.setPixelColor(i, strip.Color(r,g,b));
     // strip.setPixelColor(i, strip.Color(255,0,0));

  }
   Serial.print(" R = ");
  Serial.println(r);
   Serial.print(" G = ");
  Serial.println(b);
   Serial.print(" B = ");
  Serial.println(g);
      strip.show();
  
//  // Not supported by hardware, so will return NAN
//  Serial.print("\nGyroscope:\n");
//  Serial.print(" X = ");
//  Serial.println(myIMU.readGyroX(), 4);
//  Serial.print(" Y = ");
//  Serial.println(myIMU.readGyroY(), 4);
//  Serial.print(" Z = ");
//  Serial.println(myIMU.readGyroZ(), 4);
//
//  Serial.print("\nMagnetometer:\n");
//  Serial.print(" X = ");
//  Serial.println(myIMU.readMagX(), 4);
//  Serial.print(" Y = ");
//  Serial.println(myIMU.readMagY(), 4);
//  Serial.print(" Z = ");
//  Serial.println(myIMU.readMagZ(), 4);
//
//  Serial.print("\nThermometer:\n");
//  Serial.print(" Degrees C = ");
//  Serial.println(myIMU.readTempC(), 4);
//  Serial.print(" Degrees F = ");
//  Serial.println(myIMU.readTempF(), 4);
//  
//  delay(1000);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Used to draw a line between two points of a given color
void drawLine(uint8_t from, uint8_t to, uint32_t c) {
  uint8_t fromTemp;
  if (from > to) {
    fromTemp = from;
    from = to;
    to = fromTemp;
  }
  for(int i=from; i<=to; i++){
    strip.setPixelColor(i, c);
  }
}
