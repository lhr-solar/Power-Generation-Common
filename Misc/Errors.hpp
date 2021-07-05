/**
 * Project: Power-Generation-Common
 * File: Errors.hpp
 * Author: Matthew Yu (2021).
 * Created on: 06/12/21
 * Last Modified: 06/29/21
 * File Description: This file describes potential error codes for software
 * exceptions in user programs.
 */
#pragma once

/* Standard Error Codes 0 - 255 (2^8). */
#define ERR_NONE                        0x00 /* No error has occurred. */
#define ERR_UNKNOWN                     0x01 /* Unknown/Undefined error. */
#define ERR_BAD_STATE                   0x02 /* Program defined state is not expected. */
#define ERR_INVALID_MSG_ID              0x20 /* MSG ID was never allocated by user. */
#define ERR_INVALID_MSG_DATA            0x21 /* MSG DATA is formated badly. */
#define ERR_INVALID_MSG_DATA_LEN        0x22 /* MSG DATA length is off. */
#define ERR_UNEXPECTED_MSG_ID           0x23 /* MSG ID was not expected in context. */

/* Extended Error Codes 256 - 65636 (2^16). */
#define ERR_INVALID_PROFILE             0x100 /* Profile has a bad parameter. */
#define ERR_INVALID_VOLTAGE_START       0x101 /* Starting voltage is too low/high. */
#define ERR_INVALID_VOLTAGE_END         0x102 /* Ending voltage is too low/high. */
#define ERR_INVALID_VOLTAGE_CONSISTENCY 0x103 /* Starting voltage is >= ending voltage. */
#define ERR_INVALID_VOLTAGE_RESOLUTION  0x104 /* Voltage step resolution is too low/high. */
#define ERR_INVALID_FIFO_DEQUEUE        0x105 /* Fifo could not dequeue properly. */