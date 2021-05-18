#!/bin/bash
#xrandr --output HDMI-1 --auto --left-of eDP-1
xrandr --output HDMI-1-1 --auto --left-of eDP-1-1
xinput --set-prop "ETPS/2 Elantech Touchpad" "libinput Natural Scrolling Enabled" 1
feh --bg-scale /home/dylan/Téléchargements/fond_ecran/meuf_cafe_voiture.jpg &
killall compton
compton
eww-daemon
qutebrowser &
