
#!/bin/bash
DUDE_PATH="/home/evkuz/lit/arduino-1.8.13/hardware/tools/avr/bin/avrdude"
DUDE_CONF="/home/evkuz/lit/arduino-1.8.13/hardware/tools/avr/etc/avrdude.conf"
 #/home/evkuz/lit/arduino-1.8.13/hardware/tools/avr/bin/avrdude
#HEXDATA="/home/evkuz/lit/ek_02.hex"
#HEXDATA="/tmp/arduino_build_708043/Blink.ino.hex"
HEXDATA="/home/evkuz/avr/0_HiWonder/firmware/Learm_init_clamp.ino.with_bootloader.hex"
#HEXDATA="/home/evkuz/avr/0_HiWonder/firmware/Learm_init_clamp.ino.hex"
#HEXDATA="/tmp/arduino_build_163722/Learm_init_clamp_sit.ino.hex"
#HEXDATA="/tmp/arduino_build_529768/Blink.ino.hex"
$DUDE_PATH -C$DUDE_CONF -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:$HEXDATA:i 

