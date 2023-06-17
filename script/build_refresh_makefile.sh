#!/bin/sh

set -e

cd "$(dirname "$0")"

if [ ! -f ../build/files.txt ]; then

  find ../include ../src -name "*.c" -o -name "*.o" | sort > ../build/files.txt

  sh build_makefile.sh > ../build/Makefile

else

  cleanup() {
    rm -rf ../build/files.old.txt
  }

  trap cleanup EXIT

  cleanup

  mv ../build/files.txt ../build/files.old.txt

  find ../include ../src -name "*.c" -o -name "*.o" | sort > ../build/files.new.txt

  cmp -s ../build/files.old.txt ../build/files.new.txt || sh build_makefile.sh > ../build/Makefile

  mv ../build/files.new.txt ../build/files.txt

fi
