#!/bin/bash

avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -U hfuse:r:m328p_hfuse.txt:h -U lfuse:r:m328p_lfuse.txt:h -U efuse:r:m328p_efuse.txt:h
