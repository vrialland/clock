#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "SSD1306Wire.h"

#include "config.h"

// Display
SSD1306Wire display(OLED_ADDRESS, OLED_SDA, OLED_SCL);
// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, 0, 3600);


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
  display.drawStringMaxWidth(OLED_PADDING, 0, OLED_WIDTH, "Connecting to wifi: ");
  display.drawStringMaxWidth(OLED_PADDING, 14, OLED_WIDTH, WIFI_SSID);
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
  display.drawStringMaxWidth(OLED_PADDING, 0, OLED_WIDTH, "Connected, IP address: ");
  display.drawStringMaxWidth(OLED_PADDING, 14, OLED_WIDTH, String(WiFi.localIP()));
  display.display();
  // Init NTP client
  timeClient.begin();
}


void loop() {
  timeClient.update();
  display.clear();
  String time = timeClient.getFormattedTime();
  display.drawStringMaxWidth(OLED_PADDING, 0, OLED_WIDTH, time);
  display.display();
  Serial.println(time);
  delay(1000);
}

