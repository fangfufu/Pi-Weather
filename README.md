Pi-Weather
==========
@mainpage

Introduction
------------
This is a set of user space program for Web4Robot's Raspberry Pi Weather Board.

You can buy one of the expansion board at:
http://www.web4robot.com/PiWeather.html

Programs
--------
* hwclock - an hwclock replacement. It is used to replace the hwclock in util-linux.
* WB-Sensor - a program to read the onboard sensor data.
* WB-Water - a program to turn on all the Darlington transistors in order to drive my water pump.

### Program for general use
#### hwclock
If you are using Debian, you can use this copy of hwclock to synchronise time
by editing /etc/init.d/hwclock.sh. You need to replace all instance of
/sbin/hwclock by /usr/local/bin/hwclock.

### Program for my own use
These programs were written for my own use, so they might not be suitable for
your own set up. However they should serve as good examples.

#### WB-Sensor
I wrote this program for myself. At my home, the DS18B20 sensor on connector 1
is in my room, while the sensor on connector 2 is outdoor. Please edit the
source file if you want to change their name.

#### WB-Water
I connected all the Darlington transistors together in parallel to drive my
water pump. It takes exactly 14 seconds to fill a cup of water on in my set up.

Installation
------------
You can install the program by issuing the following commands:

    make
    sudo make install

Please note that the compilation stage can be done on a Debian machine if you
have installed gcc-4.7-arm-linux-gnueabi from the Emdebian repository.

If you have Raspberry Pi Revision 1, you should replace the 'make' with:

    make RPI_REV1=1

Dependency
----------
This library/program depends on kernel module i2c-dev. You can load the module
by typing in:

    modprobe i2c-dev

Alternatively you can edit /etc/modules.

Uninstallation
--------------
To uninstall type in the following in your terminal:

    sudo make uninstall

Additional Information
----------------------
### Header files
Here is a brief description of what each header file do:
* darlington.h: functions related to controlling the Darlington array.
* lowlevel.h: low level functions related to the expansion board.
* rtc.h: functions related to the onboard Real Time Clock
* sensors.h functions related to the onboard sensors.

### Initialisation
To initialise the expansion board, you need to include lowlevel.h.
Initialisation process is done by calling exp_open().

Copyright
---------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see {http://www.gnu.org/licenses/}.
