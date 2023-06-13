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

printf '.PHONY: launch.json\n'
printf 'launch.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"0.2.0\",\\\\n  \"configurations\": [\\\\n' && echo \$^ | xargs -n 1 echo | sort | xargs cat && echo '  ],\\\\n}\\\\n') > \$@\n"

printf '.PHONY: tasks.json\n'
printf 'tasks.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"2.0.0\",\\\\n  \"tasks\": [\\\\n' && echo \$^ | xargs -n 1 echo | sort | xargs cat && echo '  ],\\\\n}\\\\n') > \$@\n"

echo ".PHONY: norm"

print_norm() {
  printf "norm: %s.norm\n" "$1"
  printf '%s.norm: %s\n' "$1" "../$2"
  printf '\t(cd .. && norminette %s)\n' "./$2"
  printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
  printf '\ttouch $@\n'
}

find ../include -name '*.h' | cut -c 4- | sort | while IFS= read -r FILE
do
  print_norm "root/$FILE" "$FILE"
done

find ../src -name '*.c' -o -name '*.h' | cut -c 8- | sort | while IFS= read -r FILE
do
  print_norm "$FILE" "src/$FILE"
done

for i in 0 1 2; do

  MINIRT_PRECISION=$i

  find_sources() {
    (cd "$1" && find "$2" -name '*.c' | sed "s/\$/$3/" | xargs)
  }

  find_lib_objs() {
    find_sources ../src "lib/$1" "$2.o"
  }

  find_exe_objs() {
    find_sources ../src "exe/$1" "$2.o"
  }

  libs_to_filenames() {
    echo "$1" | xargs -n 1 echo | sed 's/^/libminirt_/' | sed "s/\$/$2.a/" | xargs
  }

  libs_to_ldlibs() {
    printf '%s' '-L. '
    echo "$1" | xargs -n 1 echo | sed 's/^/-lminirt_/' | sed "s/\$/$2/" | xargs
  }

  print_lib() {
    printf 'libminirt_%s.a: %s\n' "$1.$MINIRT_PRECISION" "$(find_lib_objs "$1" ".$MINIRT_PRECISION")"
    printf '\trm -f $@ $@.tmp\n'
    printf '\tar cr $@.tmp $^\n'
    printf '\tmv $@.tmp $@\n'

    printf 'libminirt_%s.debug.a: %s\n' "$1.$MINIRT_PRECISION" "$(find_lib_objs "$1" ".$MINIRT_PRECISION.debug")"
    printf '\trm -f $@ $@.tmp\n'
    printf '\tar cr $@.tmp $^\n'
    printf '\tmv $@.tmp $@\n'

    printf 'libminirt_%s.debug.address.a: %s\n' "$1.$MINIRT_PRECISION" "$(find_lib_objs "$1" ".$MINIRT_PRECISION.debug.address")"
    printf '\trm -f $@ $@.tmp\n'
    printf '\tar cr $@.tmp $^\n'
    printf '\tmv $@.tmp $@\n'
  }

  print_exe() {
    printf '%s.exe: %s\n' "$1.$MINIRT_PRECISION" "$(find_exe_objs "$1" ".$MINIRT_PRECISION") $(libs_to_filenames "$2" ".$MINIRT_PRECISION")"
    printf '\trm -f $@ $@.tmp\n'
    printf "\t\$(CC) \$(LDFLAGS) %s -o \$@.tmp \%s\n" "$(find_exe_objs "$1" ".$MINIRT_PRECISION")" "$(libs_to_ldlibs "$2" ".$MINIRT_PRECISION")"
    printf '\tmv $@.tmp $@\n'

    printf '%s.debug.exe: %s\n' "$1.$MINIRT_PRECISION" "$(find_exe_objs "$1" ".$MINIRT_PRECISION") $(libs_to_filenames "$2" ".$MINIRT_PRECISION.debug")"
    printf '\trm -f $@ $@.tmp\n'
    printf "\t\$(CC) \$(LDFLAGS) %s -o \$@.tmp \%s\n" "$(find_exe_objs "$1" ".$MINIRT_PRECISION")" "$(libs_to_ldlibs "$2" ".$MINIRT_PRECISION.debug")"
    printf '\tmv $@.tmp $@\n'

    printf '%s.debug.address.exe: %s\n' "$1.$MINIRT_PRECISION" "$(find_exe_objs "$1" ".$MINIRT_PRECISION") $(libs_to_filenames "$2" ".$MINIRT_PRECISION.debug.address")"
    printf '\trm -f $@ $@.tmp\n'
    printf "\t\$(CC) \$(LDFLAGS) %s -fsanitize=address -o \$@.tmp \%s\n" "$(find_exe_objs "$1" ".$MINIRT_PRECISION")" "$(libs_to_ldlibs "$2" ".$MINIRT_PRECISION.debug.address")"
    printf '\tmv $@.tmp $@\n'

    printf 'launch.json: %s.launch.json.debug.part\n' "$1.$MINIRT_PRECISION"
    printf '%s.launch.json.debug.part:\n' "$1.$MINIRT_PRECISION"
    printf "\tprintf '    {\\\\n      \"type\": \"lldb\",\\\\n      \"request\": \"launch\",\\\\n      \"name\": \"%s (debug)\",\\\\n      \"program\": \"\$\${workspaceFolder}/build/%s.debug.exe\",\\\\n      \"cwd\": \"\$\${workspaceFolder}\",\\\\n      \"args\": [\"./assets/map/minimal.rt\"],\\\\n      \"preLaunchTask\": \"build %s (debug)\",\\\\n    },\\\\n' > \$@\n" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION"
    printf 'launch.json: %s.launch.json.debug.address.part\n' "$1.$MINIRT_PRECISION"
    printf '%s.launch.json.debug.address.part:\n' "$1.$MINIRT_PRECISION"
    printf "\tprintf '    {\\\\n      \"type\": \"lldb\",\\\\n      \"request\": \"launch\",\\\\n      \"name\": \"%s (debug, address)\",\\\\n      \"program\": \"\$\${workspaceFolder}/build/%s.debug.address.exe\",\\\\n      \"cwd\": \"\$\${workspaceFolder}\",\\\\n      \"args\": [\"./assets/map/minimal.rt\"],\\\\n      \"preLaunchTask\": \"build %s (debug, address)\",\\\\n    },\\\\n' > \$@\n" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION"
    printf 'tasks.json: %s.tasks.json.debug.part\n' "$1.$MINIRT_PRECISION"
    printf '%s.tasks.json.debug.part:\n' "$1.$MINIRT_PRECISION"
    printf "\tprintf '    {\\\\n      \"label\": \"build %s (debug)\",\\\\n      \"type\": \"shell\",\\\\n      \"command\": \"make %s.debug.exe\",\\\\n      \"options\": {\\\\n        \"cwd\": \"\$\${workspaceFolder}\",\\\\n      },\\\\n      \"problemMatcher\": [\"\$\$gcc\"]\\\\n    },\\\\n' > \$@\n" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION"
    printf 'tasks.json: %s.tasks.json.debug.address.part\n' "$1.$MINIRT_PRECISION"
    printf '%s.tasks.json.debug.address.part:\n' "$1.$MINIRT_PRECISION"
    printf "\tprintf '    {\\\\n      \"label\": \"build %s (debug, address)\",\\\\n      \"type\": \"shell\",\\\\n      \"command\": \"make %s.debug.address.exe\",\\\\n      \"options\": {\\\\n        \"cwd\": \"\$\${workspaceFolder}\",\\\\n      },\\\\n      \"problemMatcher\": [\"\$\$gcc\"]\\\\n    },\\\\n' > \$@\n" "$1.$MINIRT_PRECISION" "$1.$MINIRT_PRECISION"
  }

  printf 'libminirt%s.so: %s\n' ".$MINIRT_PRECISION" "$(find_sources ../src lib ".$MINIRT_PRECISION.-fPIC.o")"
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

  find ../src -name '*.c' | cut -c 8- | sort | while IFS= read -r FILE
  do
    printf '%s.o:\n' "$FILE.$MINIRT_PRECISION"
    printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
    printf "\trm -f \$@ \$@.tmp\n"
    printf "\t\$(CC) \$(CPPFLAGS) -DMINIRT_PRECISION=$MINIRT_PRECISION \$(CFLAGS) -c -o \$@.tmp ../src/%s\n" "$FILE"
    printf "\tmv \$@.tmp \$@\n"

    printf '%s.debug.o:\n' "$FILE.$MINIRT_PRECISION"
    printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
    printf "\trm -f \$@ \$@.tmp\n"
    printf "\t\$(CC) \$(CPPFLAGS) -DMINIRT_PRECISION=$MINIRT_PRECISION \$(CFLAGS) -g -c -o \$@.tmp ../src/%s\n" "$FILE"
    printf "\tmv \$@.tmp \$@\n"

    printf '%s.debug.address.o:\n' "$FILE.$MINIRT_PRECISION"
    printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
    printf "\trm -f \$@ \$@.tmp\n"
    printf "\t\$(CC) \$(CPPFLAGS) -DMINIRT_PRECISION=$MINIRT_PRECISION \$(CFLAGS) -g -fsanitize=address -c -o \$@.tmp ../src/%s\n" "$FILE"
    printf "\tmv \$@.tmp \$@\n"
  done

  find ../src/lib -name '*.c' | cut -c 8- | sort | while IFS= read -r FILE
  do
    printf '%s.-fPIC.o:\n' "$FILE.$MINIRT_PRECISION"
    printf "\t[ -d \$(@D) ] || (rm -f \$(@D) && mkdir -p \$(@D))\n"
    printf "\trm -f \$@ \$@.tmp\n"
    printf "\t\$(CC) \$(CPPFLAGS) -DMINIRT_PRECISION=$MINIRT_PRECISION \$(CFLAGS) -O -fPIC -c -o \$@.tmp ../src/%s\n" "$FILE"
    printf "\tmv \$@.tmp \$@\n"
  done

done
