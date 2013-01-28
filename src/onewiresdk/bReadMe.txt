Public Domain 1-Wire Net Functions
Version 3.10
3/23/06
Copyright (C) 2006 Dallas Semiconductor


Here is the file structure for the build zip file.

CONTENTS:

*    lib (1-Wire Net library code sets)
   *    userial - Code set based on Universial Serial chip (DS2480B)
   *    general - Code set based on 1-Wire link-level functions
   *    misc_micro - Formerly in the TMEX kit, written for example programs
                using assembly language
   *    other - libusb set based on USB adapter (DS9490)

*    apps (application examples)
   *    atodtst - finds and display the value for channels A,B,C,D on the
                  DS2450 Quad A/D Converter
   *    counter - reads the DS2423 counter value of the associated memory page
   *    coupler - tests the DS2409 commands and searches for the DS2409 and the
                  devices on the branch of the DS2409
   *    fish - Read, write, format and display the file system on a 1-Wire
               memory device.
   *    gethumd - Measures the humidity using the DS2438.
   *    humalog - Sets up the DS1923 for mission or reads the current mission
                  log.  Also can set the passwords.
   *    mweather - 1-Wire Weather Station example, supports versions of the
                   Weather Station
   *    memutil - Minimal 1-Wire application to list the devices present on
                  the default 1-Wire Adapter/Port.
   *    sa_ps - Uses a DS1991 for software authorization.
   *    sa_sha - Uses the DS1961S or the DS1963S for software authorization.
   *    sa_time - Uses the DS1994 for software authorization timeouts.
   *    shaapp - 1-Wire application for using DS1961 functions.
   *    shadebit - DS1963/DS1961 SHA iButton monetary demo.  Initializes the
                   the dedicated co-processor DS1963 and the user performs
                   authenticated secure money debits using DS1963/DS1961.
   *    swtduo - performs various operations on the DS2413.
   *    swtloop - performs various operations on the Dual Addressable Switch
   *    swtmain1c - test application that performs various opertions for DS23E04
   *    swtsngl - turns the DS2405 switch on & off and reads the on/off status
   *    temp - finds and displays the temperature measurement for the
               DS1920/DS1820
   *    thermo - DS1921 Thermochron download and mission example application
   *    tstfind - loop to find all 1-Wire devices on Net

*    common (common files to all the applications)

*    builds (contains the primary build for the download)


INFORMATION:

The best source of information about 1-Wire
devices
including iButtons is Dallas Semiconductor's
iButton web site at:
http://www.ibutton.com/

Dallas Semiconductor/Maxim's main web site:
http://www.maxim-ic.com/

