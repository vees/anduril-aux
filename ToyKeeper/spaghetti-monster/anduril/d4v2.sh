avr-gcc -DCONFIGFILE=cfg-emisar-d4v2.h -Wall -g -Os -mmcu=attiny1634 -c -std=gnu99 -fgnu89-inline -fwhole-program -DATTINY=1634 -I.. -I../.. -I../../.. -fshort-enums -o anduril.o -c anduril.c
avr-gcc -Wall -g -Os -mmcu=attiny1634 -fgnu89-inline -o anduril.elf anduril.o
avr-objcopy --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex anduril.elf anduril.hex
avr-objdump -Pmem-usage anduril.elf | grep Full
mv -f anduril.hex anduril.emisar-d4v2.hex
