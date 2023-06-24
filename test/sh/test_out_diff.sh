#!/bin/sh

set -e

TEST_EXE_PATH=$1
TEST_DATA_PATH=$2
CURRENT_PATH=$3

if "./$TEST_EXE_PATH" | cmp -s "$TEST_DATA_PATH" -; then
  if [ "$V" = "1" ] || [ "$VERBOSE" = "1" ]; then
    if [ -t 1 ]; then
      printf '\033[0;32m[PASS]\033[0m %s\n' "$CURRENT_PATH"
    else
      printf '[PASS] %s\n' "$CURRENT_PATH"
    fi
  fi
else
  if [ "$V" = "1" ] || [ "$VERBOSE" = "1" ]; then
    if [ -t 1 ]; then
      printf '\033[0;31m[FAIL]\033[0m %s\n' "$CURRENT_PATH"
    else
      printf '[FAIL] %s\n' "$CURRENT_PATH"
    fi
  fi
fi
