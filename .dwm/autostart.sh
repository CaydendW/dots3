#!/bin/bash

xset -dpms s off
picom &
conky &
feh --no-fehbg --bg-fill --no-xinerama "/home/cayden/.dwm/out.png"
