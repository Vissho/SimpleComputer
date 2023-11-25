# SimpleComputer
The model of the simplest computer Simple Computer 

## Architecture of the computer Simple Computer
The architecture of Simple Computer includes the following functional blocks:
* RAM
* external devices
* central processing unit

![](https://i.imgur.com/rfW6boZ.png)

## Management Console
The management console interface is shown in Figure 1. It contains the following areas:
* “Memory” – the contents of the RAM of a Simple Computer.
* “Accumulator” – the value stored in the battery;
* "instructionCounter" – the value of the "command counter" register;
* “Operation" – the result of decoding the operation;
* "Flags" – status of the flag register ("P" - overflow during the operation, "0" - division error by 0, "M" - error going beyond the memory boundaries, "T" - ignoring clock pulses, "E" - invalid command specified);
* “Cell" – the value of the allocated memory cell in the “Memory” area (used for mapping);
* “Keys" – function keys hint;
* “Input/Otput" is the area used by Simple Computer during the execution of the program to enter information from the keyboard and display it on the screen.

The contents of the memory cells and registers of the CPU are output in decoded
form. At the same time, the "+" sign corresponds to the value 0 in the "command attribute" field, the next two
digits are the command number and then the operand in hexadecimal notation.

The user has the ability to use the cursor control keys to select
RAM cells and set values for them. By pressing the "F5" key, the user can set the value
of the battery, "F6" - the "command counter" register. The user can save the contents of the memory (in binary
form) to a file or upload it back by pressing the "l", "s"
keys respectively (after clicking in the Input/Output field, the user is prompted to enter the file name). You can start
the program for execution (set the value of the "ignore timer clock" flag to 0) with
using the “r” key. During the execution of the program, editing memory and changing
register values is not available. To execute only the current command, the user can
press the “t” key. You can reset the contents of the memory and set the "default" values to the registers
by pressing the "i" key.

![](https://i.imgur.com/wOxlxSL.png)
