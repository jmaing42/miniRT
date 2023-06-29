#!/bin/sh

set -e

cd "$(dirname "$0")"

MINIRT_PRECISION=$1

generate_gnumakefile() {
  [ ! -t 1 ] || printf "\033[0;33m[INFO]\033[0m generating Makefile..."
  [ -t 1 ] || printf "[INFO] generating Makefile..."
  MINIRT_PRECISION="$MINIRT_PRECISION" sh build_gnumakefile.sh > "../build/$MINIRT_PRECISION.mk"
  printf " done!\n"
}

if [ ! -f "../build/files.$MINIRT_PRECISION.txt" ]; then

  find ../include ../src -name "*.c" -o -name "*.h" | grep -v /test/ | sort > "../build/files.$MINIRT_PRECISION.new.txt"

  generate_gnumakefile

  mv "../build/files.$MINIRT_PRECISION.new.txt" "../build/files.$MINIRT_PRECISION.txt"

else

  cleanup() {
    rm -rf ../build/files.old.txt
  }

  trap cleanup EXIT

  mv -f "../build/files.$MINIRT_PRECISION.txt" ../build/files.old.txt

  find ../include ../src -name "*.c" -o -name "*.h" | grep -v /test/ | sort > ../build/files.new.txt

  cmp -s ../build/files.old.txt ../build/files.new.txt || generate_gnumakefile

  mv ../build/files.new.txt "../build/files.$MINIRT_PRECISION.txt"

fi
