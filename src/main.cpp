/**
 * @file   main.cpp
 * @author openDrone <opendrone@googlegroups.com>
 * @date   Wed Apr 11 22:59:22 2012
 * 
 * @brief  openDrone Quadcopter Main function File
 * @license GPLv3
 * 
 */


#include "main.h"
#include "i2c.h"
#include "qctest.h"

#define BS '\b'

unsigned long previousMillis = 0;        
unsigned long interval = 1000;           

void flightMode()
{
    SerialUSB.println(">> Flight Mode <<");
    return;
}


void setup()
{
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Hello world!");

    /* Send a message out the usb virtual serial port  */
    SerialUSB.println("Hello!");
    SerialUSB.println("Test1234567890!");
}


void loop()
{
    int i = 5;
    char ch;
    
    delay(3000);

    unsigned long currentMillis ;
    previousMillis = millis();

    SerialUSB.print("\n\rPress any key to enter [Test Mode]:  ");
    
    while(SerialUSB.available() == 0 && i >= 0)
    {
        currentMillis = millis();
        if(currentMillis - previousMillis > interval)
        {    
            // save the last time you blinked the LED 
            previousMillis = currentMillis;
            SerialUSB.print(BS);  
            SerialUSB.print(i, DEC);
            toggleLED();
            i--;
        }
    }

    if(i <= 0 )
    {
        SerialUSB.println("\n\r Entering [Flight Mode]...");
        flightMode(); //TODO
        loop();
    }
    else SerialUSB.println("\n\r Entering [Test Mode] ...");

    while(1)
    {
        do{
            SerialUSB.read();    
        }while(SerialUSB.available() != 0);

        toggleLED();
        delay(1000);
        
         /* clear screen for standard PTY terminal  "\033[1H\033[2J " */
        SerialUSB.println("\33[2J");
        
        SerialUSB.println("\n\r >> OpenDrone Flymaple 1.0 << ");
        SerialUSB.println("---------------------------------");
        SerialUSB.println("(s) Sensors Test");
        SerialUSB.println("(m) Motors Test");
        SerialUSB.println("(r) Remote Control Test");
        SerialUSB.println("(t) Take Off");
        SerialUSB.println("(l) Landing");
        SerialUSB.println("(?) Help - Print this screen");
        SerialUSB.println("(x) Reset");
        SerialUSB.println("================================");
        SerialUSB.print("Choose ( \"?\" for help): ");

        /* Echo Charactor */
        ch = SerialUSB.read(); 
        SerialUSB.println(ch);
        
        switch(ch)
        {
            case 's':  sensorsTest(); break;
            case 'm':  motorsTest(); break;
            case 'r':  remoteTest(); break;
            case 't':  qcTakeOff(); break;
            case 'l':  qcLanding(); break;
            case '?':  break;
            case 'x': loop(); //call itself for resetting
            default: break;
        }
    }
}

/* Please Do Not Remove & Edit Following Code */
int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
