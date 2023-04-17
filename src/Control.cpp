#include "Control.h"

// Constructor, sets the output pins for the motor control and initializes
// variables
Control::Control(uint8_t a_outputPinOne, uint8_t a_outputTwo)
{
    outputPinOne_ = a_outputPinOne;
    outputPinTwo_ = a_outputTwo;
    pinMode(outputPinOne_, OUTPUT);
    pinMode(outputPinTwo_, OUTPUT);
    oldTime_ = 0;
    newTime_ = 0;
    randomTime_ = random(500, 5000);
    actualSpeed = 0;
}

// Sets the speed and direction of the motor
// maxSpeed: the maximum speed of the motor
// rndParam: if true, randomly changes speed and direction of the motor at
// random intervals rvrsParam: if true, sets the motor direction to reverse
void Control::setSpeed(uint8_t maxSpeed, bool rndParam, bool rvrsParam)
{

    newTime_ = millis();

    // Random mode
    if (rndParam)
    {

        // Check if it's time to change speed and direction
        if ((newTime_ - oldTime_) >= randomTime_)
        {

            // Random mode with reverse
            if (rvrsParam)
            {

                // Randomly drive forward or backward at a random speed
                long rndRnd = (random(0, 9));
                if (rndRnd > 4)
                {
                    driveBackwards = true;
                }
                else
                {
                    driveBackwards = false;
                }

                // Drive backwards
                if (driveBackwards)
                {
                    actualSpeed = random(SLOW_SPEED, maxSpeed);
                    analogWrite(outputPinOne_, OFF_SPEED);
                    analogWrite(outputPinTwo_, actualSpeed);
                }
                else
                {
                    // Drive forwards
                    actualSpeed = random(SLOW_SPEED, maxSpeed);
                    analogWrite(outputPinOne_, actualSpeed);
                    analogWrite(outputPinTwo_, OFF_SPEED);
                }
            }
            else
            {
                driveBackwards = false;
                actualSpeed = random(SLOW_SPEED, maxSpeed);
                analogWrite(outputPinOne_, actualSpeed);
                analogWrite(outputPinTwo_, OFF_SPEED);
            }
            randomTime_ = random(500, 5000);
            oldTime_ = newTime_;
        }
    }
    else
    // Random mode without reverse
    {
        // Non-random mode with reverse
        if (rvrsParam)
        {
            // Drive backward at the maximum speed
            driveBackwards = true;
            actualSpeed = maxSpeed;
            analogWrite(outputPinOne_, OFF_SPEED);
            analogWrite(outputPinTwo_, maxSpeed);
        }
        else // Non-random mode without reverse
        {
            // Drive forward at the maximum speed
            driveBackwards = false;
            actualSpeed = maxSpeed;
            analogWrite(outputPinOne_, maxSpeed);
            analogWrite(outputPinTwo_, OFF_SPEED);
        }
    }
}

// Returns the current speed of the motor

uint8_t Control::getSpeed() { return actualSpeed; }

// Returns the current direction of the motor (true for forward, false for
// backward)
bool Control::getDirection() { return !driveBackwards; }
