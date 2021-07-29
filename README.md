
  # SMV C Decoder
  
## Overview

This small C software decodes messages sent by an  Smart Miniature Vane (SMV) from Simtec AG <https://www.swiss-airdata.com/> and print the result on the terminal. It has been designed to run on a Windows computer and requires the usage of a RS485 to USB converter for SMV-1 or RS232 to USB converter for SMV-2. Contact Simtec for more details or for a preconfigured and assembled cable.

Details about the format used to send the air data can be found in the Datasheet.

The following example shows the output of the decoder to the terminal:

```
2.95° (AOS)
2.88° (AOS)
2.75° (AOS)
2.64° (AOS)
2.49° (AOS)
1.21° (AOS)
0.91° (AOS)
0.77° (AOS)
0.64° (AOS)
0.53° (AOS)
0.42° (AOS)
0.31° (AOS)
0.20° (AOS)
0.14° (AOS)
0.09° (AOS)
0.05° (AOS)
-0.02° (AOS)
-0.08° (AOS)
-0.17° (AOS)
-0.68° (AOS)
-2.59° (AOS)
-2.65° (AOS)
-2.72° (AOS)
```

 ## Usage

 ### Compilation
Simply execute the following command:

```
make compile
```
 ### Execution
 Launch the following command:
```
decode serial-port 
```
Arguments:
- _serial-port_: Serial port on which the swiss air-data computer is connected. 

Example calls:
```
decode COM3
decode COM7
```

 ## Integration

This software has been developed with the goal to ease its reusability as much as possible. 

The core decoder _smv_decoder.c_ and _smv_decoder.h_ has been implemented to run on almost any hardware. It only requires to have the C standard librairies _stdint_, _stdlib_ and _errno_. You can very well take those two files and integrate them in your own code to run on a flight control computer for instance.

 ## Notes

Compiled with gcc version 10.2.0 (GCC) on windows 10 with mingw64 <http://mingw-w64.org/doku.php>.

Example code only. Use at own risk.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Simtec AG has no obligation to provide maintenance, support,  updates, enhancements, or modifications.