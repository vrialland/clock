#include "app_clock.hpp"


String ClockApp::getDate() const {
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
  String dayStr = String(day());
  String monthStr = months[month() - 1];
  String yearStr = String(year());
  return dayStr + " " + monthStr + " " + yearStr;
}


String ClockApp::getTime() const {
  int hours = hour();
  int minutes = minute();
  String out = "";
  out += hours < 10 ? "0" + String(hours) : String(hours);
  out += ":";
  out += minutes < 10 ? "0" + String(minutes) : String(minutes);
  return out;
}


void ClockApp::draw(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) const {
    display->setFont(Roboto_36);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawStringMaxWidth(x + SCREEN_HALF_X, y, SCREEN_WIDTH, this->getTime());
    display->setFont(Roboto_12);
    display->drawStringMaxWidth(x + SCREEN_HALF_X, y + 39, SCREEN_WIDTH, this->getDate());
}
