This folder includes the KIM-1 assembly listing and generated ROM files.
The KIM-1 ROM is mostly left intact except for a couple of minor changes.
A real KIM-1 system would automatically determine the baud rate when a user hit the rubout key.
In order to be able to get higher baud rates (ie 56700) then the auto-timing routine has to be ignored.
The PSOC captures TTL serial data and returns it to the KIM-1 calling routine.

The ROM data is included within the PSOC5 LP firmware and is here for reference.
