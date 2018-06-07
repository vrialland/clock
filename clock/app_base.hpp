#ifndef BASE_APP_HPP
#define BASE_APP_HPP

#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>


class BaseApp {
    protected:
        unsigned long _lastUpdate;
        int _updateInterval; // In seconds
        bool needsUpdate(unsigned long ms);
        virtual bool doUpdate() = 0;
    public:
        BaseApp(unsigned int updateInterval=0);
        void begin();
        bool update(unsigned long ms);
        virtual void draw(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) const = 0;
};

#endif
