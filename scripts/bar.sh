#!/bin/sh

interval=0

black=#282C34
green=#98C379
white=#ABB2BF
gray=#32363f
blue=#61AFEF
red=#E06C75
yellow=#E5C07B
magenta=#C678DD
cyan=#56B6C2

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c$green^ CPU"
  printf "^c$white^ $cpu_val"
}

volume() {
  vol_val=$(pamixer --get-volume-human)
	case "$(pamixer --get-volume-human 2>/dev/null)" in
	muted) printf "^c$yellow^   ^d^%s" "^c$white^$vol_val" ;;
	*)     printf "^c$blue^   ^d^%s" "^c$white^$vol_val" ;;
	esac
}

mem() {
  printf "^c$magenta^ MEM "
  printf "^c$white^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

backlight() {
  printf "^c$yellow^ 盛 "
  printf "^c$white^ $(xbacklight -get)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$green^ 直 ^d^%s" " ^c$white^Connected" ;;
	down) printf "^c$red^ 睊 ^d^%s" " ^c$white^Disconnected" ;;
	esac
}

clock() {
	printf "^c$red^  "
	printf "^c$white^ $(date '+%d/%m/%Y %H:%M:%S ') "
}

fcitx5_bar(){
  case "$(fcitx5-remote -q 2>/dev/null)" in
  EN)  printf "^c$white^   ^d^%s" "^c$white^EN" ;;
  VI)  printf "^c$white^   ^d^%s" "^c$white^VI" ;;
  esac
}

battery(){
  bat1_val=$(cat /sys/class/power_supply/BAT0/capacity)
  bat2_val=$(cat /sys/class/power_supply/BAT1/capacity)
  # add this because i have 2 batteries
  case "$(cat /sys/class/power_supply/AC/online 2>/dev/null)" in
	0) printf "^c$green^   ^d^%s""^c$white^|$bat1_val|$bat2_val|" ;;
	1) printf "^c$yellow^   ^d^%s""^c$white^|$bat1_val|$bat2_val|" ;;
  esac
}

while true; do

    [ $interval = 0 ] 
      interval=$((interval + 1))

  sleep 1 && xsetroot -name "$(cpu) $(mem) $(wlan) $(fcitx5_bar) $(backlight) $(battery) $(volume) $(clock) "
done
