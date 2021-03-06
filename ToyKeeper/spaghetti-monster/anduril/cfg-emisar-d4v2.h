// Emisar D4 config options for Anduril
#include "hwdef-Emisar_D4v2.h"
// ATTINY: 1634

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
// it also has an independent LED in the button
#undef USE_BUTTON_LED
// the aux LEDs are front-facing, so turn them off while main LEDs are on
// TODO: the whole "indicator LED" thing needs to be refactored into
//       "aux LED(s)" and "button LED(s)" since they work a bit differently
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif
// enable blinking aux LEDs
#define TICK_DURING_STANDBY
#define STANDBY_TICK_SPEED 3  // every 0.128 s
//#define STANDBY_TICK_SPEED 4  // every 0.256 s
//#define STANDBY_TICK_SPEED 5  // every 0.512 s

#define RGB_LED_OFF_DEFAULT 0x18  // low, voltage
#define RGB_LED_LOCKOUT_DEFAULT 0x20  // red, high
#define RGB_RAINBOW_SPEED 0x03  // half a second per color

// copied from original D4, since it's also a FET+1 and has the same host
// ../../bin/level_calc.py 1 65 7135 1 0.8 150
// ... mixed with this:
// ../../bin/level_calc.py 2 150 7135 4 0.33 150 FET 1 10 1500
#define RAMP_LENGTH 150
#define PWM1_LEVELS 1,1,2,2,3,3,4,4,5,6,7,8,9,10,12,13,14,15,17,19,20,22,24,26,29,31,34,36,39,42,45,48,51,55,59,62,66,70,75,79,84,89,93,99,104,110,115,121,127,134,140,147,154,161,168,176,184,192,200,209,217,226,236,245,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,5,7,8,9,11,12,14,15,17,19,20,22,24,25,27,29,31,33,35,37,39,41,43,45,48,50,52,55,57,59,62,64,67,70,72,75,78,81,84,87,90,93,96,99,102,105,109,112,115,119,122,126,129,133,137,141,144,148,152,156,160,165,169,173,177,182,186,191,195,200,205,209,214,219,224,229,234,239,244,250,255
#define MAX_1x7135 65

#define DEFAULT_LEVEL 65

#define HALFSPEED_LEVEL 14
#define QUARTERSPEED_LEVEL 6

#define RAMP_SMOOTH_FLOOR 1
#define RAMP_SMOOTH_CEIL 120
// 10, 28, 46, [65], 83, 101, 120
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// stop panicking at ~30% power or ~1200 lm
#define THERM_FASTER_LEVEL 105

// easier access to thermal config mode, for Emisar
#define USE_TENCLICK_THERMAL_CONFIG

#define THERM_CAL_OFFSET 5

#ifdef USE_MUGGLE_MODE
#undef USE_MUGGLE_MODE
#endif

#ifdef USE_MOMENTARY_MODE
#undef USE_MOMENTARY_MODE
#endif

#ifdef USE_TACTICAL_STROBE_MODE
#undef USE_TACTICAL_STROBE_MODE
#endif 

#ifdef USE_BIKE_FLASHER_MODE
#undef USE_BIKE_FLASHER_MODE
#endif

#ifdef MOON_DURING_LOCKOUT_MODE
#undef MOON_DURING_LOCKOUT_MODE
#endif

#define USE_PARTY_STROBE_MODE
#define USE_LIGHTNING_MODE
#define USE_CANDLE_MODE

#define STROBE_ADJUST_SPEED_DIV 31
