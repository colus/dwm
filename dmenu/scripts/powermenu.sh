#!/bin/sh

function powermenu{
  options="Cancel\nShutdown\nReboot\nLogout"
  selected=$(echo -e $options | dmenu)
  if [[ $selected = "Shutdown" ]]; then
    poweroff
  elif [[ $selected = "Reboot" ]]; then
    reboot
  elif [[ $selected = "Logout" ]]; then
    logout
  elif [[ $selected = "Cancel" ]]; then
    return
  fi
  
}

powermenu()
