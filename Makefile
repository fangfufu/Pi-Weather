ifeq ($(shell uname -m),armv6l)
  CC = cc
else
  CC = arm-linux-gnueabi-gcc-4.7
endif

CFLAGS = -std=gnu99 -Wall -Wextra -O2 -pedantic
LDFLAGS =
COMMON_SOURCES = lowlevel.c
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)
INSTALL_PATH = /usr/local/bin
EXECUTABLE = Pi-Water

all: $(EXECUTABLE)

Pi-Water: Pi-Water.o darlington.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

depend: .depend
.depend: *.c
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend
include .depend

.PHONY: clean
clean:
	rm .depend *.o $(EXECUTABLE) -rf

.PHONY: install
install:
	install -m 0755 $(EXECUTABLE) /usr/local/bin

.PHONY: uninstall
uninstall:
	rm -rf /usr/local/bin/$(EXECUTABLE)
