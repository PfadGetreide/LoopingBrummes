#ifndef Control_h
#define Control_h

#include <Arduino.h>

class Control
{
private:
    uint8_t outputPinOne_; // Pin number of the first output pin
    uint8_t outputPinTwo_; // Pin number of the second output pin
    unsigned long oldTime_; // Time of the last change in motor direction
    unsigned long newTime_; // Time of the current change in motor direction
    unsigned long randomTime_; // Time interval for random change in motor direction
    const uint8_t OFF_SPEED = 0; // Constant value for motor speed when it is turned off
    const uint8_t SLOW_SPEED = 30; // Constant value for low motor speed
    const uint8_t ON_SPEED = 255; // Constant value for full motor speed
    bool driveBackwards = false; // Current direction of motor rotation
    uint8_t actualSpeed; // Current speed of the motor

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
