#!/bin/sh

set -e

TEST_EXE_PATH=$1
TEST_DATA_PATH=$2
CURRENT_PATH=$3

(cd "$TEST_DATA_PATH" && find . -name "*.txt") | cut -c 3- | sed s/.txt\$// | sort | while IFS= read -r line;
do
  if echo "$line" | xargs | ASAN_OPTIONS=detect_leaks=0 xargs "./$TEST_EXE_PATH" | diff "$TEST_DATA_PATH/$line.txt" -; then
    if [ "$V" = "1" ] || [ "$VERBOSE" = "1" ]; then
      if [ -t 1 ]; then
        printf '\033[0;32m[PASS]\033[0m %s\n' "$CURRENT_PATH - $line"
      else
        printf '[PASS] %s\n' "$CURRENT_PATH - $line"
      fi
    fi
  else
    if [ "$V" = "1" ] || [ "$VERBOSE" = "1" ]; then
      if [ -t 1 ]; then
        printf '\033[0;31m[FAIL]\033[0m %s\n' "$CURRENT_PATH - $line"
      else
        printf '[FAIL] %s\n' "$CURRENT_PATH - $line"
      fi
    fi
    exit 1
  fi
done
