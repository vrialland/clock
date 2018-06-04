#ifndef CONFIG_H
#define CONFIG_H

// Screen
#define SCREEN_ADDRESS 0x3c
#define SCREEN_SDA D3
#define SCREEN_SCL D5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_HALF_X SCREEN_WIDTH / 2
#define SCREEN_HALF_Y SCREEN_HEIGHT / 2

// Wifi related
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "password"

// NTP setting
#define TIME_NTP_SERVER "pool.ntp.org" // NTP server URL
#define TIME_OFFSET 2 * 3600  // Offset to UTC time in seconds 
#define TIME_SYNC_DELAY 3600 // Delay before NTP resync

#endif



