#!/bin/sh

set -e

cd "$(dirname "$0")"

[ -d ../build ] || sh make_build.sh

cd ../build

make norm
