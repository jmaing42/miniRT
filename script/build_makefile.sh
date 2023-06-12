#!/bin/sh

set -e

cd "$(dirname "$0")"

echo '##########################################################'
echo '# THIS FILE IS AUTO GENERATED. DO NOT MODIFY IT MANUALLY #'
echo '##########################################################'
echo ''

echo "OBJS_LIB_FPIC = $(cd ../src && find lib -name '*.c' | sed 's/$/.-fPIC.o/' | xargs)"
echo "OBJS_LIB_BMP = $(cd ../src && find lib/bmp -name '*.c' | sed 's/$/.o/' | xargs)"
echo "OBJS_LIB_CORE = $(cd ../src && find lib/core -name '*.c' | sed 's/$/.o/' | xargs)"
echo "OBJS_EXE_MINIRT = $(cd ../src && find exe/minirt -name '*.c' | sed 's/$/.o/' | xargs)"

echo "norm: $(cd ../src && find . -name '*.c' -o -name '*.h' | cut -c 3- | sed 's/$/.norm/' | xargs) $(cd .. && find include -name '*.c' -o -name '*.h' | sed 's#^#root/#' | sed 's/$/.norm/' | xargs)"

cat build_makefile.mk

find ../include -name '*.h' | cut -c 4- | while IFS= read -r FILE
do
  printf "root/%s.norm:\n" "$FILE"
  printf "\tmkdir -p %s\n" "root/$(dirname "$FILE")"
  printf "\tnorminette ../%s\n" "$FILE"
  printf "\ttouch \$@\n"
done

find ../src -name '*.c' -o -name '*.h' | cut -c 8- | while IFS= read -r FILE
do
  printf "%s.norm:\n" "$FILE"
  printf "\tmkdir -p %s\n" "$(dirname "$FILE")"
  printf "\tnorminette ../src/%s\n" "$FILE"
  printf "\ttouch \$@\n"
done

find ../src -name '*.c' | cut -c 8- | while IFS= read -r FILE
do
  printf "%s.o:\n" "$FILE"
  printf "\tmkdir -p %s\n" "$(dirname "$FILE")"
  printf "\t\$(CC) \$(CPPFLAGS) \$(CFLAGS) -c -o %s.o ../src/%s\n" "$FILE" "$FILE"
done

find ../src/lib -name '*.c' | cut -c 8- | while IFS= read -r FILE
do
  printf "%s.-fPIC.o:\n" "$FILE"
  printf "\tmkdir -p %s\n" "$(dirname "$FILE")"
  printf "\t\$(CC) \$(CPPFLAGS) \$(CFLAGS) -fPIC -c -o %s.-fPIC.o ../src/%s\n" "$FILE" "$FILE"
done
