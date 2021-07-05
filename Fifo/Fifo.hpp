/**
 * Project: Power-Generation-Common
 * File: Fifo.hpp
 * Author: Matthew Yu (2021).
 * Organization: UT Solar Vehicles Team
 * Created on: 06/26/21
 * Last Modified: 07/04/21
 * File Description: This file declares a Fifo class, which
 * can be used for message parsing.
 */

/** Includes. */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

class Fifo {
    private:
        char * buffer;
        size_t head;
        size_t tail;
        size_t maxCapacity;
        size_t usedCapacity;

    public:
        /**
         * Instantiates a new FIFO.
         * @param[in] buffer Reference to the buffer used by the FIFO.
         * @param[in] maxCapacity Capacity of the buffer.
         */
        Fifo(char * buffer, size_t maxCapacity);

        /**
         * Peek at the first <len> characters in the buffer.
         * 
         * @param[out] buffer External buffer to read characters into.
         * @param[in] len Length of external buffer and number of characters to
         *                read.
         * @param[in] idx Starting index to read at.
         * @return Number of characters looked at in the buffer.
         */
        size_t peek(char* buffer, size_t len);

        /**
         * Enqueues a character in the buffer if the buffer is not full.
         * 
         * @param[in] inp Input character to put into the buffer.
         * @return true if character was enqueued successfully.
         */
        bool enqueue(char inp);

        /**
         * Dequeue and returns first character in the buffer if the buffer is
         * not empty.
         * 
         * @param[out] inp Output character address to read character into.
         * @return true if character was dequeued successfully.
         */
        bool dequeue(char& inp);

        void clear(void);
        bool isFull(void);
        bool isEmpty(void);
        size_t getUsedCapacity(void);
    
#ifdef DEBUG
    public:
#else
    private:
#endif
        /**
         * Prints the queue in order of the buffer allocation.
         * The current tail element is prefixed with '*' and the 
         * current head element is postfixed with '*'.
         */
        void _printQueue(void);
};


int testFifo() {
    char buffer[5] = { 0 };
    Fifo fifo = Fifo(buffer, 5);
    fifo._printQueue();
    fifo.enqueue('h');
    fifo.enqueue('e');
    fifo.enqueue('y');
    fifo.enqueue('o');
    if (!fifo.enqueue('!')) printf("Queue is full!\n");
    
    char out;
    fifo.dequeue(out);
    fifo.dequeue(out);
    fifo.dequeue(out);
    fifo.dequeue(out);
    if (!fifo.dequeue(out)) printf("Queue is empty!\n");
    
    fifo.enqueue('a');
    fifo.enqueue('b');
    fifo.enqueue('c');

    char buffer2[5] = { 0 };
    printf("Read %i chars: %s\n", fifo.peek(buffer2, 5), buffer2);
    return 0;
}
