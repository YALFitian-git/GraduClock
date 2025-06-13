#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "time.h"

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Enter your access point credentials here
const char* ssid = ""; //Set AP SSID
const char* password = ""; //Set AP Passkey (leave blank if unneeded)


// Timezone config
const long gmtOffset_sec = -18000; //Replace pre-set value with your region's GMT offset
const int daylightOffset_sec = 0; //Daylight Savings setting
const char* ntpServer = "pool.ntp.org";  //NTP Server setting

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Configure time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  // Get timestamp, subtract from target and convert to units
  char countDown[12];
  time_t currentTime;
  int targetTimeStamp = 1767247200; //Replace pre-set value with your target timestamp
  currentTime = time(NULL); //Get current timestamp
  int countdownTime = (targetTimeStamp - currentTime); //Subtract current timestamp from target to create a countdown
  int days = (countdownTime / 86400); 
  int rem = (countdownTime % 86400); 
  int hours = (rem / 3600); //remainder variable converts remainders in days to hours
  rem = rem % 3600;
  int mins = (rem / 60); //remainder variable converts remainders in hours to minutes
  sprintf(countDown, "%lu:%02lu:%02lu", days, hours, mins); //Text formatting

  // Display on OLED
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(8, 20);
  display.print(countDown);
  display.display();
  delay(1000);
}
