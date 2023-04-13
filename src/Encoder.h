#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>

class Encoder {
private:

  // Pin Numbers
  uint8_t inputPinA_;
  uint8_t inputPinB_;
  uint8_t buttonPin_;

  // Pin states (if HIGH or LOW)
  bool pinAState_;
  bool pinBState_;

  // counter for menu
  uint8_t menuPos_;
  uint8_t encoderSpeed_;
  uint8_t speedPercentage_;

  uint8_t maxMenuItems_;
  //volatile uint8_t lastReportedEncoderPos_;
  
  // debouncer Variables
  uint32_t interruptTime_;
  uint32_t lastInterruptTime_;
  uint8_t debounceTime_;

  bool randomONencoder_;
  bool reverseONencoder_;
  bool speedSelectState_;
  
public:
  Encoder(uint8_t a_inputPinA, uint8_t a_inputPinB, uint8_t a_buttonPin);
  void interruptA();
  void interruptB();
  void interruptBTN();
  uint8_t getMenuPosition();
  bool getRandomState();
  bool getReverseState();
  uint8_t getSpeedPercentage();
  uint8_t getSpeed();
};

#endif