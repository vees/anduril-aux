# Adventures in Andruil 

## First Attempt

*Goal is to add a run through colored aux modes at the bottom of the primary ramp.*

Added the following line in `cfg-emisar-d4v2.h`:

    #define AUX_LEVELS 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x00,

The first four bits identify the brightness level and the second four bits identify the color 0 through 6. There are special events that kick in for the rainbow and voltage cases on 7 and `else` (none of the previous values), but I didn't want to tempt fate with a dynamic mode/state here.

The 0x00 continued so that this row had 150 values the same as the `PWM1_LEVELS`.

Changed the `PWM1_LEVELS` to read:

    #define PWM1_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,

and then continue on with a normal ramp so that the `set_level` function would be set to `0` while the `rgb_led_update` function could have active lights.

Then to get the `rgb_led_update` function to be called from within the ramp, I added the call to `set_level_and_therm_target` function, which is called if the value of `USE_THERMAL_REGULATION` is set. Otherwise `set_level_and_therm_target` is defined as a call to `set_level` function directly.

Since `set_level` is also used outside the main ramp, not all functions would necessarily also turn off the `rgb_led_update`. This appears in certain issues with the lockout mode where clicking the button disables the aux LED to call a `set_level` of `PWM_LEVELS[0]` which is predictably a value of `0`.

The resulting function looked like this:

    #ifdef USE_THERMAL_REGULATION
    void set_level_and_therm_target(uint8_t level) {
        target_level = level;
        set_level(level);
        #ifdef USE_INDICATOR_LED
        indicator_led(0);
        #elif defined(USE_AUX_RGB_LEDS)
        const uint8_t *my_aux_levels = aux_levels;
        rgb_led_update(pgm_read_byte(my_aux_levels+level), 0);
        #endif

    }
    #endif

The changes are messy but the end run was successful. 

Building from the `Makefile` script called the following functions:

    avr-gcc -DCONFIGFILE=cfg-emisar-d4v2.h -Wall -g -Os -mmcu=attiny1634 -c -std=gnu99 -fgnu89-inline -fwhole-program -DATTINY=1634 -I.. -I../.. -I../../.. -fshort-enums -o anduril.o -c anduril.c
    avr-gcc -Wall -g -Os -mmcu=attiny1634 -fgnu89-inline -o anduril.elf anduril.o
    avr-objcopy --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex anduril.elf anduril.hex
    avr-objdump -Pmem-usage anduril.elf | grep Full
    mv -f anduril.hex anduril.emisar-d4v2.hex

The hex file was loaded to the device using:

    avrdude -p t1634 -c usbasp -u -Uflash:w:anduril.emisar-d4v2.hex

Results: Starting from the "off" mode, pressing the button 1H caused the light to turn off, rapidly flash through the aux modes before finally turning on the primary LED. Working back down the ramp, the lowest mode seems to be dim yellow which is `0x11` not `0x10` so it maybe that we want to kick another 0 value below that to pad against the dim red, or validate that `pgm_read_byte(my_aux_levels+level)` is not an off-by-one error.

## Second Attempt

Some lessons learned from the previous attempt:

- The `cfg-emisar-d4v2.h` file calls the `hwdef-Emisar_D4v2.h` file which contains the hardware definitions, so its still useful to have this file in place to isolate some of the settings even if I copy the `andruil.c` file to edit large portions.
- Large swaths of the code can be removed using `#undef` statements.
- As a nice side effect, I got the new voltage colors of the Anduril 2 build, which was not in the standard hexes.
- The ramp proceeds through the defined `RAMP_LENGTH` of 150 levels very quickly. The aux colors flash by in less than a second.
- Because `set_level_and_therm_target` is used to enable the primary LED (more often `set_level` is used to bring it to zero) its possible to use calls to that function to identify the primary areas of the ramp. In fact, these all occur within the context of `steady_state`.

