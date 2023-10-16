#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>

class Encoder
{
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

    // debouncer Variables
    uint32_t interruptTime_;
    uint32_t lastInterruptTime_;
    uint8_t debounceTime_;

    // Flags for encoder behavior
    bool randomONencoder_;
    bool reverseONencoder_;
    bool speedSelectState_;

public:
    // Constructor
    Encoder(uint8_t a_inputPinA, uint8_t a_inputPinB, uint8_t a_buttonPin);

    // Interrupt handlers
    void interruptA();
    void interruptB();
    void interruptBTN();

    // Getters for encoder states
    uint8_t getMenuPosition();
    bool getRandomState();
    bool getReverseState();
    uint8_t getSpeedPercentage();
    uint8_t getSpeed();
};

#endif