This folder includes the KIM-1 assembly listing and generated ROM files.
The KIM-1 ROM is mostly left intact except for a couple of minor changes.
A real KIM-1 system would automatically determine the baud rate when a user hit the rubout key.
In order to be able to get higher baud rates (ie 56700) the auto-timing routine has to be ignored.
The PSOC5 LP captures TTL serial data and returns it to the KIM-1 calling routine.

Changes were made to a few lines of the KIM-1 startup code in the 6530-002 ROM

DET1
BIT   SAD       		;TEST
;BNE   START     		;KEYBD SSW TEST
JMP   START     		;KEYBD SSW TEST *************
NOP
;BMI   DET1      		;START BIT TEST
LDA   #$FC

The ROM data is included within the PSOC5 LP firmware and is here for reference.
