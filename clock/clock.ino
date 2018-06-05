// WifiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

// NTP Client
#include <NTPClient.h>
#include <WiFiUdp.h>

// SSD1306 + UI
#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>

// Clock helpers
#include <TimeLib.h>

#include "config.hpp"
#include "fonts.hpp"
#include "images.hpp"


// Clock helpers
String getTime() {
  int hours = hour();
  int minutes = minute();
  String out = "";
  out += hours < 10 ? "0" + String(hours) : String(hours);
  out += ":";
  out += minutes < 10 ? "0" + String(minutes) : String(minutes);
  return out;
}


String getDate() {
  const String months[] = {
    "janvier",
    "février",
    "mars",
    "avril",
    "mai",
    "juin",
    "juillet",
    "août",
    "septembre",
    "octobre",
    "novembre",
    "décembre"
  };
  String dayStr = String(day());
  String monthStr = months[month() - 1];
  String yearStr = String(year());
  return dayStr + " " + monthStr + " " + yearStr;
}


void showWifiSetup(OLEDDisplay *display, const char* ssid) {
    display->drawXbm((int)(SCREEN_HALF_X - WIFI_LOGO_WIDTH / 2), 2, WIFI_LOGO_WIDTH, WIFI_LOGO_HEIGHT, WIFI_LOGO_BITS);
    display->setFont(Roboto_12);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawStringMaxWidth(SCREEN_HALF_X, 44, SCREEN_WIDTH, "SSID: \"" + String(ssid) + "\"");
    display->display();
}


// Apps frames
void drawClockFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) {
  display->setFont(Roboto_36);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawStringMaxWidth(SCREEN_HALF_X, 0, SCREEN_WIDTH, getTime());
  display->setFont(Roboto_12);
  display->drawStringMaxWidth(SCREEN_HALF_X, 39, SCREEN_WIDTH, getDate());
}


// Display
SSD1306Brzo display(SCREEN_ADDRESS, SCREEN_SDA, SCREEN_SCL);
OLEDDisplayUi ui(&display);
FrameCallback frames[] = { drawClockFrame };
int framesCount = 1;

// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, TIME_NTP_SERVER, TIME_OFFSET, TIME_SYNC_DELAY);


void setup() {
  Serial.begin(115200);

  // Init display
  display.init();
  display.flipScreenVertically();
  
  // Configure wifi connection
  WiFiManager wifiManager;
  showWifiSetup(&display, SSID);
  wifiManager.autoConnect(SSID);

  // Clear screen
  display.clear();
  display.display();

  // Configure UI
  ui.setTargetFPS(30);
  ui.setActiveSymbol(UI_ACTIVE_SYMBOL);
  ui.setInactiveSymbol(UI_INACTIVE_SYMBOL);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, framesCount);
  ui.init();
  display.flipScreenVertically();
  
  // Init NTP client
  timeClient.begin();
}


void loop() {
  // Update time if needed
  timeClient.update();
  setTime(timeClient.getEpochTime());

  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }
}

