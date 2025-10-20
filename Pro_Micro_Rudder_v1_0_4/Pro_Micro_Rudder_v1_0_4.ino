// Custom Rudder/Multi-Axis Joystick Firmware
// VERSION: 1.0.4 (Final with -127 to 127 mapping)

//==============================================================================
// COMPILER OPTIONS
//==============================================================================
// Uncomment the line below to enable Serial Debug Output.

//#define DEBUG

#include "Joystick.h"

// //==============================================================================
// // JOYSTICK CONFIGURATION
// //==============================================================================
// // Define a joystick with Z, Rz, Rudder, and Throttle axes enabled.
// // Brakes will be mapped to the Rudder and Throttle sliders.
// Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
//   8, 0,                  // 8 Buttons, 0 Hat Switches
//   false, false, true,    // X, Y, Z Axis (Main Rudder is on Z)
//   false, false, true,    // Rx, Ry, Rz (Rx/Ry are OFF, Aux1 is on Rz)
//   true, true,            // Rudder, Throttle (These are for the brakes)
//   false, false, false);  // Accelerator, Brake, Steering

//==============================================================================
// PIN DEFINITIONS (Digital Buttons)
//==============================================================================
const int BUTTON_PINS[] = { 4, 5, 6, 7, 8, 14, 15, 16 };
const int NUM_BUTTONS = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);

//==============================================================================
// PIN DEFINITIONS (Analog Axes)
//==============================================================================
const int AXIS_RUDDER_PIN        = A0;
const int AXIS_LEFT_BRAKE_PIN  = A1;
const int AXIS_RIGHT_BRAKE_PIN = A2;
const int AXIS_AUX1_PIN          = A3;
// Pins A9 and A10 are no longer used in this configuration but are kept for reference
// const int AXIS_AUX2_PIN          = A9;
// const int AXIS_AUX3_PIN          = A10;

//==============================================================================
// FIRMWARE VERSION
//==============================================================================
const char* SOFTWARE_VERSION = "1.0.4";

#ifdef DEBUG
  // Variables and function prototypes for the debug menu
  bool inMenu = false;
  unsigned long menuButtonPressTime = 0;
  const long DEBOUNCE_DELAY = 50;
  const long LONG_PRESS_THRESHOLD = 500;
  void handleSerialMenu();
  void printMenu();
#endif

//==============================================================================
// SETUP FUNCTION
//==============================================================================
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial && millis() < 3000); // Wait 3s for serial
    Serial.println("------------------------------------");
    Serial.print("Starting Controller Firmware v");
    Serial.println(SOFTWARE_VERSION);
    Serial.println("------------------------------------");
    Serial.println("Press and hold Button 1 to enter menu.");
  #else
    Joystick.begin(false); // Initialize the Joystick for manual sendState()

    // Set the desired logical range for each active axis to -127 to 127
    // Joystick.setZAxisRange(-127, 127);     // For the main rudder
    // Joystick.setRudderRange(-127, 127);    // For the left brake slider
    // Joystick.setThrottleRange(-127, 127);  // For the right brake slider
 
 //   Joystick.setRzAxisRange(-127, 127);    // For Aux1
  #endif

  // Configure all button pins with an internal pull-up resistor
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
}

//==============================================================================
// MAIN LOOP FUNCTION
//==============================================================================
void loop() {
  #ifdef DEBUG
    handleSerialMenu();
    if (inMenu) {
      delay(100);
      return;
    }
    // Print raw analog values for debugging
    Serial.print("Rudder: ");   Serial.print(analogRead(AXIS_RUDDER_PIN));
    Serial.print(" | L.Brake: ");  Serial.print(analogRead(AXIS_LEFT_BRAKE_PIN));
    Serial.print(" | R.Brake: ");  Serial.print(analogRead(AXIS_RIGHT_BRAKE_PIN));
    Serial.print(" | Aux1: ");     Serial.println(analogRead(AXIS_AUX1_PIN));
    delay(50);
  #else
    // --- Normal Joystick Operation ---

    // Read button states
    for (int i = 0; i < NUM_BUTTONS; i++) {
      Joystick.setButton(i, !digitalRead(BUTTON_PINS[i]));
    }
    
    // Read analog inputs, map them to the -127 to 127 range, and set the axis values
    Joystick.setZAxis(map(analogRead(AXIS_RUDDER_PIN), 0, 1023, -127, 127));
    Joystick.setRudder(map(analogRead(AXIS_LEFT_BRAKE_PIN), 503, 1023, 0, 255));
    Joystick.setThrottle(map(analogRead(AXIS_RIGHT_BRAKE_PIN), 93, 600 , 0, 255));
   // Joystick.setRzAxis(map(analogRead(AXIS_AUX1_PIN), 0, 1023, -127, 127));

    // Send the collective state of all controls to the computer
    Joystick.sendState();
    delay(5); // Small delay for a stable update rate (~200 Hz)
  #endif
}

#ifdef DEBUG
//==============================================================================
// DEBUG MENU FUNCTIONS (Only compiled if DEBUG is defined)
//==============================================================================
void handleSerialMenu() {
  bool button1Pressed = !digitalRead(BUTTON_PINS[0]);
  if (button1Pressed && menuButtonPressTime == 0) {
    menuButtonPressTime = millis();
  } else if (button1Pressed && (millis() - menuButtonPressTime >= LONG_PRESS_THRESHOLD) && !inMenu) {
    inMenu = true;
    Serial.println("\n------------------------------------");
    Serial.println("  *** Entering Configuration Menu ***");
    printMenu();
    menuButtonPressTime = 0;
  } else if (!button1Pressed && menuButtonPressTime != 0) {
    if (inMenu) {
      inMenu = false;
      Serial.println("\n  *** Exiting Configuration Menu ***");
    }
    menuButtonPressTime = 0;
  }
  if (inMenu && Serial.available()) {
    char command = Serial.read();
    if (command == 'h' || command == '?') {
      printMenu();
    } else {
      Serial.println("  Invalid command.");
    }
  }
}

void printMenu() {
  Serial.println("\n--- Menu Options ---");
  Serial.println("  h: Show this menu");
  Serial.println("--------------------");
  Serial.println("Press Button 1 to exit.");
}
#endif