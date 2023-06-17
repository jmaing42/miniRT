#!/bin/sh

set -e

cd "$(dirname "$0")"

generate_makefile() {
  printf "\033[0;33m[INFO]\033[0m generating Makefile..."
  sh build_makefile.sh > ../build/Makefile
}

if [ ! -f ../build/files.txt ]; then

  find ../include ../src -name "*.c" -o -name "*.o" | sort > ../build/files.new.txt

  generate_makefile

  mv ../build/files.new.txt ../build/files.txt

else

  cleanup() {
    rm -rf ../build/files.old.txt
  }

  trap cleanup EXIT

  mv -f ../build/files.txt ../build/files.old.txt

  find ../include ../src -name "*.c" -o -name "*.o" | sort > ../build/files.new.txt

  cmp -s ../build/files.old.txt ../build/files.new.txt || generate_makefile

  mv ../build/files.new.txt ../build/files.txt

fi
