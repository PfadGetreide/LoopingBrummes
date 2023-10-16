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

    // Initializing the menu position, encoder speed and speed percentage
    // variables
    menuPos_ = 0;
    encoderSpeed_ = 0;
    speedPercentage_ = 0;

    // Initializing the debounce time and last interrupt time
    lastInterruptTime_ = 0;
    interruptTime_ = 0;
    debounceTime_ = 20;

    // Setting the maximum number of menu items
    maxMenuItems_ = 3;

    // Initializing the random, reverse and speed select states
    randomONencoder_ = false;
    reverseONencoder_ = false;
    speedSelectState_ = false;
}

void Encoder::interruptA()
{
    interruptTime_ = millis();
    // debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)
    {

        // Debounce again (maybe unnecessary)
        if (digitalRead(inputPinA_) != pinAState_)
        {
            // Update the pin A state
            pinAState_ = !pinAState_;
            if (pinAState_ && !pinBState_)
            {
                if (speedSelectState_)
                {
                    speedPercentage_ += 5;
                    if (speedPercentage_ > 100)
                    {
                        speedPercentage_ = 0;
                    }
                    encoderSpeed_ = static_cast<uint8_t>(
                        (static_cast<float>(speedPercentage_) / 100) * 255);
                    // Serial.println(encoderSpeed_);
                }
                else
                {
                    menuPos_ += 1;
                    if (menuPos_ >= maxMenuItems_)
                    {
                        menuPos_ = 0;
                    }
                }
                // Serial.println(menuPos_);
            }
            lastInterruptTime_ = interruptTime_;
        }
    }
    Serial.println("A ");
    Serial.print("A State: ");
    Serial.println(pinAState_);
    Serial.print("B State: ");
    Serial.println(pinBState_);
    Serial.print("Menu Position: ");
    Serial.println(menuPos_);
    interruptTime_ = millis();
}

void Encoder::interruptB()
{
    interruptTime_ = millis();
    // debounce
    if (interruptTime_ - lastInterruptTime_ >
        debounceTime_) // Check if enough time has passed since the last
                       // interrupt
    {

        // Debounce again maybe unnecessary
        if (digitalRead(inputPinB_) !=
            pinBState_) // Check if the input pin B has changed since the last
                        // interrupt
        {
            pinBState_ = !pinBState_;
            if (pinBState_ && !pinAState_)
            {
                if (speedSelectState_)
                {
                    speedPercentage_ -= 5;
                    if (speedPercentage_ > 100)
                    {
                        speedPercentage_ = 100;
                    }
                    encoderSpeed_ = static_cast<uint8_t>(
                        (static_cast<float>(speedPercentage_) / 100) * 255);
                    // Serial.println(encoderSpeed_);
                }
                else
                {
                    // cycle to the first menu item
                    menuPos_ -= 1;
                    if (menuPos_ >= maxMenuItems_)
                    {
                        menuPos_ = maxMenuItems_ - 1;
                    }
                }
            }
            lastInterruptTime_ = interruptTime_;
        }
    }
    Serial.println("b ");
    Serial.print("A State: ");
    Serial.println(pinAState_);
    Serial.print("B State: ");
    Serial.println(pinBState_);
    Serial.print("Menu Position: ");
    Serial.println(menuPos_);
}

void Encoder::interruptBTN()
{
    interruptTime_ = millis(); // Get current time in milliseconds
    // debounce
    if (interruptTime_ - lastInterruptTime_ >
        debounceTime_) // Check if enough time has passed since the last
                       // interrupt
    {

        // state change for if the button was pressed when in menu state
        if (menuPos_ ==
            0) // Check if we are currently in the "speed select" menu
        {
            // Serial.println("speedselect");
            speedSelectState_ =
                !speedSelectState_; // Toggle the speed select state
        }
        if (menuPos_ ==
            1) // Check if we are currently in the "random select" menu
        {
            // Serial.println("randomselect");
            randomONencoder_ =
                !randomONencoder_; // Toggle the random select state
        }
        if (menuPos_ ==
            2) // Check if we are currently in the "reverse select" menu
        {
            // Serial.println("reverseselect");
            reverseONencoder_ =
                !reverseONencoder_; // Toggle the reverse select state
        }
    }
    // Debugging-Ausgabe
    Serial.print("Menu Position: ");
    Serial.println(menuPos_);
}

uint8_t Encoder::getMenuPosition()
{
    return menuPos_;
} // Return the current menu position

bool Encoder::getRandomState()
{
    return randomONencoder_;
} // Return the current random select state

bool Encoder::getReverseState()
{
    return reverseONencoder_;
} // Return the current reverse select state

uint8_t Encoder::getSpeedPercentage()
{
    return speedPercentage_;
} // Return the current speed percentage
