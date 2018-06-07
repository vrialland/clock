#include "app_base.hpp"

BaseApp::BaseApp(unsigned int updateInterval) :
    _lastUpdate(0), _updateInterval(updateInterval) {}

bool BaseApp::needsUpdate(unsigned long ms) {
    return ms - this->_lastUpdate >= this->_updateInterval * 1000;
}

bool BaseApp::update(unsigned long ms) {
    if (this->needsUpdate(ms)) {
        Serial.println("Updating...");
        if (this->doUpdate()) {
            this->_lastUpdate = ms;
            return true;
        }
    }
    return false;
}
