#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

echo "=== gf2 test suite ==="

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

fail=0

run() {
	name=$1
	shift
	printf '%-40s ' "$name"
	if "$@" >"$TMP/out" 2>"$TMP/err"; then
		echo OK
	else
		echo FAIL
		cat "$TMP/out" "$TMP/err"
		fail=1
	fi
}

# --- i18n unit tests (no X11 required) ---
echo "--- i18n ---"
g++ -std=c++11 -I. tests/test_i18n.cpp i18n.cpp -o "$TMP/test_i18n"
run "i18n translations" "$TMP/test_i18n"

# --- CLI smoke tests ---
echo "--- CLI ---"
g++ gf2.cpp i18n.cpp -o "$TMP/gf2" -g -O0 -lX11 -pthread \
	-DUI_UNICODE $([ -d /usr/include/freetype2 ] && echo "-lfreetype -DUI_FREETYPE -I/usr/include/freetype2")

check_output() {
	name=$1
	expected=$2
	shift 2
	printf '%-40s ' "$name"
	output=$("$@" 2>&1 || true)
	if printf '%s' "$output" | grep -qF "$expected"; then
		echo OK
	else
		echo FAIL
		printf 'expected "%s", got:\n%s\n' "$expected" "$output"
		fail=1
	fi
}

check_output "--help (English)" "Usage:" env LANG=C "$TMP/gf2" --help || true
check_output "--help (Chinese)" "用法：" env LANG=zh_CN.UTF-8 "$TMP/gf2" --help || true
check_output "--help (Japanese)" "使い方:" env LANG=ja_JP.UTF-8 "$TMP/gf2" --help || true

# Vim must not be required at startup.
printf '%-40s ' "no vim warning at startup"
output=$(env LANG=C GF_DUMP_MENU=0 "$TMP/gf2" --help 2>&1 || true)
if printf '%s' "$output" | grep -q "vim: not found"; then
	echo FAIL
	fail=1
else
	echo OK
fi

# --- Debugger fixture ---
echo "--- debug fixture ---"
if command -v gdb >/dev/null 2>&1; then
	gcc -g -O0 testcases.c -o "$TMP/testcases"
	check_output "gdb batch: c = 5.000000" "c = 5.000000" \
		gdb -q -batch -ex run "$TMP/testcases"
else
	echo "gdb not found, skipping debugger fixture test"
fi

# --- gf2 functional tests (require X11 + gdb) ---
echo "--- functional ---"
if [ -n "${DISPLAY:-}" ] && command -v gdb >/dev/null 2>&1; then
	if tests/test_gf2_functionality.sh; then
		:
	else
		fail=1
	fi
else
	echo "DISPLAY or gdb unavailable, skipping functional tests"
fi

if [ "$fail" -ne 0 ]; then
	echo "=== TESTS FAILED ==="
	exit 1
fi
echo "=== ALL TESTS PASSED ==="
