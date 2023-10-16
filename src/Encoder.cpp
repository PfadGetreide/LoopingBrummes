#include "Encoder.h"

Encoder::Encoder(uint8_t a_inputPinA, uint8_t a_inputPinB, uint8_t a_buttonPin)
{
    inputPinA_ = a_inputPinA;
    inputPinB_ = a_inputPinB;
    buttonPin_ = a_buttonPin;

    pinAState_ = digitalRead(inputPinA_);
    pinBState_ = digitalRead(inputPinB_);

    menuPos_ = 0;
    encoderSpeed_ = 0;
    speedPercentage_ = 0;

    lastInterruptTime_ = 0;
    interruptTime_ = 0;
    debounceTime_ = 20;

    maxMenuItems_ = 3;

    randomONencoder_ = false;
    reverseONencoder_ = false;
    speedSelectState_ = false;
}

void Encoder::interruptA()
{

    // debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)
    {

        // Debounce again maybe unnecessary
        if (digitalRead(inputPinA_) != pinAState_)
        {
            pinAState_ = !pinAState_;
            // if (pinAState_ && !pinBState_)
            //{
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
            //}
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
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)
    {

        // Debounce again maybe unnecessary
        if (digitalRead(inputPinB_) != pinBState_)
        {
            pinBState_ = !pinBState_;
            // if (pinBState_ && !pinAState_)
            // {
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
            //}
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
    interruptTime_ = millis();
    // debounce
    if (interruptTime_ - lastInterruptTime_ > debounceTime_)
    {

        // state change for if the button was pressed when in menu state
        if (menuPos_ == 0)
        {
            // Serial.println("speedselect");
            speedSelectState_ = !speedSelectState_;
        }
        if (menuPos_ == 1)
        {
            // Serial.println("randomselect");
            randomONencoder_ = !randomONencoder_;
        }
        if (menuPos_ == 2)
        {
            // Serial.println("reverseselect");
            reverseONencoder_ = !reverseONencoder_;
        }
    }
    // Debugging-Ausgabe
    Serial.print("Menu Position: ");
    Serial.println(menuPos_);
}

uint8_t Encoder::getMenuPosition() { return menuPos_; }

bool Encoder::getRandomState() { return randomONencoder_; }

bool Encoder::getReverseState() { return reverseONencoder_; }

uint8_t Encoder::getSpeedPercentage() { return speedPercentage_; }

uint8_t Encoder::getSpeed() { return encoderSpeed_; }