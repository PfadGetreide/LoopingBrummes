#ifndef Menu_h
#define Menu_h

// Include the required libraries.
#include "Encoder.h"             // Library for handling rotary encoders.
#include <Adafruit_GFX.h>        // Graphics library for displays.
#include <Adafruit_SSD1306.h>    // Library for driving OLED displays.
#include <Arduino.h>             // Arduino core library.
#include <SPI.h>                 // SPI communication library.
#include <Wire.h>                // I2C communication library.

// Declare the Menu class.
class Menu {
  private:
    // Declare private member variables.
    Encoder* menuEncoder_;       // Pointer to a rotary encoder object.
    Adafruit_SSD1306* menuDisplay_;  // Pointer to an OLED display object.
    uint8_t menuPosition_;       // Current position of the menu cursor.
    uint8_t speed_;              // Current speed setting.
    bool randomON_;              // Whether random mode is on.
    bool reverseON_;             // Whether reverse mode is on.
  
  public:
    // Declare public methods.
    // Constructor. Takes pointers to an Encoder and Adafruit_SSD1306 object.
    Menu(Encoder* a_encoder, Adafruit_SSD1306* a_lcd);
    // Displays the current menu on the OLED display.
    void displayMenu();
};

// End the include guard.
#endif
