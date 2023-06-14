#!/bin/sh

set -e

cd "$(dirname "$0")"

echo '##########################################################'
echo '# THIS FILE IS AUTO GENERATED. DO NOT MODIFY IT MANUALLY #'
echo '##########################################################'
echo ''


# ==============================================================================
# basic variables
# ==============================================================================

echo 'CFLAGS = -Wall -Wextra -Werror'
echo 'CPPFLAGS = -I./include -I./src/include'


# ==============================================================================
# vscode debug configuration
# ==============================================================================

printf '.PHONY: launch.json\n'
printf 'launch.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"0.2.0\",\\\\n  \"configurations\": [\\\\n' && echo \$^ | xargs -n 1 echo | sort | xargs cat && echo '  ],\\\\n}\\\\n') > \$@\n"

printf '.PHONY: tasks.json\n'
printf 'tasks.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"2.0.0\",\\\\n  \"tasks\": [\\\\n' && echo \$^ | xargs -n 1 echo | sort | xargs cat && echo '  ],\\\\n}\\\\n') > \$@\n"


# ==============================================================================
# norminette
# ==============================================================================

echo ".PHONY: norm"

print_norm() {
  printf "norm: %s.norm\n" "$1"
  printf '%s.norm: %s\n' "$1" "../$2"
  printf '\t(cd .. && norminette %s)\n' "./$2"
  printf "\tmkdir -p \$(@D)\n"
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


# ==============================================================================
# util functions
# ==============================================================================

# list of source files
find_sources() {
  SRC_PATH="$1"

  (cd ../src && find "$SRC_PATH" -name '*.c')
}

# list of objs for given lib
list_lib_objs() {
  LIB_NAME="$1"
  SUFFIX="$2"

  find_sources "lib/$LIB_NAME" | sed "s/\$/$SUFFIX.o/"
}

# list of objs for given exe
list_exe_objs() {
  EXE_NAME="$1"
  SUFFIX="$2"

  find_sources "exe/$EXE_NAME" | sed "s/\$/$SUFFIX.o/"
}

# map space-separated list of lib name to list of lib file name
libs_to_filenames() {
  LIB_NAMES="$(echo "$1" | xargs -n 1 echo)"
  SUFFIX="$2"

  echo "$LIB_NAMES" | sed 's/^/libminirt_/' | sed "s/\$/$SUFFIX.a/"
}

# map space-separated list of lib name to list of LDFLAGS
libs_to_ldlibs() {
  LIB_NAMES="$(echo "$1" | xargs -n 1 echo)"
  SUFFIX="$2"

  echo "$LIB_NAMES" | sed 's/^/-lminirt_/' | sed "s/\$/$SUFFIX/"
}

# emit obj rule
emit_o() {
  SRC_PATH="$1"
  SUFFIX="$2"
  EXTRA_FLAGS="$3"

  printf '%s%s.o: ../src/%s\n' "$SRC_PATH" "$SUFFIX" "$SRC_PATH"
  printf "\tmkdir -p \$(@D)\n"
  printf "\trm -f \$@ \$@.tmp\n"
  printf "\t(cd .. && \$(CC) \$(CPPFLAGS) \$(CFLAGS) %s -c -o build/\$@.tmp ./src/%s)\n" "$EXTRA_FLAGS" "$SRC_PATH"
  printf "\tmv \$@.tmp \$@\n"
}

# emit lib rule
emit_a() {
  LIB_NAME="$1"
  SUFFIX="$2"

  printf 'libminirt_%s%s.a: %s\n' "$LIB_NAME" "$SUFFIX" "$(list_lib_objs "$LIB_NAME" "$SUFFIX" | xargs)"
  printf '\trm -f $@ $@.tmp\n'
  printf '\tar cr $@.tmp $^\n'
  printf '\tmv $@.tmp $@\n'
}

# emit exe rule
emit_exe() {
  EXE_NAME="$1"
  SUFFIX="$2"
  DEPENDENCY_LIBS="$3"
  EXTRA_FLAGS="$4"
  EMIT_VSCODE_SETTINGS="$5"
  DEBUG_ARGS="$6"
  if [ "$DEBUG_ARGS" = "" ]; then
    DEBUG_ARGS='[]'
  fi

  printf '%s%s.exe: %s\n' "$EXE_NAME" "$SUFFIX" "$(list_exe_objs "$EXE_NAME" "$SUFFIX" | xargs) $(libs_to_filenames "$DEPENDENCY_LIBS" "$SUFFIX" | xargs)"
  printf '\trm -f $@ $@.tmp\n'
  printf "\t(cd .. && \$(CC) \$(LDFLAGS) -L build %s %s -o build/\$@.tmp %s)\n" "$(libs_to_ldlibs "$DEPENDENCY_LIBS" "$SUFFIX" | xargs)" "$EXTRA_FLAGS" "$(list_exe_objs "$EXE_NAME" "$SUFFIX" | sed s#^#build/# | xargs)"
  printf '\tmv $@.tmp $@\n'

  if [ "$EMIT_VSCODE_SETTINGS" = "1" ]; then
    NAME="$EXE_NAME ($(printf '%s' "$SUFFIX" | sed s/^\\.//))"
    if [ "$NAME" = "$EXE_NAME ()" ]; then
      NAME="$EXE_NAME"
    fi

    printf 'launch.json: %s%s.launch.json.debug.part\n' "$EXE_NAME" "$SUFFIX"
    printf '%s%s.launch.json.debug.part:\n' "$EXE_NAME" "$SUFFIX"
    printf "\tprintf '    {\\\\n      \"type\": \"lldb\",\\\\n      \"request\": \"launch\",\\\\n      \"name\": \"Debug %s\",\\\\n      \"program\": \"\$\${workspaceFolder}/build/%s%s.exe\",\\\\n      \"cwd\": \"\$\${workspaceFolder}\",\\\\n      \"args\": %s,\\\\n      \"preLaunchTask\": \"Build %s\",\\\\n    },\\\\n' > \$@\n" "$NAME" "$EXE_NAME" "$SUFFIX" "$DEBUG_ARGS" "$NAME"

    printf 'tasks.json: %s%s.tasks.json.debug.part\n' "$EXE_NAME" "$SUFFIX"
    printf '%s%s.tasks.json.debug.part:\n' "$EXE_NAME" "$SUFFIX"
    printf "\tprintf '    {\\\\n      \"label\": \"Build %s\",\\\\n      \"type\": \"shell\",\\\\n      \"command\": \"make %s%s.exe\",\\\\n      \"options\": {\\\\n        \"cwd\": \"\$\${workspaceFolder}\",\\\\n      },\\\\n      \"problemMatcher\": [\"\$\$gcc\"]\\\\n    },\\\\n' > \$@\n" "$NAME" "$EXE_NAME" "$SUFFIX"
  fi
}


# ==============================================================================
# per-precision
# ==============================================================================

for MINIRT_PRECISION in 0 1 2; do

  print_exe_obj() {
    SRC_PATH="$1"

    emit_o "$SRC_PATH" ".$MINIRT_PRECISION" "-DMINIRT_PRECISION=$MINIRT_PRECISION -O"
    emit_o "$SRC_PATH" ".$MINIRT_PRECISION.debug" "-DMINIRT_PRECISION=$MINIRT_PRECISION -g"
    emit_o "$SRC_PATH" ".$MINIRT_PRECISION.debug.address" "-DMINIRT_PRECISION=$MINIRT_PRECISION -g -fsanitize=address"
  }

  print_lib_obj() {
    SRC_PATH="$1"

    print_exe_obj "$SRC_PATH"
    emit_o "$SRC_PATH" ".$MINIRT_PRECISION.-fPIC" "-DMINIRT_PRECISION=$MINIRT_PRECISION -O -fPIC"
  }

  print_lib() {
    LIB_NAME="$1"

    emit_a "$LIB_NAME" ".$MINIRT_PRECISION"
    emit_a "$LIB_NAME" ".$MINIRT_PRECISION.debug"
    emit_a "$LIB_NAME" ".$MINIRT_PRECISION.debug.address"
  }

  print_exe() {
    EXE_NAME="$1"
    DEPENDENCY_LIBS="$2"
    EXTRA_FLAGS="$3"

    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION" "$DEPENDENCY_LIBS" "-DMINIRT_PRECISION=$MINIRT_PRECISION"
    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION.debug" "$DEPENDENCY_LIBS" "-DMINIRT_PRECISION=$MINIRT_PRECISION" 1
    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION.debug.address" "$DEPENDENCY_LIBS" "-DMINIRT_PRECISION=$MINIRT_PRECISION -fsanitize=address" 1
  }

  printf 'libminirt%s.so: %s\n' ".$MINIRT_PRECISION" "$(find_sources lib | sed "s/\$/.$MINIRT_PRECISION.-fPIC.o/" | xargs)"
  printf '\trm -f $@ $@.tmp\n'
  printf "\t\$(CC) \$(LDFLAGS) -shared -o \$@.tmp \$<\n"
  printf "\tmv \$@.tmp \$@\n"

  print_lib bmp
  print_lib common
  print_lib core
  print_lib json
  print_lib plugin_rtinrt
  print_lib plugin_portal
  print_lib scene
  print_exe minirt_validate "common json plugin_portal plugin_rtinrt scene"
  print_exe minirt "bmp common core json plugin_portal plugin_rtinrt scene"

  find ../src/exe -name '*.c' | cut -c 8- | sort | while IFS= read -r FILE
  do
    print_exe_obj "$FILE"
  done

  find ../src/lib -name '*.c' | cut -c 8- | sort | while IFS= read -r FILE
  do
    print_lib_obj "$FILE"
  done

done
