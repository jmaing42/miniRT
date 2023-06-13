#!/bin/sh

set -e

cd "$(dirname "$0")"

echo '##########################################################'
echo '# THIS FILE IS AUTO GENERATED. DO NOT MODIFY IT MANUALLY #'
echo '##########################################################'
echo ''
echo 'CFLAGS = -Wall -Wextra -Werror'
echo 'CPPFLAGS = -I../include -I../src/include'
echo ''

find_sources() {
  (cd "$1" && find "$2" -name '*.c' | sed "s/\$/$3/" | xargs)
}

find_lib_objs() {
  find_sources ../src "lib/$1" .o
}

find_exe_objs() {
  find_sources ../src "exe/$1" .o
}

libs_to_filenames() {
  echo "$1" | xargs -n 1 echo | sed 's/^/libminirt_/' | sed 's/$/.a/' | xargs
}

libs_to_ldlibs() {
  printf '%s' '-L. '
  echo "$1" | xargs -n 1 echo | sed 's/^/-lminirt_/' | xargs
}

print_lib() {
  printf 'libminirt_%s.a: %s\n' "$1" "$(find_lib_objs "$1")"
  printf '\trm -f $@ $@.tmp\n'
  printf '\tar cr $@.tmp $^\n'
  printf '\tmv $@.tmp $@\n'
}

print_exe() {
  printf '%s.exe: %s\n' "$1" "$(find_exe_objs "$1") $(libs_to_filenames "$2")"
  printf '\trm -f $@ $@.tmp\n'
  printf "\t\$(CC) \$(LDFLAGS) %s -o \$@.tmp \%s\n" "$(find_exe_objs "$1")" "$(libs_to_ldlibs "$2")"
  printf '\tmv $@.tmp $@\n'
}

printf 'libminirt.so: %s\n' "$(find_sources ../src lib .-fPIC.o)"
printf '\trm -f $@\n'
printf "\t\$(CC) \$(LDFLAGS) -shared -o \$@ \$<\n"

print_lib bmp
print_lib common
print_lib core
print_lib json
print_lib plugin_rtinrt
print_lib plugin_portal
print_lib scene
print_exe minirt_validate "common json plugin_portal plugin_rtinrt scene"
print_exe minirt "bmp common core json plugin_portal plugin_rtinrt scene"

echo ".PHONY: norm"

print_norm() {
  printf "norm: %s.norm\n" "$1"
  printf '%s.norm: %s\n' "$1" "../$2"
  printf '\t(cd .. && norminette %s)\n' "./$2"
  printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
  printf '\ttouch $@\n'
}

find ../include -name '*.h' | cut -c 4- | while IFS= read -r FILE
do
  print_norm "root/$FILE" "$FILE"
done

find ../src -name '*.c' -o -name '*.h' | cut -c 8- | while IFS= read -r FILE
do
  print_norm "$FILE" "src/$FILE"
done

find ../src -name '*.c' | cut -c 8- | while IFS= read -r FILE
do
  printf '%s.o:\n' "$FILE"
  printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
  printf "\trm -f \$@ \$@.tmp\n"
  printf "\t\$(CC) \$(CPPFLAGS) \$(CFLAGS) -c -o \$@.tmp ../src/%s\n" "$FILE"
  printf "\tmv \$@.tmp \$@\n"
done

find ../src/lib -name '*.c' | cut -c 8- | while IFS= read -r FILE
do
  printf '%s.-fPIC.o:\n' "$FILE"
  printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
  printf "\trm -f \$@ \$@.tmp\n"
  printf "\t\$(CC) \$(CPPFLAGS) \$(CFLAGS) -fPIC -c -o \$@.tmp ../src/%s\n" "$FILE"
  printf "\tmv \$@.tmp \$@\n"
done
