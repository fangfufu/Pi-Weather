ifeq ($(shell uname -m),armv6l)
  CC = cc
else
  CC = arm-linux-gnueabi-gcc-4.7
endif

CFLAGS = -std=gnu99 -Wall -Wextra -O2 -pedantic

ifneq ($(RPI_REV1),)
CFLAGS += -DRPI_REV1
endif

LDFLAGS =
COMMON_SOURCES = lowlevel.c
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)
INSTALL_PATH = /usr/local/bin
STICKY_BIN = WB-Water WB-Sensor
NORMAL_BIN = hwclock
BIN = $(NORMAL_BIN) $(STICKY_BIN)

all: $(BIN)

hwclock: hwclock.o rtc.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

WB-Water: WB-Water.o darlington.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

WB-Sensor : WB-Sensor.o sensors.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

depend: .depend
.depend: *.c
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend
include .depend

.PHONY: clean
clean:
	rm *.o $(BIN) -rf

.PHONY: install
install:
	install -m 0755 $(NORMAL_BIN) /usr/local/bin
	install -m 4755 $(STICKY_BIN) /usr/local/bin

.PHONY: uninstall
uninstall:
	rm -rf $(foreach file, $(BIN), /usr/local/bin/$(file))
