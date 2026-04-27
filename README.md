# Info pre vedúceho
Dobrý deň. 

Tento repozitár obsahuje momentálnu verziu mojej BP pre Vašu kontrolu. Na nasledujúcich miestach nájdete
všetko dôležité:
- okomentované šablóny základných prípadov použitia sú v súbore `\examples\posix_demo\use_cases.c`. Poprosil by
som Vás, aby ste prípadnú kontrolu začali tam: ak som niečomu dôležitému nepochopil alebo mi niečo podstatné uniklo,
z toho súboru to hneď odhalíte
- dokumentácia (v angličtine) sa nachádza buď v tomto súbore alebo v adresári `docs` *(je potrebné ju vygenerovať)*
- zdrojové súbory sa nachádzajú v adresári `\src`
- prípady použitia a testy som robil na simulovanom  MCU, ktorého pseudo port nájdete v adresári `\platform\posix\`
- Opísaná aplikácia, ktorá bola testovaná na doske FRDM-KL27z sa nachádza v adresári `\examples\frdm_kl27z_demo`
Ak pri kontrole narazíte na nejaký vážny nedostatok, budem vďačný, ak mi dáte vedieť. Inak môžeme všetko prediskutovať
na ďalšom stretnutí.


Michal Židzik


# Context library
**Author:** Michal Zidzik
**Date:** 2025 - 2026

Purpose of this library is to provide abstract layer over context management functions 
for **embedded systems**. It provides functions for protecting, storing and loading 
memory areas filled with sensitive data with expected usage being the situation when
embedded device is put in some power saving mode (SLEEP, STOP and many others). 

Target audience is embedded developers who need to include some basic memory protection 
in their software and are willing to sacrifice bit of time learning (*and probably porting*)
new library. I also hope that it can provide a bit of insight and serve as a tool for learning
memory management on embedded systems. Library is open source and you are welcome to change whathever
you want about it.

Library was written in C(TODO standard) and uses CMake(TODO standard) as building tool. Apart from this file,
doxygen documentation for it has been created. Library is also described to the great detail in my bachelors thesis,
but that is written in Slovak language.

*This library was written as part of my bachelors thesis for Faculty of information technology on*
*Brno University of technology in academic year 2025/26* 


# Where to start

- Read previous section to get on the same page with me
- Check **[Devices](#devices)** section to learn whether library has been ported to your device
- If no, proceed with **[How to port](#how-to-port)** section, then return here
- Proceed with **[How to include](#how-to-include)** section
- You will probably want to look into **[API](#api)** and **[Basic functionality](#basic-functionality)** sections of this document


# Library structure

 - `./` folder contains basic documentation, versioning and licensing info.
 - `./docs`: Doxygen generated documentation
 - `./examples`: well-commented use cases and testbench for different
 embedded devices that this library supports
 - `./include`: header files of this library
 - `./platform`: ports of this library to different microcontroller devices
 - `./src`: library source files (.c)


# API

Data types that user interacts with:
- `Cl_memory_area_t`: area of memory that represents range of addresses with same logical meaning
- `Cl_peripheral_area_t`: area of memory that represents set of individual non-connected addresses

User-defined metadata:
- `memory_areas`: table of all memory areas
- `peripheral_areas`: table of all peripheral areas
- `area_backup_table`: table mapping memory area to its backup memory area
- `peripheral_backup_table`: table mapping peripheral area to its backup memory area

Functions for direct context storage:
- `cl_clear_mem_area`: this must be called for destination areas
- `cl_save_mem_area`: save contents of one memory area into another one
- `cl_load_mem_area`: retrieve saved contents
- `cl_read_mem_area`: retrieve saved contents, don't mark it as obsolete
- `cl_save_peripheral`: save contents of peripheral area into memory area
- `cl_load_peripheral`: retrieve saved contents
- `cl_read_peripheral`: retrieve saved contents, don't mark it as obsolete

Functions for automatic context storage:
- `cl_area_on`: inform library that context area has been turned on *(trigger load)*
- `cl_area_off`: inform library that context area has been turned off *(trigger save)*
- `cl_protect_memory`: mark context area as protected
- `cl_unprotect_memory`: mark context area as unprotected
- `cl_change_mode`: inform library that power mode of MCU has been changed


# Basic functionality

This library is expected to be used in following way:
1. Port with metadata about MCU is created
2. User defines context areas that he wants to protect alongside 
areas where he wants to protect them (registers into RAM array, 
RAM array into non-volatile memory...)
3. User declares these areas as protected
4. Every time power mode changes, user informs library about this change

*For better explanation, please visit `\examples` folder*


# Used terms

- *library* refers to this library
- *port* is implementation of `/platform` files in such a way that library can 
work on new device
- *user* is embedded developer using this library
- *memory area* is sequence of addresses with one logical or physical meaning
- *peripheral area* is set of addresses with one logical or physical meaning
(expected usage is registers of peripheral device or some MCU module)
- *context* refers to any data important to user, that might be lost in power
saving modes (memory area + peripheral area)
- *MCU*,*microcontroller*,*embedded device*,*device* are used interchangeably
- *source area* is area with some important data that user wants to save
- *destination area* is area used **only** as data backup


# How to port

TODO


# How to include

TODO




# Notes
- `git tag v<num.num.num>`
- `git push origin v<num.num.num>`
- `cmake -S . -B build -DTARGET_PLATFORM=frdm_kl27z`
- `cmake --build build`

## TO not DOs
 - deal with error handling
 - for some functions check if size of area is at least 2
 - get consistent comments for memory area + peripheral area = context area
 - 256 ids should be configurable macro 
- rewrite CMake files, everything is in one and its horrible

## TODOs
 - write proper testbench 
 - fix load/store design error
 - ideally go through comments
- logging is allways level TRACE and more importantly allways goes to console. fix it
- add logging macros as described in bachelors thesis
- add application for MCU1
- add application for MCU2


## Mention in improvements
 - maybe replace hard-coded structure creation with some macro: that could absolutely work in some cases
 - rework layer 1 so that new functions for sending data can be added in some simpler way
 - maye add function checking reset type? but this may be problematic as that is really dependent upon MCU specific stuff
 - more robust version of this library
- simplify L1: there is no need for separate cl_save_e and cl_save_b/hw/w/dw functions: cl_save_b/hw/w/dw should be renamed to cl_save_e and be directly included in macro 

## Requirements and technical notes
 - Library works with data stored in Little endian format.
 - deal with CMake version
 - GCC at least 4.4
 - (?? 1B == 8b ??)
 - (?? every byte is addressable ??)
 - every address space used as destination should not be used in any other way
 - `const` ends in FLASH

## Possible issues
 - fragmentation of addres space : dynamically merge empty spaces with load function
 - table area-mode-on/off could possibly be too big cause it grows exponentionaly
 - great issue will be that I need to load data in logical order: if LRAM->HRAM loading happens before RF->HRAM
        loading, its a problem
 - similarily, problem with A->B->C loading in case A and B are turned off: for every saved/loading area, there needs to be proper algorithm for choosing destination. That should not be super hard and should fix the problem quite well.
 - it will probably pose a big issue to reinitialize destination areas after they are deleted: in turn_on, this should probably happen
 - loading using change_mode now does more loading than it should because of duplicates in backup_area table. Logic behind this
 table needs  to be reworked properly with this and also recursive saving in mind
 ## Versioning
 MAJOR:MINOR:PATCH
 MAJOR: if you change API in significant way, for non finished project use 0
 MINOR: if you add some big functionality
 PATCH: change to implementation of something, bug fix etc.

## AI
- ChatGPT + Copilot
- Used for writing several helper functions which are all clearly marked in Doxygen documentation
- Used as information source: less-known C constructs, best practice for Doxygen
- Used for writing part of test cases
- Copilot used when writing tests
- Used when writing CMake
