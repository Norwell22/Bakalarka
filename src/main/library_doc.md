# Library documentation

This file serves as a basic first version of documentation for my library
Its main point is for me stoopid person to not forget what I came up with

## Configuration file

Very important will be architecture choice
Don't forget to allow/block raw functions
Turn logging on-off
Probably some lightweight version

## Layer 1
Layer 1 refers to most low-level library layer. Its goal is basically to move data from one place to another
It's most important and problematic role is to provide means for different ways in which we can move data from one place to another
It contains basic moving in memory from one place to another, should also contain send/receive mechanism and custom sending mechanism with 
option to pass down some bonus data.
MCU-specific functions aren't currently on one place because I haven't figured out yet what is the best approach about them
MCU-specific functions for storing data: `store_byte`, `send_byte`, `custom_send_byte`
MCU-specific functions for receiving data: `load_byte`, `rcv_byte`, `custom_rcv_byte`

Generic functions build on those functions and provide means for storing data in every technical way. Data can be stored/loaded:
 - by bytes
 - by half words
 - by words
 - (by double words)
 Those functions are currently stored in l1_public.c
 
 There are some TODOs accross different files, mainly stuff that I need to figure out what best approach about them might be

In one sentence: now I can write and load data across different memory areas without worying about technical details of it. 

## Layer 2


## TODOs
 - deal with floating point data somehow, probably add functions like for B,HW,W,DW
 - write conf file
 - write proper testbench
 - make proper voluntary logging
 - last address of context should not be part of it
 - write example code to showcase to Strnadel
 - fix ugly local includes
 - remove unnecessary includes
 - check Endianess, probably deal with it in config
 - after series of events int x[10]; <VLLS1>;<wakeup>; is space for x  still 'allocated' ?
 - it would probably be better if areas itself also contained ways to write into them (load/send/custom_send)
 - metadata should also contain current_mode as this simplifies user interface 
 - there should be an option to save one area into multiple backup places if one won't be enough
 - maybe replace hard-coded structure creation with some macro: that could absolutely work in some cases
 - L3 meta-meta data: **current mode**, **number of areas**
 - change it so that end address is actually end address

## Requirements
 - deal with CMake version
 - GCC at least 4.4
 - (?? 1B == 8b ??)
 - (?? every byte is addressable ??)
 - every address space used as destination should not be used in any other way

## Possible issues
 - fragmentation of addres space : dynamically merge empty spaces with load function
 - table area-mode-on/off could possibly be too big cause it grows exponentionaly
 - great issue will be that I need to load data in logical order: if LRAM->HRAM loading happens before RF->HRAM
        loading, its a problem
 - similarily, problem with A->B->C loading in case A and B are turned off: for every saved/loading area, there needs to be proper algorithm for choosing destination. That should not be super hard and should fix the problem quite well.
 - it will probably pose a big issue to reinitialize destination areas after they are deleted: in turn_on, this should probably happen