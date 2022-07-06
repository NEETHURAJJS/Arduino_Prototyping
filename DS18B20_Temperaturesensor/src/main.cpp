#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2
#define LED_RED A0
#define LED_GREEN A1
#define LED_BLUE A2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
float Temperature = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup(void)
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  sensors.begin(); // Start up the library
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();
  display.display();
  delay(2000);
}
void drawCentreString(const char *buf, int x, int y);
void loop(void)

{
  sensors.requestTemperatures();
  Temperature = sensors.getTempCByIndex(0);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  drawCentreString("Temp", 64, 0);
  display.setCursor(16, 32);
  // display.print("Temperature=");
  display.setTextSize(2);
  display.print(sensors.getTempCByIndex(0));
  // display.print("Temperature=");
  // display.println(Temperature);
  // display.println(("°C"));

  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("°C  ");
  /*
  display.setCursor(16, 64);
  display.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  //display.print((char)176);//shows degrees character
  display.println("°F");


  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  //Serial.print((char)176);//shows degrees character
  Serial.println("°F");
  */
  display.display();
  // delay(2000);
  display.clearDisplay();

  if (Temperature > 30)
  {
    Serial.println("RED is on");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
  else if (Temperature > 28)

  {
    Serial.println("GREEN is on");
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
  else
  {
    Serial.println("BLUE is on");
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
  }
  delay(500);
}

void drawCentreString(const char *buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h); // calc width of new string
  display.setCursor(x - w / 2, y);
  display.println(buf);
}