/**
* This module decodes messages received by a smart miniature vane through RS232 or RS485.
*
* © 2021 Simtec AG. All rights reserved.
* Company Confidential
*
* Compiled and tested with gcc version 8.1.0 (x86_64-posix-seh-rev0, Built by MinGW-W64 project)
*
* Example code only. Use at own risk.
*
* This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* Simtec AG has no obligation to provide maintenance, support,  updates, enhancements, or modifications.
*/

#ifndef SMV_DECODER_H
#define SMV_DECODER_H

#include <stdint.h>

/** @brief Type of angle that has been measured by the smart miniature vane*/
typedef enum
{
    ANGLE_AOA,  /**< Angle of attack */
    ANGLE_AOS   /**< Angle of sideslip */
} angle_type_t;

/** @brief Decoded data sent by a smart miniature vane */
typedef struct
{
    angle_type_t type;
    float value;
} angle_data_t;

/** @brief Status of the smv decoder */
typedef enum
{
    SMV_PENDING = 0,    /**< No complete message has been decoded yet*/
    SMV_SUCCESS = 1,    /**< One complete data message has been decoded */
    SMV_ERROR = 2       /**< An error happened during the decoding of the message */
} smv_status_t;

/**
 * @brief Decodes a message transmitted by a smart miniature vane from Simtec AG.
 * This function shall be called everytime a new byte has been received.
 * If the byte is the last of a message and this message was decoded successfully, SMV_SUCCESS will be 
 * returned and the angle data will contained the decoded angle.
 * If the message is not fully decoded yet, SMV_PENDING will be returned.
 * If there was an error decoding the message, SMV_ERROR will be returned.
 *
 * @param[in]   raw_data    Raw 8 bits data received by a smv module
 * @param[out]  angle_data  Decoded angle message received by the smv module
 * 
 * @return Status of the decoder.
 */
smv_status_t smv_decode(char raw_data, angle_data_t* angle_data);

#endif
