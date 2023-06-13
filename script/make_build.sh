#!/bin/sh

set -e

cd "$(dirname "$0")"

[ ! -d ../build ] || sh build_makefile.sh > ../build/Makefile
[ ! -d ../build ] || exit 0


cleanup() {
  rm -rf ../tmp
}

trap cleanup EXIT

rm -rf ../tmp
mkdir ../tmp
sh build_makefile.sh > ../tmp/Makefile
mv ../tmp ../build
