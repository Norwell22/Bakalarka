/*
@author: Michal Zidzik
@date:26.11.2025
@file: context_manager.c
@brief: initial file for testing and running library
*/
#include "../../include/main/context_manager.h"
#include <stdio.h> //this would be better if wasn't here

void lib_init()
{}

//this is generalized function, containing logic that does some work
void blink_led() 
{
   puts("PLATFORM INDEPENDEND LOGIC");
   platform_toggle_led();  //this is call  to the function that must be implemented for specific platform
}