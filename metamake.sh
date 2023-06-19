#!/bin/sh

set -e

cd "$(dirname "$0")"

sh script/targets_mk.sh > targets.mk
