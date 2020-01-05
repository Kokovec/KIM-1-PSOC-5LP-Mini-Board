# KIM-1-PSOC-5LP-Mini-Board
A KIM-1 system built around a Cypress PSOC 5LP (Schmartboard PSOC 5LP Dev Board)

## Description: ##
This is a KIM-1 system clone that includes code (firmware), schematics and PCB.
It's designed to run most of the programs that can be found in The First Book of KIM.
This KIM-1 clone emulates a 6502 and faithfully runs the original firmware.
This KIM-1 board has somewhat reduced functionality as is doesn't include I/O or a tape interface.
It uses a touchscreen inteface instead of a matrix keypad.

## Features: ##
This KIM-1 clone includes:
  * 1 MHz clock operation
  * 6502 emulator (cycle accurate)
  * Partly emulated 6530 (x2) which includes:
    * ROM area
    * RAM area
    * Interval Timer (with frequency divider)
  * 32K RAM expansion
  * 7-Segment display
  * Non-amplified audio out (for the program Music Box)
  * TTL serial input (terminal keyboard / loading programs)
  * Touchscreen interface (Nextion Enhanced NX4024K032)
