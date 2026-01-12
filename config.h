/* Copyright 2014-2015 Drew Thoreson
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <linux/input.h>
#include "snes.h"

/*
 * Controller definitions.  You may add as many controllers to this list as
 * you like and usnes will automagically poll them.
 *
 * It is a good idea to share CLOCK/LATCH pins between controllers, to reduce
 * latency differences and the amount of polling that has to be done.  But if
 * you share CLOCK/LATCH pins, they must be shared between ALL controllers,
 * otherwise usnes will fall back to polling them individually.
 */

// define a tuple struct for the control AND the event type it goes under
typedef struct {
	unsigned int control;
	int event_type;
} controlmap;

static struct controller {
	controlmap mapping[SNES_NR_BUTTONS];
	unsigned char clock;
	unsigned char latch;
	unsigned char data;
	int mouse_speed;
	int scroll_speed;
} controller[] =
{{
	.mapping = {
		[SNES_R] = {KEY_FORWARD, 0},
		[SNES_L] = {KEY_BACK, 0},

		[SNES_A] = {BTN_RIGHT, 0},
		[SNES_B] = {REL_WHEEL, 1}, // negative for scroll down
		[SNES_X] = {REL_WHEEL, 1}, // positive for scroll up
		[SNES_Y] = {BTN_LEFT, 0},

		[SNES_UP]    = {REL_Y, 1}, // negative for mouse up
		[SNES_DOWN]  = {REL_Y, 1}, // positive for mouse down
		[SNES_LEFT]  = {REL_X, 1}, // negative for mouse left
		[SNES_RIGHT] = {REL_X, 1}, // positive for mouse right

		[SNES_START]  = {KEY_LEFTMETA, 0}, // Windows key
		[SNES_SELECT] = {BTN_MIDDLE, 0}
	},
	.clock = 21,
	.latch = 20,
	.data  = 16,
	.mouse_speed = 5,
	.scroll_speed = 2
},
/* e.g. second controller with shared CLOCK and LATCH pins: */
/*{
	.keymap = {
		[SNES_R] = KEY_Q,
		[SNES_L] = KEY_W,

		[SNES_A] = KEY_E,
		[SNES_B] = KEY_T,
		[SNES_X] = KEY_U,
		[SNES_Y] = KEY_I,

		[SNES_UP]    = KEY_O,
		[SNES_DOWN]  = KEY_P,
		[SNES_LEFT]  = KEY_S,
		[SNES_RIGHT] = KEY_D,

		[SNES_START]  = KEY_F,
		[SNES_SELECT] = KEY_G
	},
	.clock = 21,
	.latch = 20,
	.data  = 12
}*/
};
#define NR_CONTROLLERS (sizeof(controller)/sizeof(*controller))

/*
 * The delay, in milliseconds, that usnes will wait after polling.
 */
#define POLL_MS 60

#endif
