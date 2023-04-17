#ifndef Control_h
#define Control_h

#include <Arduino.h>

class Control
{
private:
    uint8_t outputPinOne_;
    uint8_t outputPinTwo_;
    unsigned long oldTime_;
    unsigned long newTime_;
    unsigned long randomTime_;
    const uint8_t OFF_SPEED = 0;
    const uint8_t SLOW_SPEED = 30;
    const uint8_t ON_SPEED = 255;
    bool driveBackwards = false;
    uint8_t actualSpeed;

public:
    // Constructor to set output pins and initialize variables
    Control(uint8_t outputPinOne, uint8_t outputTwo);

    // Method to set the motor speed and direction
    void setSpeed(uint8_t param, bool rndParam, bool rvrsParam);

    // Method to get the current motor speed
    uint8_t getSpeed();

    // Method to get the current motor direction
    bool getDirection();
};

#endif
