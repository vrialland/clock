#ifndef BASE_APP_HPP
#define BASE_APP_HPP

#include <SSD1306Brzo.h>
#include <OLEDDisplayUi.h>


class BaseApp {
    public:
        void begin();
        bool update();
        virtual void draw(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) const = 0;
};

#endif
