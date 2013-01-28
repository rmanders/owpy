owpy
====

1-wire library wrapper in python

version: 1.0

This is a very basic python wrapper or 1wire communication.

the directory src/onewiresdk contains the original 1-wire sdk released from 
Maxim semiconductor. Additional code has been added to this sdk in order
to add functionality for newer 1-wire components as they become available.

There are many devices used to access a 1-wire network. When compiling
owpy, you can change the support for the device used by adding a device
library reference variable in the make file and then changing the 
$(DEVICE) variable to point to it. By default, the device used is the
ds2490 USB dongle. In the future, I would like to be able to compile in
support for all known devvices and simple specify which device on initialization
of owpy within python. 
