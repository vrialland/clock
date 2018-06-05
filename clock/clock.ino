// WifiManager
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// NTP Client
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <SSD1306Brzo.h>
#include <TimeLib.h>

#include "config.hpp"
#include "fonts.hpp"
#include "images.hpp"

// Display
SSD1306Brzo display(SCREEN_ADDRESS, SCREEN_SDA, SCREEN_SCL);
// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, TIME_NTP_SERVER, TIME_OFFSET, TIME_SYNC_DELAY);


String getTime(long epochTime) {
  int hours = hour(epochTime);
  int minutes = minute(epochTime);
  String out = "";
  out += hours < 10 ? "0" + String(hours) : String(hours);
  out += ":";
  out += minutes < 10 ? "0" + String(minutes) : String(minutes);
  return out;
}


String getDate(long epochTime) {
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
  String dayStr = String(day(epochTime));
  String monthStr = months[month(epochTime) - 1];
  String yearStr = String(year(epochTime));
  return dayStr + " " + monthStr + " " + yearStr;
}


void setup() {
  Serial.begin(115200);

  // Init display
  display.init();
  
  // Configure wifi connection
  WiFiManager wifiManager;
  // Display setup infos on screen (wifi logo + SSID)
  String ssid = "Clock";
  display.drawXbm((int)(SCREEN_HALF_X - WIFI_LOGO_WIDTH / 2), 2, WIFI_LOGO_WIDTH, WIFI_LOGO_HEIGHT, WIFI_LOGO_BITS);
  display.setFont(Roboto_12);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawStringMaxWidth(SCREEN_HALF_X, 44, SCREEN_WIDTH, "SSID: \"" + ssid + "\"");
  display.display();
  
  wifiManager.autoConnect(ssid.c_str());

  // Clear screen
  display.clear();
  display.display();
  
  // Init NTP client
  timeClient.begin();
}


void loop() {
  // Update time if needed
  timeClient.update();

  // Clear screen
  display.clear();

  // Display time and date
  display.setFont(Roboto_36);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawStringMaxWidth(SCREEN_HALF_X, 23, SCREEN_WIDTH, getTime(timeClient.getEpochTime()));
  display.setFont(Roboto_12);
  display.drawStringMaxWidth(SCREEN_HALF_X, 53, SCREEN_WIDTH, getDate(timeClient.getEpochTime()));

  // Update screen
  display.display();

  delay(1000);
}

