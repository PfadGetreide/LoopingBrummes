#include "Menu.h" 

Menu::Menu(Encoder* a_encoder, Adafruit_SSD1306* a_lcd){
  //pass objects
    //pinMode(LED_BUILTIN, OUTPUT);

  menuEncoder_ = a_encoder;
  menuDisplay_ = a_lcd;
  menuPosition_ = 0;

  //set cols and rows
  //DISP_cols = 16;
  //DISP_rows = 2;

  // start condition for Brummes
  speed_ = 0;
  randomON_ = false;
  reverseON_ = false;

}

void Menu::displayMenu(){
  //delay(100);
  menuPosition_ = menuEncoder_->getMenuPosition();
  randomON_ = menuEncoder_->getRandomState();
  reverseON_ = menuEncoder_->getReverseState();
  speed_ = menuEncoder_->getSpeedPercentage();
  menuDisplay_->clearDisplay();
  menuDisplay_->setCursor(0, 0);
  menuDisplay_->setTextSize(1);
  //menuDisplay_->
  //menuDisplay_->startscrollright(0x00, 0x07);
  menuDisplay_->println("Looping Brummes!");
  menuDisplay_->display();

  switch (menuPosition_)
  {
    case 0:
    menuDisplay_->setTextSize(3);
      //menuDisplay_->stopscroll();
      menuDisplay_->setCursor(0, 8);
      menuDisplay_->print("Spd:");
      menuDisplay_->print(speed_);
      break;
    case 1:
      menuDisplay_->setTextSize(3);
      menuDisplay_->setCursor(0, 8);
      menuDisplay_->print("Rnd:");
      if(randomON_){
        menuDisplay_->print("ON");
      }else{
        menuDisplay_->print("OFF");
      }

      break;
    case 2:
          menuDisplay_->setTextSize(3);
      menuDisplay_->setCursor(0, 8);
      menuDisplay_->print("Rvr:");
      if(reverseON_){
        menuDisplay_->print("ON");
      }else{
        menuDisplay_->print("OFF");
      }

      break;
  }
    menuDisplay_->display();
}