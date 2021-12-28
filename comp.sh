#!/usr/bin/env bash

#avr-gcc running_led.c -mmcu=attiny88 -std=gnu99 -Wall -Os -o $1
avr-objcopy -j .text -j .data -O ihex $1 $1.hex
avr-size --mcu=attiny88 --format=avr $1
