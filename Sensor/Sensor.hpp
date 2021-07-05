/**
 * Project: Power-Generation-Common
 * File: Sensor.hpp
 * Author: Matthew Yu (2021).
 * Organization: UT Solar Vehicles Team
 * Created on: 07/04/21
 * Last Modified: 07/04/21
 * File Description: Header file that defines an interface (or abstract class)
 * for sensors.
 * 
 * The proposed sensor interface uses an independent thread to
 * execute non ISR interruptible routines. Routines can be initiated
 * by using an allocated LowPowerTicker to manage a periodic flag. 
 */

/** Includes. */
#include "mbed.h"

class Sensor {
    private:
        float data;
        LowPowerTicker tickerEnable;
        Thread threadSampling;
        bool enable;

    public:
        /** Instantiates a new Sensor object. */
        Sensor(void);

        /** 
         * Starts the sensor sampling routine at a fixed period, in ms.
         * 
         * @param[in] periodMs Sample period. Firm real time.
         * @note The sample period is a suggestion and is only firm real time.
         *       If the implementation of sampleData takes longer than the
         *       sample period to execute, then sampleData will only occur on
         *       the next sample period.
         */
        void start(std::chrono::milliseconds periodMs);

        /** Stops the sample events. */
        void stop(void);

        /** 
         * Terminates the sensor execution thread entirely. Terminating the
         * execution thread means that calling the start() or stop() routines
         * will do nothing meaningful. The last sample value can be retrieved
         * via getData().
         */
        void kill(void);

        /**
         * Retrieves the last sensor sample.
         * 
         * @return float Last sensor sample.
         */
        float getData(void);
    
    private:
        /** 
         * User defined implementation to interrogate the sensor and retrieve
         * the latest sample data. 
         */
        virtual void _sampleData(void) = 0;

        /** Sensor execution loop. */
        void _loop(void);

        /** Enable the next _sampleData call. */
        void _setEnable(void);
};
