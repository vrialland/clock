#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "SSD1306Wire.h"
#include "TimeLib.h"

#include "config.h"
#include "fonts.h"

// Display
SSD1306Wire display(SCREEN_ADDRESS, SCREEN_SDA, SCREEN_SCL);
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
  // Init display
  display.init();
  display.setFont(Roboto_12);

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
  display.setFont(Roboto_36);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawStringMaxWidth(SCREEN_HALF_X, 23, SCREEN_WIDTH, getTime(timeClient.getEpochTime()));
  display.setFont(Roboto_12);
  display.drawStringMaxWidth(SCREEN_HALF_X, 53, SCREEN_WIDTH, getDate(timeClient.getEpochTime()));
  display.display();
  delay(1000);
}

