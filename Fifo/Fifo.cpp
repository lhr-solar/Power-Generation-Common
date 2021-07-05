/**
 * Project: Power-Generation-Common
 * File: Fifo.cpp
 * Author: Matthew Yu (2021).
 * Organization: UT Solar Vehicles Team
 * Created on: 06/26/21
 * Last Modified: 07/04/21
 * File Description: This file implements a Fifo class, which
 * can be used for message parsing.
 */

/** Includes. */
#include "Fifo.hpp"

Fifo::Fifo(char * buffer, size_t maxCapacity) {
    this->buffer = buffer;
    this->head = 0;
    this->tail = 0;
    this->maxCapacity = maxCapacity;
    this->usedCapacity = 0;
}

size_t Fifo::peek(char* buffer, size_t len) {
    if (isEmpty()) return 0;

    size_t charsRead = 0;
    uint16_t i = tail;
    while (i != head && charsRead < (len-1)) {
        buffer[charsRead] = this->buffer[i];
        i = (i + 1) % maxCapacity;
        ++charsRead;
    }

    return charsRead;
}

bool Fifo::enqueue(char inp) {
    if (isFull()) return false;
                
    buffer[head] = inp;
    head = (head + 1) % maxCapacity;
    ++usedCapacity;

    return true;
}

bool Fifo::dequeue(char& inp) {
    if (isEmpty()) return false;
                
    inp = buffer[tail];
    buffer[tail] = '\0';
    tail = (tail + 1) % maxCapacity;
    --usedCapacity;

    return true;
}

void Fifo::clear(void) {
    head = 0;
    tail = 0;
    usedCapacity = 0;
}

bool Fifo::isFull(void) { return (((head + 1) % maxCapacity) == tail) && (usedCapacity == maxCapacity); }

bool Fifo::isEmpty(void) { return (head == tail) && (usedCapacity == 0);}

size_t Fifo::getUsedCapacity(void) { return usedCapacity; }

void Fifo::_printQueue(void) {
    printf("Head:%i\tTail:%i\t", head, tail);
    for (size_t i = 0; i < maxCapacity; ++i) {
        printf(
            "[%c%i:%c%c]", 
            i == tail ? '*' : '_', 
            i, 
            buffer[i], 
            i == head ? '*' : '_'
        );
    }
    printf("\n");
}
