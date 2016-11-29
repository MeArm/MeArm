//This code has the mode select commented out as well as the slider code
//The result is a faster joysticks code. There's a delay function that we use to
// slow the movemement of the arm down.
// Idle is also set at 100 which probably needs adjusting to stop the servos timing out so quickly.

#include <Servo.h> 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 4 - Data/Command select (D/C)
// pin 8 - LCD chip select (CS)
// pin 7 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(4, 8, 7);//updated MeArm Pins
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define XPOS 0
#define YPOS 1

const int SERVOS = 4;
const int ACC = 10; // the accurancy of the potentiometer value before idle starts counting
const int CON = 50; // the value of the contrast for the LCD Screen Min is 0 and Max 120 if you can't see anything try increasing, if you see a black box try decreasing.
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS],ANA[SERVOS];
Servo myservo[SERVOS];
//int modePin = 3;
//int mode = LOW; // mode stores button push to change between Joysticks and Sliders

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

/*static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
*/

void setup()   {
  Serial.begin(57600);
//  int mode = LOW; 
//  pinMode(modePin, INPUT); // Enables button for Mode Change on Startup
  display.begin();
  // init done
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(CON);
  display.display(); // show splashscreen
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
//  display.println("To Use Sliders");
//  display.println("Hold Right Button");
//  display.println("Else");
  display.println("Greetings");
  display.println("from Mime");
  display.println("Industies ");
  display.println(" ");
  display.println("Code V1.0");
  display.print("Contrast=");
  display.println(CON);
  display.display(); // show splashscreen
  delay(5000);
  display.clearDisplay();   // clears the screen and buffer
  
//  mode=digitalRead(modePin);
  
/*  if (mode == HIGH){
    display.clearDisplay();   // clears the screen and buffer
    display.println("Sliders");
    display.println("Enabled");
    display.display(); // push display to screen
    delay(2000);
  } else {
    display.clearDisplay();   // clears the screen and buffer
    display.println("Joysticks");
    display.println("Enabled");
    display.display(); // push display to screen
    delay(2000);
  }
 */
  //Middle Servo
  PIN[0] = 10;
  MIN[0] = 0;
  MAX[0] = 180;
  INITANGLE[0] = 90;
  ANA[0] = 1;
  //Left Side
  PIN[1] = 9;
  MIN[1] = 80; // This should bring the lever to just below 90deg to ground
  MAX[1] = 180;
  INITANGLE[1] = 152; // This should bring the lever parallel with the ground
  ANA[1] = 0;
  //Right Side
  PIN[2] = 6;
  MIN[2] = 25;
  MAX[2] = 180;
  INITANGLE[2] = 90;
  ANA[2] = 2;
  //Claw Servo
  PIN[3] = 5;
  MIN[3] = 0;
  MAX[3] = 179;
  INITANGLE[3] = 0;
  ANA[3] = 3;
  
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i]=INITANGLE[i];
  }
}

void loop() {
  delay(15); // Delay function to slow movement of arm down
//  if (mode == LOW){ 
    for (int i = 0; i < SERVOS; i++){
      value[i] = analogRead(ANA[i]);
      currentAngle[i] = myservo[i].read();
    
      if (value[i] > 612) {
        idle[i] = 0;
      
        if (currentAngle[i] < MAX[i]) ++currentAngle[i];
        if (!myservo[i].attached()){
          myservo[i].attach(PIN[i]);
        }
        myservo[i].write(currentAngle[i]);     
      } else if (value[i] < 412) {
      idle[i] = 0;
      if (currentAngle[i] > MIN[i]) --currentAngle[i];
      if (!myservo[i].attached()){
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);    
    } else {
      ++idle[i];
    }
    if (idle[i] > 100){
      myservo[i].detach();
      idle[i] = 0;
    }  
  }  
//  } else {  for (int i = 0; i < SERVOS; i++){
//    value[i] = analogRead(ANA[i]);
//    currentAngle[i] = map(value[i],0,1023,MIN[i],MAX[i]);
    
//    if (currentAngle[i] > (previousAngle[i]+ACC)) {
/*      idle[i] = 0;
      
      if (currentAngle[i] < MAX[i]);
      if (!myservo[i].attached()){
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);
      previousAngle[i]=currentAngle[i];     
    } else if (currentAngle[i] < (previousAngle[i]-ACC)) {
      idle[i] = 0;
      if (currentAngle[i] > MIN[i]) --currentAngle[i];
      if (!myservo[i].attached()){
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);
      previousAngle[i]=currentAngle[i];     
    } else {
      ++idle[i];
    }
    if (idle[i] > 100){
      myservo[i].detach();
      idle[i] = 0;
    }  
  }  
  }
*/  
//  Serial.print(currentAngle[0]);
//  Serial.print(" ; ");
//  Serial.print(currentAngle[1]);
//  Serial.print(" ; ");
//  Serial.print(currentAngle[2]);
//  Serial.print(" ; ");
//  Serial.println(currentAngle[3]);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("These are the current");
  display.println("servo angles.");
  display.print(currentAngle[0]);
  display.print(";");
  display.print(currentAngle[1]);
  display.print(";");
  display.print(currentAngle[2]);
  display.print(";");
  display.println(currentAngle[3]);
  display.println("Mime.co.uk");
//  display.println(idle[1]);
  
//  Display Potentiometer Values on LCD (Slows MeArm Down too)
//  display.print(value[0]);
//  display.print(";");
//  display.print(value[1]);
//  display.print(";");
//  display.print(value[2]);
//  display.print(";");
//  display.println(value[3]);
  

  display.display();
  
}



/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
