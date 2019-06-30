// Matt Rencher
// www.renchtech.com
// Read Serial from Python script
// Print the percentage on an OLED LCD

// Tested with:
// LCD: SSD1306 i2c 128x32
// Arduino Nano

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED 13

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
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
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

uint8_t color = WHITE;
String per;

void setup()   {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  uiInit();
}

const byte numChars = 6;
char receivedChars[numChars];   // an array to store the received data
int cursorX = 24;
String serialString;
float serialFloat;
int serialInt;
String prevString;

void loop() {
  
  if (Serial.available()) {
    serialString = Serial.readString();    // Recieve an entire string
    
    if (prevString == serialString){
      return;
      
    } else {
      prevString = serialString;
      serialFloat = serialString.toFloat();
      serialInt = int(serialFloat);
      if (serialInt >= 100) {
        cursorX = 24;
      } if (serialInt >= 10) {
        cursorX = 48;
      } if (serialInt < 10 && serialInt >= 0){
        cursorX = 64;
      }
      
      erase();
      digitalWrite(LED, LOW);
      display.setCursor(cursorX, 0);
      display.setTextSize(3);
      
      if (serialString != "") {
        digitalWrite(LED, HIGH);
        display.print(serialInt);
        display.setTextSize(2);
        display.print("%");
      } else {
        digitalWrite(LED, LOW);
      }

    display.display();
    delay(250);
    }
    
  } else {
//    delay(50);
  }
}  // END LOOP

void uiInit(){
  display.setCursor(0, 5);
  display.setTextSize(1);
  display.setTextColor(color);
  display.print("CPU");
  display.display();
}

void erase(){
  color = BLACK;
  display.fillRect(20,0,128,32, color);
  display.display();
  color = WHITE;
}
