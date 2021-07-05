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
 * Users can either grab the data directly using getData or use an EventQueue
 * to automatically process the sample (e.g. sending it out to COM. receivers).
 */
#pragma once

/** Includes. */
#include "mbed.h"

class Sensor {
    protected:
        float data;
        LowPowerTicker tickerEnable;
        Thread threadSampling;
        bool enable;
        EventQueue * queue;
        void (*processFnc)(float);

    public:
        /** Instantiates a new Sensor object. */
        Sensor(void);

        /**
         * Instantiates a new Sensor object that pushes a function call to
         * an EventQueue upon completing a sample.
         * 
         * @param[in] queue Reference to the queue to push events to.
         * @param[in] processFnc Callback that is pushed to the queue.
         *            Must have an api of uint16_t msgId and float data.
         */
        Sensor(EventQueue *queue, void (*processFnc)(float data));

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
    
    protected:
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
