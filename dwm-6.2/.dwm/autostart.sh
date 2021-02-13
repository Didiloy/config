#!/bin/bash
xrandr --output HDMI-1 --auto --left-of eDP-1
compton -o 0.80 &
feh --bg-scale /home/dylan/Téléchargements/fond_ecran/meuf_cafe_voiture.jpg &
qutebrowser &
