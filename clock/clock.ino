#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "SSD1306Wire.h"

#include "config.h"

// Display
SSD1306Wire display(SCREEN_ADDRESS, SCREEN_SDA, SCREEN_SCL);
// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, TIME_NTP_SERVER, TIME_OFFSET, 3600);


void setup() {
  // Init display
  display.init();
  display.setFont(ArialMT_Plain_10);
  
  // Connect to configured wifi
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(WIFI_SSID);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawStringMaxWidth(0, 0, SCREEN_WIDTH, "Connecting to wifi: ");
  display.drawStringMaxWidth(0, 14, SCREEN_WIDTH, WIFI_SSID);
  display.display();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  display.clear();
  display.drawStringMaxWidth(0, 0, SCREEN_WIDTH, "Connected, IP address: ");
  display.drawStringMaxWidth(0, 14, SCREEN_WIDTH, String(WiFi.localIP()));
  display.display();
  // Init NTP client
  timeClient.begin();
}


void loop() {
  timeClient.update();
  display.clear();
  String time = timeClient.getFormattedTime();
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawStringMaxWidth(SCREEN_HALF_X, SCREEN_HALF_Y, SCREEN_WIDTH, time);
  display.display();
  Serial.println(time);
  delay(1000);
}

