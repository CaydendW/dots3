function fish_prompt
    echo -n [(whoami)'@'(uname -n)':' (string replace -r "$HOME" "~" "$PWD")]'$ '
end

