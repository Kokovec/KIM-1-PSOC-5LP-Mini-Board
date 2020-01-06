Programs (binary files) may be loaded into the Kim-1 system via the TTL serial interface (57600,8,N,1).

The binary files should be in the following format: [4 byte Header][programa data]

The 4 byte header is simply the start and end addresses where the program data will be loaded.

The end address is the address where the last byte of indormation will be stored.

From the serial terminal type "~" (without quotes) and use a serial transfer program to send the raw binary data to the KIM-1.

There's no error checking and the KIM-1 system expects to see all bytes transferred as calculated from the header information.
If the transfer hangs (due to lack of bytes) a reboot is required.
Keep in mind that there's no support for protocol based serial transfers (Kermit, XMODEM, etc).
The data must be transfered byte by byte with no handshaking.

Note: TealTerm can be used to transfer programs to the KIM-1 system although it makes for a lousy terminal emulator.
