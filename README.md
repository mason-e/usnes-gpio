usnes-gpio - RPi SNES controller driver
==============================================

Original Copyright (C) 2014-2015 Drew Thoreson

Addenda in this README by mason-e

About
-----

usnes is a driver for the Super Nintendo controller, connected over GPIO on the
Raspberry Pi.  It uses the Linux uinput interface to emulate a USB input device
from user space.  usnes will work with unmodified SNES controllers, provided
you are able to connect them to the Pi's GPIO pins.

Addendum:

This fork has been modified to support mouse movement. The original version of the driver did not support that due to requiring an `EV_REL` event vs. `EV_KEY` event in the Linux kernel. 

Some things to note:

- There might be some jankiness, as this isn't intended to be a replacement for a good mouse. I made it because I own a Raspberry Pi with broken USB ports, so it's better than nothing in my case.
- I haven't tested with multiple controllers, but kept the support for it that was already in Drew's implementation.

Pinout
------

Below is the pinout for the SNES controller (copied from
http:/www.gamefaqs.com/snes/916396-super-nintendo/faqs/5395).  You will need to
connect the clock, latch and data pins on the controller to GPIO pins on the
Pi, and tell the daemon about the mapping.  This can be done by editing the
`controller` array in config.h.

    ,------------------------------.
    | (1) (2) (3) (4) | (5) (6) (7) )
    '------------------------------`

    Pin    Description    Color of wire in cable
    ---    -----------    ----------------------
    1      +5v            White
    2      Data Clock     Yellow
    3      Data Latch     Orange
    4      Serial Data    Red
    5      ?              No wire
    6      ?              No wire
    7      Ground         Brown

NOTE: I have had success driving controllers at 3.3v, but as always YMMV.

Do not connect pin 1 to 5v unless you know what you are doing.  You may break
your Pi.  I take no responsibility for what happens.

Addendum:

You will see in the config file that it has pin numbers like 21, 20, 16. These are the GPIOXX numbers, _not_ the pin numbers from, e.g. 1-40 that you will often see on Raspberry Pi documentation.

Configuration
-------------

By default, usnes emulates a single controller with the following 
mapping:

    SNES BUTTON    CONTROL
    -----------    ---
    A              Right click
    B              Scroll wheel down
    X              Scroll wheel up
    Y              Left click
    L              Back
    R              Forward
    D-Pad Up       Mouse move up
    D-Pad Down     Mouse move down
    D-Pad Left     Mouse move left
    D-Pad Right    Mouse move right
    Start          Windows Key (Meta)
    Select         Middle click

This can be changed by editing the `controller` array in config.h prior to
compiling.

Addendum:

Possible event codes can be found in the Linux kernel [input-event-codes.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h) file. These must be properly designated as `EV_KEY` or `EV_REL` events to work right. The speed value on `EV_REL` is user configurable and affects how quickly the mouse moves/scrolls. 

For mouse scroll, I found `REL_WHEEL_HI_RES` to work for me. I believe the speed values for this need to be fractions of 120. `REL_WHEEL` is also another option, but in my testing, even with the speed set to 1 this scrolled too much at once.

Build/Install
-------------

The bcm2835 library is a dependency.  It should be installed prior to building.

    $ make
    # make install

Addendum:

bcm2835 can be installed by obtaining it from https://www.airspayce.com/mikem/bcm2835/

Then run (version may vary):

    tar zxvf bcm2835-1.75.tar.gz
    cd bcm2845-1.75
    ./configure
    make
    sudo make check
    sudo make install

Even after I had bcm2835, I failed due to a missing directory, but was able to get past it by making an empty directory `mkdir /usr/local/share/man/man1`

Running
-------

    # usnes