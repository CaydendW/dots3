#
# ~/.config/fish/config/fish
#

# Check if running interactively
if ! status -i
    exit
end

# Aliases
alias ls='ls -l -h -a --color=auto --group-directories-first'
alias grep='grep -i --color'
alias cls='clear'
alias reboot='sudo reboot'
alias shutdown='sudo shutdown -P now'
alias please='sudo'
alias calc='bc'
alias fishrc='vim ~/.config/fish/config.fish'
alias calculator='bc'
alias py='python'
alias mountwin='sudo mount -t ntfs /dev/sda1 /mnt/c && sudo mount -t ntfs /dev/sdb2 /mnt/d'
alias rr='curl -s -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash'
alias scrots='scrot -s ~/Documents/scrot/%H:%M:%S::%Y-%m-%d.png'

# Editor
export EDITOR=vim
export VISUAL=code

# Standard terminal start
clear

#Run colorscript
if [ "$TERM_PROGRAM" != "vscode" ] && [ "$TERM_PROGRAM" != "kate" ] && [ "$TERM_PROGRAM" != "platformio-ide-terminal" ]
         colorscript random
end

#Path exports
export PATH="$HOME/.cargo/bin:$PATH"
export PATH="$HOME/.emacs.d/bin:$PATH"
export PATH="$HOME/.yarn/bin:$HOME/.config/yarn/global/node_modules/.bin:$PATH"
