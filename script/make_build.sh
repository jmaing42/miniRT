#!/bin/sh

set -e

cd "$(dirname "$0")"

[ -d ../build ] || mkdir ../build

sh build_refresh_makefile.sh
