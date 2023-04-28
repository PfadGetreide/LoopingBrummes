// *********************************************************************
// Includes
// *********************************************************************
#include "Control.h"
#include "Encoder.h"
#include "Menu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// *********************************************************************
// Defines
// *********************************************************************

// Pins for TB67H451AFNG,EL DC motor driver.
#define CNRTL_PIN_ONE 6 // forward
#define CNRTL_PIN_TWO 7 // backwards

// Pins for addressable rgb data and number of leds
#define LED_PIN 3
#define NUMBER_OF_LEDS 44
#define BRIGHTNESS 10

// Rotary Encoder pins
#define ENCODER_A 10
#define ENCODER_B 11
#define ENCODER_BTN 12

// Display pins
#define WIDTH 128 // OLED display width, in pixels
#define HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1

#define ADDRESS 0x3C

// I2C pins for the SSD1306
// changed pins in path below below
// C:\Users\user\.platformio\packages\framework-arduinopico\variants\rpipico
// #define PIN_WIRE0_SDA  20
// #define PIN_WIRE0_SCL  21

// delay pin for step-up converter. Otherwise the pico crashes
#define DELAY_PIN 2

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
Adafruit_NeoPixel pixels =
    Adafruit_NeoPixel(NUMBER_OF_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// *********************************************************************
// Functions
// *********************************************************************

void interruptA();
void interruptB();
void interruptBTN();

void setup()
{
    // set delay pin to output
    pinMode(DELAY_PIN, OUTPUT);

    // serial init, only needed for testing purposses
    // Serial.begin(9600);
    // Serial.print("Morsche");

    // start display
    display.begin(SSD1306_SWITCHCAPVCC, ADDRESS);
    display.setTextColor(SSD1306_WHITE);

    // Menu Begin
    MENU.displayMenu();

    // set Interrupts
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);
    pinMode(ENCODER_BTN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), interruptA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B), interruptB, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), interruptBTN, RISING);

    // start leds
    pixels.begin();
    pixels.setBrightness(BRIGHTNESS);

    // give every led a start colour
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 255, 255));
        pixels.show();
    }

    // wait for everything to stablilize, then start the step-up converter
    delay(1000);
    digitalWrite(DELAY_PIN, HIGH);
}

void loop()
{
    // Check if the encoder was moved
    if (encoderMoved_)
    {
        // Display the menu
        MENU.displayMenu();

        // Reset the encoder moved flag
        encoderMoved_ = false;
    }

    // Set the speed and direction of the LEDs based on the encoder state
    CNTRL.setSpeed(ENCD.getSpeed(), ENCD.getRandomState(), ENCD.getReverseState());

    // Wait for 100ms
    delay(100);

    // If the direction is forward
    if (CNTRL.getDirection())
    {
        // For each LED
        for (int i = 0; i < NUMBER_OF_LEDS; i++)
        {
            // Set the color based on the speed
            pixels.setPixelColor(i, pixels.Color(CNTRL.getSpeed(), (255 - CNTRL.getSpeed()), (255 - CNTRL.getSpeed())));

            // Update the LED
            pixels.show();
        }
    }
    else // If the direction is backward
    {
        // For each LED
        for (int i = 0; i < NUMBER_OF_LEDS; i++)
        {
            // Set the color based on the speed
            pixels.setPixelColor(i, pixels.Color((255 - CNTRL.getSpeed()), CNTRL.getSpeed(), (255 - CNTRL.getSpeed())));

            // Update the LED
            pixels.show();
        }
    }
}

// Interrupt function for encoder pin A
void interruptA()
{
    // Set the encoder moved flag
    encoderMoved_ = true;

    // Call the encoder interrupt function for pin A
    ENCD.interruptA();
}

// Interrupt function for encoder pin B
void interruptB()
{
    // Set the encoder moved flag
    encoderMoved_ = true;

    // Call the encoder interrupt function for pin B
    ENCD.interruptB();
}

// Interrupt function for encoder button
void interruptBTN()
{
    // Set the encoder moved flag
    encoderMoved_ = true;

    // Call the encoder interrupt function for the button
    ENCD.interruptBTN();
}