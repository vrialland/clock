#ifndef APP_CLOCK_HPP
#define APP_CLOCK_HPP

// OLED + UI
#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>

// Time related
#include <NtpClientLib.h>
#include <TimeLib.h>

// Local includes
#include "app_base.hpp"
#include "config.hpp"
#include "fonts.hpp"
#include "images.hpp"


class ClockApp : public BaseApp {
    private:
        String _ntpServerName;
        int8_t _timeOffset;
        bool _daylight;
        int8_t _minutes;
        int updateInterval;
    protected:
        String getDate() const;
        String getTime() const;
    public:
        ClockApp(String ntpServerName="pool.ntp.org", int8_t timeOffset=0, bool daylight=false, int8_t minutes=0, int updateInterval=3600);
        void begin();
        bool needsUpdate(unsigned long ms);
        bool doUpdate();
        void draw(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) const;
};

#endif
