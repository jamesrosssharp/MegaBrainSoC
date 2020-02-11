== MegaBrain SoC ==

Making a custom instruction set and compiler toolchain for it turned out to be 
a complete pain the proverbial, although I did learn a lot about lexers and 
parsers and compilers in general doing it.
    So I decided I wanted a 32 bit platform anyway so I decided to use an 
existing ISA, i.e. thumb, and specifically, the Cortex-M0 instruction set.
    First goal: make an emulator for the Cortex-M0 instruction set and create
executable, emulatable programs for it. Hello world should suffice. A simple 
memory mapped UART peripheral is all that is required. - COMPLETE
    Second Goal: Add in SD card peripheral, to support boot from SD card. 4kB boot rom will have enough code to read in boot sectors into memory and kick off boot from card.
    Next goal: start emulating the hardware required for a simple 2d/3d 
gaming platform. First, a simple blitter engine. Then add sprite channels, and tile channels. Then basic 3D primitives, support for index and vertex buffers, and basic texturing.
    Fourth goal: write several games including JPTA, Bloodlust, and Kraptor, as well as a doom clone.
    Finally: start on the HDL... I will use verilog, just for fun.


