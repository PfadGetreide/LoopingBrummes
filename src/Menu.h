#ifndef Menu_h
#define Menu_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Encoder.h" 


class Menu {
private:
  Encoder* menuEncoder_;
  Adafruit_SSD1306* menuDisplay_;
  //uint8_t DISP_cols;
  //uint8_t DISP_rows;
  uint8_t menuPosition_;
  uint8_t speed_;
  bool randomON_;
  bool reverseON_;

  
public:
  Menu(Encoder* a_encoder, Adafruit_SSD1306* a_lcd);
  void displayMenu();
};

#endif