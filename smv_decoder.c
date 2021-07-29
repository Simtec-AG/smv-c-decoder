/*
* © 2021 Simtec AG. All rights reserved.
* Company Confidential
*/

#include "smv_decoder.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>


/** @brief Carriage return */
#define CR ((char)0x0D)

/** @brief Maximum size in byte of the buffer needed to decode one message */
#define MAX_BUFFER_LENGTH 12

/** 
 * @brief Decodes an entire message received from a smart miniature vane.
 * @param[in]   raw_msg         Data received by the smv.
 * @param[in]   raw_msg_length  Length of the message in byte.
 * @param[out]  angle_data      Pointer that will contain the decoded angle data.
 * @return smv_status_t         SMV_SUCCESS it the message has been decoded without error, 
 *                              SMV_ERROR otherwise.
 */
static smv_status_t smv_decode_msg(uint8_t raw_msg[], uint8_t raw_msg_length, angle_data_t* angle_data)
{
    smv_status_t status = SMV_ERROR;
    errno = 0;

    if (raw_msg[0] == 'A')
    {
        angle_data->type = ANGLE_AOA;
    }
    else
    {
        angle_data->type = ANGLE_AOS;
    }

    // Convert the string in integer value
    raw_msg[raw_msg_length] = '\0';
    int32_t value_int = strtol((char *)&raw_msg[1], NULL, 10);

    // Verify if an error ocurred during the string to int convertion
    if(errno == 0)
    {
        status = SMV_SUCCESS;
        angle_data->value = ((float) value_int) / 100;
    }

    return status;
}

smv_status_t smv_decode(char raw_data, angle_data_t* angle_data)
{
    static uint8_t buffer[MAX_BUFFER_LENGTH] = {0};
    static uint8_t pos = 0;

    smv_status_t status = SMV_ERROR;

    if ((raw_data == 'A') || (raw_data == 'B'))
    {
        // A SOH marks the beggining of a message
        buffer[0] = (uint8_t)raw_data;
        pos = 1;
        status = SMV_PENDING;
    }
    else if ((pos > 0) && (pos < MAX_BUFFER_LENGTH))
    {
        // Store the byte received
        buffer[pos] = (uint8_t)raw_data;

        if (raw_data == CR)
        {
            // A carriage return marks the end of a message, decode
            status = smv_decode_msg(buffer, pos + 1, angle_data);
            pos = 0;
        }
        else
        {
            // Current message is not totally received
            pos++;
            status = SMV_PENDING;
        }
    }

    return status;
}
