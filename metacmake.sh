#!/bin/sh

set -e

cd "$(dirname "$0")"

sh script/cmakelists_txt.sh > CMakeLists.txt
