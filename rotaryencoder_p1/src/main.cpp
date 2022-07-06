#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES 10 // Number of snowflakes in the animation example
#define SW 2
#define outputA 6
#define outputB 7

int counter = 0;
int state;
int last_state;
int stateCLK;
int last_stateCLK;
String currentdir =" ";
unsigned long lastButtonpress = 0; 

void setup()
{
  Serial.begin(115200);
  pinMode(SW,INPUT);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();
  display.display();
  // delay(2000);

  //last_state = digitalRead(outputA);
  last_stateCLK = digitalRead(outputA);
}
void drawCentreString(const char *buf, int x, int y);
void loop()
{
  // display.clearDisplay();
  //state = digitalRead(outputA);
  stateCLK = digitalRead(outputA);
  if (stateCLK != last_stateCLK && state ==1)
  {


    if (digitalRead(outputB) != stateCLK)
    {
      counter++;
      currentdir = "CW";
    }
    else
    {
      counter--;
      currentdir = "CCW";
      }
      
    // display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    // display.setCursor(0, 64);
    drawCentreString("position", 64, 0);

    // Serial.print("position");
    Serial.print("direction");
    Serial.println(currentdir);
    display.print("direction");
    display.println(currentdir);
    //Serial.println(counter);
    display.setCursor(64, 32);
    // display.print("position");
    //display.println(counter);
    display.display();
    // delay(2000);
    display.clearDisplay();
  }

  stateCLK = last_stateCLK;

  // Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if ((millis() - lastButtonpress) > 50) {
			Serial.println("Button pressed!");
      display.println("Button pressed");
		}

		// Remember last button press event
		lastButtonpress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);
}


void drawCentreString(const char *buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h); // calc width of new string
  display.setCursor(x - w / 2, y);
  display.println(buf);
}