#include "Encoder.h"

Encoder::Encoder(uint8_t a_inputPinA, uint8_t a_inputPinB, uint8_t a_buttonPin)
{
    // Assigning the pin numbers
    inputPinA_ = a_inputPinA;
    inputPinB_ = a_inputPinB;
    buttonPin_ = a_buttonPin;

    // Reading the initial states of the input pins
    pinAState_ = digitalRead(inputPinA_);
    pinBState_ = digitalRead(inputPinB_);

    // Initializing the menu position, encoder speed and speed percentage variables
    menuPos_ = 0;
    encoderSpeed_ = 0;
    speedPercentage_ = 0;

    // Initializing the debounce time and last interrupt time
    lastInterruptTime_ = 0;
    interruptTime_ = 0;
    debounceTime_ = 5;

    // Setting the maximum number of menu items
    maxMenuItems_ = 3;

    // Initializing the random, reverse and speed select states
    randomONencoder_ = false;
    reverseONencoder_ = false;
    speedSelectState_ = false;
}

void Encoder::interruptA()
{
    // Get the current time
    interruptTime_ = millis();

    // Debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)
    {

        // Debounce again (maybe unnecessary)
        if (digitalRead(inputPinA_) != pinAState_)
        {
            // Update the pin A state
            pinAState_ = !pinAState_;

            // If pin A state is high and pin B state is low
            if (pinAState_ && !pinBState_)
            {
                // If speed select state is true
                if (speedSelectState_)
                {
                    // Increment the speed percentage by 5 and update the encoder speed
                    speedPercentage_ += 5;
                    if (speedPercentage_ > 100)
                    {
                        speedPercentage_ = 0;
                    }
                    encoderSpeed_ = static_cast<uint8_t>(
                        (static_cast<float>(speedPercentage_) / 100) * 255);
                    // Debugging output
                    // Serial.println(encoderSpeed_);
                }
                else
                {
                    // Increment the menu position by 1 and cycle back to the first menu item if necessary
                    menuPos_ += 1;
                    if (menuPos_ >= maxMenuItems_)
                    {
                        menuPos_ = 0;
                    }
                }
                // Debugging output
                // Serial.println(menuPos_);
            }
            lastInterruptTime_ = interruptTime_;
        }
    }
}

void Encoder::interruptB()
{
    interruptTime_ = millis();  // Get current time in milliseconds
    // debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)  // Check if enough time has passed since the last interrupt
    {

        // Debounce again maybe unnecessary
        if (digitalRead(inputPinB_) != pinBState_)  // Check if the input pin B has changed since the last interrupt
        {
            pinBState_ = !pinBState_;  // Flip the state of pin B
            if (pinBState_ && !pinAState_)  // Check if pin B is high and pin A is low (i.e. rotating in one direction)
            {
                if (speedSelectState_)  // Check if we are currently in the "speed select" menu
                {
                    speedPercentage_ -= 5;  // Decrement the speed percentage by 5%
                    if (speedPercentage_ > 100)  // Check if the speed percentage is above 100%
                    {
                        speedPercentage_ = 100;  // Cap the speed percentage at 100%
                    }
                    encoderSpeed_ = static_cast<uint8_t>(
                        (static_cast<float>(speedPercentage_) / 100) * 255);  // Calculate the corresponding encoder speed based on the percentage
                    // Serial.println(encoderSpeed_);
                }
                else  // We are not in the "speed select" menu
                {
                    // cycle to the first menu item
                    menuPos_ -= 1;  // Decrement the menu position by 1
                    if (menuPos_ >= maxMenuItems_)  // Check if the menu position is greater than or equal to the maximum number of menu items
                    {
                        menuPos_ = maxMenuItems_ - 1;  // Wrap around to the first menu item
                    }
                }
            }
            lastInterruptTime_ = interruptTime_;  // Update the last interrupt time
        }
    }
}

void Encoder::interruptBTN()
{
    interruptTime_ = millis();  // Get current time in milliseconds
    // debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)  // Check if enough time has passed since the last interrupt
    {

        // state change for if the button was pressed when in menu state
        if (menuPos_ == 0)  // Check if we are currently in the "speed select" menu
        {
            // Serial.println("speedselect");
            speedSelectState_ = !speedSelectState_;  // Toggle the speed select state
        }
        if (menuPos_ == 1)  // Check if we are currently in the "random select" menu
        {
            // Serial.println("randomselect");
            randomONencoder_ = !randomONencoder_;  // Toggle the random select state
        }
        if (menuPos_ == 2)  // Check if we are currently in the "reverse select" menu
        {
            // Serial.println("reverseselect");
            reverseONencoder_ = !reverseONencoder_;  // Toggle the reverse select state
        }
    }
}

uint8_t Encoder::getMenuPosition() { return menuPos_; }  // Return the current menu position

bool Encoder::getRandomState() { return randomONencoder_; }  // Return the current random select state

bool Encoder::getReverseState() { return reverseONencoder_; }  // Return the current reverse select state

uint8_t Encoder::getSpeedPercentage() { return speedPercentage_; }  // Return the current speed percentage
