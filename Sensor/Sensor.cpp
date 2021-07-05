/**
 * Project: Power-Generation-Common
 * File: Sensor.cpp
 * Author: Matthew Yu (2021).
 * Organization: UT Solar Vehicles Team
 * Created on: 07/04/21
 * Last Modified: 07/04/21
 * File Description: Implementation file that implements an interface (or
 * abstract class) for sensors.
 * 
 * The proposed sensor interface uses an independent thread to
 * execute non ISR interruptible routines. Routines can be initiated
 * by using an allocated LowPowerTicker to manage a periodic flag. 
 */

/** Includes. */
#include "Sensor.hpp"

Sensor::Sensor(void) {
    data = 0.0;
    enable = false;
    threadSampling.start(this->_loop);
}

void Sensor::start(std::chrono::milliseconds periodMs) {
    enable = false;
    tickerEnable.attach(this->_setEnable, periodMs);
}

void Sensor::stop(void) {
    tickerEnable.detach();
    enable = false;
}

void Sensor::kill(void) {
    threadSampling.terminate();
    tickerEnable.detach();
}

float Sensor::getData(void) { return data; }

void Sensor::_loop(void) {
    while (true) {
        if (enable) {
            sampleData();
            enable = false;
        }
    }
}

void Sensor::_setEnable(void) {
    enable = true;
}
