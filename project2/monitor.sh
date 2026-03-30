#!/bin/bash

LOG="health.log"
CPU_TH=80
MEM_TH=80
DISK_TH=80
INTERVAL=60

log() { echo "$(date '+%Y-%m-%d %H:%M:%S'): $@" >> "$LOG"; }

cpu_usage() {
  awk '{u=$2+$4; t=$2+$4+$5; if (t!=0) printf "%d", u/t*100}' /proc/stat 2>/dev/null || echo 0
}

mem_usage() {
  free | awk 'NR==2{printf "%.0f", $3*100/$2}'
}

disk_usage() {
  df / | awk 'NR==2{printf "%.0f", $5}'
}

procs() {
  ps ax | wc -l | awk '{print $1-1}'
}

alert() {
  local m=$1 r=$2 t=$3
  if [ "$r" -gt "$t" ]; then
    echo "ALERT: $m $r% > ${t}%"
    log "ALERT: $m $r% > ${t}%"
  fi
}

status() {
  clear
  CPU=$(cpu_usage)
  MEM=$(mem_usage)
  DISK=$(disk_usage)
  PROCS=$(procs)
  echo "=== System Health ==="
  echo "CPU: ${CPU}%"
  echo "Mem: ${MEM}%"
  echo "Disk: ${DISK}%"
  echo "Procs: $PROCS"
  echo "Log: $LOG"
  alert "CPU" "$CPU" "$CPU_TH"
  alert "Mem" "$MEM" "$MEM_TH"
  alert "Disk" "$DISK" "$DISK_TH"
  echo "===================="
}

menu() {
  echo "1. Status"
  echo "2. Set CPU thresh"
  echo "3. Set Mem thresh"
  echo "4. Set Disk thresh"
  echo "5. View log"
  echo "6. Clear log"
  echo "7. Monitor (loop)"
  echo "0. Exit"
  read -p "Choose: " opt
  case $opt in
    1) status ;;
    2) read -p "CPU %: " CPU_TH ;;
    3) read -p "Mem %: " MEM_TH ;;
    4) read -p "Disk %: " DISK_TH ;;
    5) cat "$LOG" ;;
    6) > "$LOG" ; log "Log cleared" ;;
    7) while true; do status; sleep $INTERVAL; done ;;
    0) exit 0 ;;
    *) echo "Invalid" ;;
  esac
  read -p "Press Enter..."
}

trap "log 'Stopped'; exit 0" INT

touch "$LOG"
log "Started"
while true; do menu; done
