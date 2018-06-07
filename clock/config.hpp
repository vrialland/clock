#ifndef CONFIG_HPP
#define CONFIG_HPP

// Wifi
#define SSID "Clock"

// Screen
#define SCREEN_ADDRESS 0x3c
#define SCREEN_SDA D3
#define SCREEN_SCL D5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_HALF_X SCREEN_WIDTH / 2
#define SCREEN_HALF_Y SCREEN_HEIGHT / 2

// NTP setting
#define TIME_NTP_SERVER "pool.ntp.org" // NTP server URL
#define TIME_OFFSET 1  // Offset to UTC time in hours
#define TIME_SYNC_DELAY 3600 // Delay before NTP resync
#define TIME_USE_DAYLIGHT true // Daylight savings
#define TIME_MINUTES 0 // Minutes offset

#endif
