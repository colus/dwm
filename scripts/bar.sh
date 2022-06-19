#!/bin/sh

interval=0

black=#2E3440
green=#A3BE8C
white=#D8DEE9
gray=#373d49
blue=#81A1C1
red=#BF616A
darkblue=#7292b2

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c$blue^ ^b$gray^ CPU"
  printf "^c$white^ ^b$black^ $cpu_val"
}

volume() {
  vol_val=$(pamixer --get-volume-human)
	case "$(pamixer --get-volume-human)" in
	muted) printf "^c$blue^ ^b$gray^   ^d^%s" " ^c$white^$vol_val" ;;
	*) printf "^c$blue^ ^b$gray^   ^d^%s" " ^c$white^$vol_val" ;;
	esac
}

mem() {
  printf "^c$blue^^b$gray^   "
  printf "^c$white^^b$black^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$blue^ ^b$gray^ 󰤨 ^d^%s" " ^c$white^Connected" ;;
	down) printf "^c$blue^ ^b$gray^ 󰤭 ^d^%s" " ^c$white^Disconnected" ;;
	esac
}

clock() {
	printf "^c$blue^ ^b$gray^ 󱑆 "
	printf "^c$white^^b$black^ $(date '+%d/%m/%Y %H:%M:%S ') "
}

fcitx5_bar(){
  case "$(fcitx5-remote -q)" in
  EN)  printf "^c$blue^ ^b$gray^   ^d^%s" " ^c$white^EN" ;;
  VI)  printf "^c$blue^ ^b$gray^   ^d^%s" " ^c$white^VI" ;;
  esac
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] 

  sleep 1 && xsetroot -name " $(cpu) $(mem) $(wlan) $(fcitx5_bar) $(volume) $(clock) "
done
