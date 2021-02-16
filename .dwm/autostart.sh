#!/bin/bash

xset -dpms s off
picom &
conky &
feh --no-fehbg --bg-fill "$HOME/.dwm/out.png"
