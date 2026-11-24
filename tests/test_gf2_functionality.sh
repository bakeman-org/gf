#!/bin/sh
# Functional test: drive gf2 through its control pipe against the debuggee ELF
# and verify gdb commands are really sent and produce expected results.
set -eu

cd "$(dirname "$0")/.."
TESTS="$PWD/tests"
DEBUGGEE="$TESTS/debuggee"
TMP=""
GF2_PID=""
GDB_PID=""

# ---------- Nerd Font banner + colour helpers ----------
# Prefer a CJK-capable Nerd Font since this project ships Chinese UI strings.
_NF="Maple Mono NF CN"
_NFOUND=""
for f in "$HOME/.local/share/fonts/"*.ttf \
         "$HOME/.local/share/fonts/"*.otf \
         /usr/share/fonts/**/*.ttf \
         /usr/share/fonts/**/*.otf; do
	case "$f" in
	*[Mm]aple*Mono*NF*CN*) _NFOUND=1; break ;;
	esac
done

printf '\033[?25l'   # hide cursor while banner prints
printf '\033[1;36m ╔══════════════════════════════════════════════════════════════╗\033[0m\n'
printf '\033[1;36m ║\033[0m  \033[1;32m\033[1;36m  gf2 functional test · \033[1;33mNERD FONT\033[1;36m  \033[1;32m\033[1;36m                \033[0m║\033[1;36m\033[0m\n'
printf '\033[1;36m ║\033[0m  \033[2mfont: %s  %s\033[0m                                \033[1;36m║\033[0m\n' \
	"$_NF" \
	"$([ -n "$_NFOUND" ] && printf '\033[32m✔ available\033[0m' || printf '\033[33m⚠ not in local fonts — falls back to terminal default\033[0m')"
printf '\033[1;36m ╠══════════════════════════════════════════════════════════════╣\033[0m\n'
printf '\033[1;36m ║\033[0m  \033[2mrun with DISPLAY or TERM=xterm-256color for best result\033[0m  \033[1;36m║\033[0m\n'
printf '\033[1;36m ╚══════════════════════════════════════════════════════════════╝\033[0m\n'
printf '\033[?25h'   # restore cursor

# ANSI colour tags; terminals without colour support just see the plain text.
COL_GREEN='\033[32m'
COL_RED='\033[31m'
COL_CYAN='\033[1;36m'
COL_BOLD='\033[1m'
COL_RESET='\033[0m'
tag_ok()  { printf '%b✔%b'  "$COL_GREEN" "$COL_RESET"; }
tag_fail(){ printf '%b✗%b'  "$COL_RED"   "$COL_RESET"; }
tag_div() { printf '%b─%b'  "$COL_CYAN"  "$COL_RESET"; }

cleanup() {
	if [ -n "$GF2_PID" ]; then kill -INT "$GF2_PID" 2>/dev/null || true; fi
	sleep 0.3
	if [ -n "$GDB_PID" ]; then kill "$GDB_PID" 2>/dev/null || true; fi
	pkill -x gf2 2>/dev/null || true
	pkill -x gdb 2>/dev/null || true
	if [ -n "$TMP" ] && [ -z "${KEEP_LOG:-}" ]; then rm -rf "$TMP"; fi
	if [ -n "$TMP" ] && [ -n "${KEEP_LOG:-}" ]; then echo "Artifacts kept at: $TMP"; fi
}
trap cleanup EXIT INT TERM

failures=0
report() {
	name=$1
	shift
	printf '%-42s ' "$name"
	if "$@" >"$TMP/report.out" 2>&1; then
		echo "$(tag_ok) OK"
	else
		echo "$(tag_fail) FAIL"
		sed 's/^/    /' "$TMP/report.out" | head -5
		failures=$((failures + 1))
	fi
}

# --- compile debuggee ELF ---
printf '%b--- building debuggee ELF %b---\033[0m\n' "$COL_CYAN" "$COL_RESET"
gcc -g -O0 -fno-omit-frame-pointer -o "$DEBUGGEE" "$TESTS/debuggee.c" -lpthread
file "$DEBUGGEE" | grep -q ELF || { printf '%bFAIL: not an ELF%b\n' "$COL_RED" "$COL_RESET"; exit 1; }
printf '%bOK%b: %s\n' "$COL_GREEN" "$COL_RESET" "$(file -b "$DEBUGGEE" | cut -c1-64)"

TMP=$(mktemp -d)
PIPE="$TMP/control.pipe"
GDBLOG="$TMP/gdb.log"
HOME_DIR="$TMP/home"
mkfifo "$PIPE"
mkdir -p "$HOME_DIR/.config"

cat > "$HOME_DIR/.config/gf2_config.ini" <<EOF
[ui]
language=en

[gdb]
argument=-q
argument=-ex
argument=set logging file $GDBLOG
argument=-ex
argument=set logging overwrite on
argument=-ex
argument=set logging on

[pipe]
control=$PIPE
EOF

printf '%b--- gf2 functional tests via control pipe %b---\033[0m\n' "$COL_CYAN" "$COL_RESET"

# Isolated HOME ensures no interference with the user's real config.
HOME="$HOME_DIR" DISPLAY=${DISPLAY:-:0} ./gf2 "$DEBUGGEE" \
	>"$TMP/gf2.stdout" 2>"$TMP/gf2.stderr" &
GF2_PID=$!
sleep 3
kill -0 "$GF2_PID" 2>/dev/null || {
	printf '%bFAIL: gf2 did not start%b\n' "$COL_RED" "$COL_RESET"
	cat "$TMP/gf2.stderr"
	exit 1
}

# Each echo opens/closes the FIFO; gf2's reader picks up one line per open.
send() {
	printf '%s\n' "$1" > "$PIPE" &
	sleep 0.8
}

send "c file $DEBUGGEE"
send "c break main"
send "c run"
send "c info breakpoints"
send "c bt"
send "c info threads"
send "c print localA"
send "c next"
send "c next"
send "c print sum"
send "c disassemble main"
send "c continue"

sleep 1

report "gf2 alive during session" test -d "/proc/$GF2_PID"
report "gdb log created" test -s "$GDBLOG"

if [ -s "$GDBLOG" ]; then
	report "breakpoint at main"       grep -qi 'breakpoint.*main' "$GDBLOG"
	report "backtrace produced"       grep -qi 'main' "$GDBLOG"
	report "threads enumerated"       grep -qi 'thread' "$GDBLOG"
	report "local variable inspected" grep -q 'localA' "$GDBLOG"
	report "disassembly produced"     grep -qi 'Dump of assembler' "$GDBLOG"
else
	cat "$TMP/gf2.stderr" | head -10
fi

# Clean shutdown with single Ctrl+C.
START=$(date +%s%N)
kill -INT "$GF2_PID" 2>/dev/null || true
for i in $(seq 1 30); do
	kill -0 "$GF2_PID" 2>/dev/null || break
	sleep 0.1
done
ELAPSED=$(( ($(date +%s%N) - START) / 1000000 ))
if kill -0 "$GF2_PID" 2>/dev/null; then
	echo "FAIL: gf2 did not exit on single Ctrl+C"
	failures=$((failures + 1))
else
	printf '%-42s ' "single Ctrl+C exit (${ELAPSED}ms)"
	if [ "$ELAPSED" -lt 3000 ]; then echo OK; else echo FAIL; failures=$((failures + 1)); fi
fi
sleep 0.5
report "no gdb process leaked" sh -c '! pgrep -x gdb >/dev/null'

printf '\033[1;36m╔══════════════════════════════════════════════════════════════╗\033[0m\n'
if [ "$failures" -ne 0 ]; then
	printf '%b║  %b✗  %s FUNCTIONAL TEST(S) FAILED%b                              ║\033[0m\n' \
		"$COL_CYAN" "$COL_RED" "$failures" "$COL_RESET"
	printf '\033[1;36m╚══════════════════════════════════════════════════════════════╝\033[0m\n'
	exit 1
fi
printf '%b║  %b✔  ALL FUNCTIONAL TESTS PASSED%b                               ║\033[0m\n' \
	"$COL_CYAN" "$COL_GREEN" "$COL_RESET"
printf '\033[1;36m╚══════════════════════════════════════════════════════════════╝\033[0m\n'
