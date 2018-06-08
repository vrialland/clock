// WifiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// SSD1306 + UI
#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>

// Local imports
#include "config.hpp"
#include "fonts.hpp"
#include "images.hpp"

// Apps
#include "app_clock.hpp"


void showWifiSetup(OLEDDisplay *display, const char* ssid) {
    display->drawXbm((int)(SCREEN_HALF_X - WIFI_LOGO_WIDTH / 2), 2, WIFI_LOGO_WIDTH, WIFI_LOGO_HEIGHT, WIFI_LOGO_BITS);
    display->setFont(Roboto_12);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawStringMaxWidth(SCREEN_HALF_X, 44, SCREEN_WIDTH, "SSID: \"" + String(ssid) + "\"");
    display->display();
}


// Apps
ClockApp appClock(TIME_NTP_SERVER, TIME_OFFSET, TIME_USE_DAYLIGHT, TIME_MINUTES, TIME_SYNC_DELAY);

// Apps frames
void drawClockFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) {
  appClock.draw(display, state, x, y);
}


void drawWeatherFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) {
  display->setFont(Roboto_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawStringMaxWidth(x + SCREEN_HALF_X, y, SCREEN_WIDTH, "Here comes the sun...");
}


// Display
SSD1306Brzo display(SCREEN_ADDRESS, SCREEN_SDA, SCREEN_SCL);
OLEDDisplayUi ui(&display);
FrameCallback frames[] = { drawClockFrame, drawWeatherFrame };
int framesCount = 2;


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
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, framesCount);
  ui.init();
  display.flipScreenVertically();

  // Setup loading
  int x0=4, y0=32, x1=120, y1=8, textY = 44;
  display.setFont(Roboto_12);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  
  // Load apps
  display.clear();
  display.drawProgressBar(x0, y0, x1, y1, 0);
  display.drawStringMaxWidth(SCREEN_HALF_X, textY, SCREEN_WIDTH, "Loading clock app...");
  display.display();
  appClock.begin();

  // Loading finished!
  display.clear();
  display.drawProgressBar(x0, y0, x1, y1, 100);
  display.drawStringMaxWidth(SCREEN_HALF_X, textY, SCREEN_WIDTH, "Done !");
  display.display();

  delay(1000);
}


void loop() {
  unsigned long ms = millis();
  Serial.println("Loop " + String(ms));
  
  // Don't break a running animation
  if (ui.getUiState()->frameState == FIXED) {
    appClock.update(ms);
  }

  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }
}

