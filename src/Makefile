# Native linux (x86) compiler and linker
CC = gcc
AR = ar

#----------------------------------------------------------
# Include paths for local sources
#----------------------------------------------------------
PYTHON = /usr/include/python2.7
OWCOMMON = ./onewiresdk/common

#----------------------------------------------------------
# Variables for specific 1-wire interface device libraries
#----------------------------------------------------------
DS2490 = ./onewiresdk/lib/other/libUSB/

#----------------------------------------------------------
# General make config variables
#----------------------------------------------------------
DEVICE = $(DS2490)
INCL = -I$(PYTHON) -I$(OWCOMMON) -I$(DEVICE)
CFLAGS = -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC $(INCL)
LFLAGS = -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-Bsymbolic-functions -lusb $(INCL)
VERSION = 0.0.1

X86OBJS = x86/cnt1d.o x86/temp10.o x86/temp28.o x86/tempall.o x86/maxq1004.o

#----------------------------------------------------------
# Build targets
#----------------------------------------------------------

TARGETS = x86

#----------------------------------------------------------
# Main make section
#----------------------------------------------------------

.SECONDEXPANSION:

all: $(TARGETS)

x86: x86/owpy

x86/owpy: owpy.c x86/owmasterobjs $(X86OBJS)
	$(CC) $(LFLAGS) $< x86/owmasterobjs $(X86OBJS) -o x86/owpy.so

x86/touch:
	mkdir -p x86
	touch x86/touch

x86/%.o: $(OWCOMMON)/%.c x86/touch
	$(CC) $(CFLAGS) -c $< -o x86/$*.o

x86/owmasterobjs: $(DEVICE)/*.c x86/owerr.o x86/ioutil.o x86/crcutil.o x86/touch
	$(CC) $(CFLAGS) -c $(DEVICE)/*.c 
	$(AR) r x86/owmasterobjs *.o x86/owerr.o x86/ioutil.o x86/crcutil.o
	rm -f *.o
clean:
	rm -rf x86

