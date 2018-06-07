#ifndef APP_CLOCK_HPP
#define APP_CLOCK_HPP

// OLED + UI
#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>

// Time related
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

// Local includes
#include "app_base.hpp"
#include "config.hpp"
#include "fonts.hpp"
#include "images.hpp"


class ClockApp : public BaseApp {
    protected:
        String getDate() const;
        String getTime() const;
    public:
        virtual void draw(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) const;
};

#endif
