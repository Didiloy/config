#!/bin/bash
LUM="$(brightnessctl | grep 'Current' | cut -d " " -f 4 | sed 's/(//' | sed 's/)//')"
echo "$LUM"
