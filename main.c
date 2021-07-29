/*
 * 2013-2021 (c) Simtec AG
 * All rights reserved
 * 
 * Read a serial port on which a smv probes from Simtec AG send data, and print the 
 * decoded data to the terminal.
 * Use a RS485 or RS232 to USB converter. Contact Simtec 
 * for more details or for a preconfigured and assembled cable.
 * 
 * Compiled and tested with MinGW (gcc)
 * http://sourceforge.net/projects/mingwbuilds/
 *
 * Example code only. Use at own risk.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Simtec AG has no obligation to provide maintenance, support,
 * updates, enhancements, or modifications.
 */

#include "smv_decoder.h"
#include "serial.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/**@brief baudrate at which the serial port is read */
#define BAUDRATE 115200

/** @brief Print the help menu of this decoder */
static void print_help()
{
    printf("\n");
    printf("A simple terminal program to print simtec angle messages from smart miniature vanes\n");
    printf("(c) 2021, Simtec AG\n");
    printf("\n");
}

/** @brief Print a decoded angle to the serial */
void print_message(angle_data_t angle)
{

    const char deg = (char)0xF8;
    printf("%3.2f%c ", angle.value, deg);

    if (angle.type == ANGLE_AOA)
    {
        printf("(AOA)\n");
    }
    else
    {
        printf("(AOS)\n");
    }
}

/** @brief Decode and print a smv message */
static void decode_and_print_message(char data)
{
    angle_data_t angle;
    smv_status_t status = smv_decode(data, &angle);

    if (status == SMV_SUCCESS)
    {
        print_message(angle);
    }
    else if (status == SMV_ERROR)
    {
        printf("Error decoding the message !\n");
    }
}

int main(int argc, char **argv)
{
    int32_t return_code = EXIT_FAILURE;
    print_help();
    serial_port_t adc_serial =
        {
            .baudrate = BAUDRATE,
            .com_port = "\\\\.\\",
            .windows_handle = NULL
        };

    if (argc > 1)
    {
        strcat(adc_serial.com_port, argv[1]);

        if (serial_open(&adc_serial) == EXIT_SUCCESS)
        {
            printf("Starting on %s @ B%d\n", adc_serial.com_port, adc_serial.baudrate);
            printf("Hit any key to exit\n\n");

            while (!kbhit())
            {
                char data = 0;
                if (serial_get_data(&adc_serial, &data) == EXIT_SUCCESS)
                {
                    decode_and_print_message(data);
                }
            }

            serial_close(&adc_serial);
        }
        else
        {
            printf("Couldn't open %s", adc_serial.com_port);
        }
    }
    else
    {
        printf("Error, The serial port needs to be passed as an argument! \n");
        printf("E.g.: COM1, COM2, ... \n\n");
    }

    return return_code;
}
