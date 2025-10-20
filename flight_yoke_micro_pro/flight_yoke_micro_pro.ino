// Basic Flight Yoke Sketch for Arduino Pro Micro
// Reads four analog inputs for Roll, Pitch, Thrust, and Flaps.
// Includes a DEBUG flag to output raw values to the Serial Plotter.

//================================================================
// COMPILER OPTIONS
//================================================================
// Uncomment the line below to enable Serial Plotter debug output
// instead of acting as a Joystick.
//#define DEBUG

#include "Joystick.h"

// Define the analog pins for each axis
const int PIN_PITCH   = A0; // Y-Axis
const int PIN_ROLL    = A1; // X-Axis
const int PIN_THRUST  = A2; // Throttle
const int PIN_FLAPS   = A3; // Mapped to Rudder axis

void setup() {
  // Always start Serial communication for debugging
  Serial.begin(115200);
  
  #ifndef DEBUG
    // Only initialize the Joystick if we are NOT in debug mode
    Joystick.begin(false);
  #endif

  // Set the pin modes for the analog inputs
  pinMode(PIN_PITCH, INPUT);
  pinMode(PIN_ROLL, INPUT);
  pinMode(PIN_THRUST, INPUT);
  pinMode(PIN_FLAPS, INPUT);
}

void loop() {
  // --- Read Raw Analog Values (0-1023) ---
  int pitchValue = analogRead(PIN_PITCH);
  int rollValue = analogRead(PIN_ROLL);
  int thrustValue = analogRead(PIN_THRUST);
  int flapsValue = analogRead(PIN_FLAPS);

  #ifdef DEBUG
    // --- DEBUG OUTPUT ---
    // Print the raw values in a comma-separated format for the Serial Plotter
    Serial.print(pitchValue);
    Serial.print(",");
    Serial.print(rollValue);
    Serial.print(",");
    Serial.print(thrustValue);
    Serial.print(",");
    Serial.println(flapsValue); // Use println on the last value

  #else
    // --- NORMAL JOYSTICK OUTPUT ---
    // Map Pitch and Roll to the X and Y axes (-127 to 127)
    int xAxis = map(rollValue, 0, 1023, -127, 127);
    int yAxis = map(pitchValue, 0, 1023, -127, 127);

    // Map Thrust and Flaps to the Throttle and Rudder axes (0 to 255)
    int throttle = map(thrustValue, 0, 1023, 0, 255);
    int rudder = map(flapsValue, 0, 1023, 0, 255);

    // Set Joystick State
    Joystick.setXAxis(xAxis);
    Joystick.setYAxis(yAxis);
    Joystick.setThrottle(throttle);
    Joystick.setRudder(rudder);

    // Send Update to PC
    Joystick.sendState();
  #endif

  // A small delay to keep a stable update rate
  delay(10);
}