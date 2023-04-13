// *********************************************************************
// Includes
// *********************************************************************
#include <Arduino.h>
//#include <LiquidCrystal.h>
#include "Control.h" 
#include "Encoder.h" 
#include "Menu.h" 
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// *********************************************************************
// Defines
// *********************************************************************

// Pins for H-Bridge. One is down left. Two is up left. Three is down right. Four is up right
// on the left is the positive side of the motor, right the negative side
#define CNRTL_PIN_ONE 6 //forward
#define CNRTL_PIN_TWO 7 //backwards
//#define CNRTL_PIN_THREE 8
//#define CNRTL_PIN_FOUR 9

// Pin for addressable rgb data and number of leds
#define LED_PIN 3
#define NUMBER_OF_LEDS 44
#define BRIGHTNESS 10

// Rotary Encoder
#define ENCODER_A 10
#define ENCODER_B 11
#define ENCODER_BTN 12

//Display
#define WIDTH 128 // OLED display width, in pixels
#define HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1

#define ADDRESS 0x3C

#define DELAY_PIN 2 //enable step up

// display i2c pins
//SDA 20
//SCL 21 
// // //wurde in C:\Users\mazze\AppData\Local\Arduino15\packages\rp2040\hardware\rp2040\2.4.1\variants\generic\pins_arduino geandert
//C:\Users\mazze\AppData\Local\Arduino15\packages\rp2040\hardware\rp2040\2.7.1\variants\rpipico
//#define PIN_WIRE0_SDA  (20u)
//#define PIN_WIRE0_SCL  (21u)
// default "Wire" object: SDA = GP4, SCL = GP5, I2C0 peripheral
// our new wire object:
#define WIRE1_SDA       20  // Use GP2 as I2C1 SDA
#define WIRE1_SCL       21  // Use GP3 as I2C1 SCL
#define PIN_WIRE0_SCL  21;
#define PIN_WIRE0_SDA 20;
//arduino::MbedI2C Wire1(WIRE1_SDA, WIRE1_SCL);



// *********************************************************************
// Global Variables
// *********************************************************************

// change variable if the encoder has moved to change the menu
bool encoderMoved_ = false;

// *********************************************************************
// Objects
// *********************************************************************

Control CNTRL(CNRTL_PIN_ONE, CNRTL_PIN_TWO);
Encoder ENCD(ENCODER_A, ENCODER_B, ENCODER_BTN);
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);
Menu MENU(&ENCD, &display);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMBER_OF_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// *********************************************************************
// Functions
// *********************************************************************

void interruptA();
void interruptB();
void interruptBTN();

void setup()
{
  pinMode(DELAY_PIN, OUTPUT);
  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.print("Morsche");
  //start leds

  //start display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  //ADDRESS = 0x3C;
  if(!display.begin(SSD1306_SWITCHCAPVCC, ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  //delay(2000); // Display Adafruit logo for a bit :)
  display.clearDisplay();


  //display.setRotation(2); // Uncomment to rotate display 180 degrees
  display.setTextSize(2);   // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);      // Use full 256 char 'Code Page 437' font

  // Menu Begin
  MENU.displayMenu();

  // for upload test
  //pinMode(20, OUTPUT);

  //Interrupts
  
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), interruptA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), interruptB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), interruptBTN, RISING);

  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);

  for(int i=0; i<NUMBER_OF_LEDS; i++) 
  { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(0, 255, 255));  //blue

    pixels.show();   // Send the updated pixel colors to the hardware.

   }
  delay(1000);
  digitalWrite(DELAY_PIN, HIGH);
}

void loop()
{  

  if(encoderMoved_){
    MENU.displayMenu();
    encoderMoved_ = false;
    
  }
  CNTRL.setSpeed(ENCD.getSpeed(), ENCD.getRandomState(), ENCD.getReverseState());
  delay(100);
  //Serial.println(ENCD.getSpeed());
  if(CNTRL.getDirection()){
    for(int i=0; i<NUMBER_OF_LEDS; i++) 
    { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(CNTRL.getSpeed(), (255 - CNTRL.getSpeed()), (255 - CNTRL.getSpeed())));
      pixels.show();
    }
  }else{
    for(int i=0; i<NUMBER_OF_LEDS; i++) 
    { // For each pixel...
      pixels.setPixelColor(i, pixels.Color((255 - CNTRL.getSpeed()), CNTRL.getSpeed(), (255 - CNTRL.getSpeed())));
      pixels.show();
    }
  }
  
}

void interruptA(){
  encoderMoved_ = true;
  ENCD.interruptA();
}
void interruptB(){
  encoderMoved_ = true;
  Serial.println("Test2");
  ENCD.interruptB();
}
void interruptBTN(){
  encoderMoved_ = true;
  Serial.println("Test1");
  ENCD.interruptBTN();
}
