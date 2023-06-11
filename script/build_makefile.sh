#!/bin/sh

set -e

echo "SRCS_LIB_CORE = $(cd ../src && find lib/core -name "*.c" | xargs)"
echo "SRCS_EXE_MINIRT = $(cd ../src && find exe/minirt -name "*.c" | xargs)"
cat build_makefile.mk
find ../src -name "*.c" | cut -c 7 | while IFS= read -r FILE
do
  printf "%s.o:\n" "$FILE"
  printf "\t\$(CC) \$(CPPFLAGS) \$(CFLAGS) -c -o %s.o ../build/%s" "$FILE" "$FILE"
done
