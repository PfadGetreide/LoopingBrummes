#include "Menu.h"

// Constructor for the Menu class. Takes pointers to an Encoder and Adafruit_SSD1306 object.
Menu::Menu(Encoder* a_encoder, Adafruit_SSD1306* a_lcd)
{
    // Store the encoder and display objects.
    menuEncoder_ = a_encoder;
    menuDisplay_ = a_lcd;
    // Initialize the menu position to zero.
    menuPosition_ = 0;
    // Initialize the speed, random, and reverse settings.
    speed_ = 0;
    randomON_ = false;
    reverseON_ = false;
}

// Displays the current menu on the OLED display.
void Menu::displayMenu()
{
    // Get the current menu position, speed setting, and random and reverse states from the encoder object.
    menuPosition_ = menuEncoder_->getMenuPosition();
    randomON_ = menuEncoder_->getRandomState();
    reverseON_ = menuEncoder_->getReverseState();
    speed_ = menuEncoder_->getSpeedPercentage();
    // Clear the display and set the cursor position to (0,0).
    menuDisplay_->clearDisplay();
    menuDisplay_->setCursor(0, 0);
    // Set the text size to 1 and display a header.
    menuDisplay_->setTextSize(1);
    menuDisplay_->println("Looping Brummes!");
    menuDisplay_->display();

    // Based on the current menu position, display the appropriate menu item.
    switch (menuPosition_)
    {
        case 0:
            // Set the text size to 3, display the speed setting.
            menuDisplay_->setTextSize(3);
            menuDisplay_->setCursor(0, 8);
            menuDisplay_->print("Spd:");
            menuDisplay_->print(speed_);
            break;
        case 1:
            // Set the text size to 3, display the random setting.
            menuDisplay_->setTextSize(3);
            menuDisplay_->setCursor(0, 8);
            menuDisplay_->print("Rnd:");
            if (randomON_)
            {
                menuDisplay_->print("ON");
            }
            else
            {
                menuDisplay_->print("OFF");
            }
            break;
        case 2:
            // Set the text size to 3, display the reverse setting.
            menuDisplay_->setTextSize(3);
            menuDisplay_->setCursor(0, 8);
            menuDisplay_->print("Rvr:");
            if (reverseON_)
            {
                menuDisplay_->print("ON");
            }
            else
            {
                menuDisplay_->print("OFF");
            }
            break;
    }
    // Display the updated menu.
    menuDisplay_->display();
}
