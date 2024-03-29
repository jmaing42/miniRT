#!/bin/sh

set -e

cd "$(dirname "$0")"

CC=$( (command -v clang > /dev/null && echo clang) || (command -v gcc > /dev/null && echo gcc) || (command -v cc > /dev/null && echo cc) )
if [ "$USE_DEPS" = "" ]; then
  if [ "$CC" = "cc" ]; then
    USE_DEPS="0"
  else
    USE_DEPS="1"
  fi
fi
if [ "$USE_DEPS" != "0" ] && [ "$USE_DEPS" != "1" ]; then
  [ -t 2 ] && printf "\033[0;31m[ERROR]\033[0m" 1>&2 || printf "[ERROR]" 1>&2
  printf ' Invalud USE_DEPS: %s (valid values are: 0, 1, (empty))' "$USE_DEPS" 1>&2
  exit 1
fi

echo '##########################################################'
echo '# THIS FILE IS AUTO GENERATED. DO NOT MODIFY IT MANUALLY #'
echo '##########################################################'
echo ''

printf 'CC = %s\n' "$CC"
printf '\n'
printf '%s' '-include ../include.mk\n'
printf '\n'


# ==============================================================================
# basic variables
# ==============================================================================

echo 'CFLAGS = -Wall -Wextra -Werror'
echo 'CPPFLAGS = -I./include -I./src/include'
echo 'CPPFLAGS_INTERNAL = -I../include -I../src/include'


# ==============================================================================
# vscode debug configuration
# ==============================================================================

printf '.PHONY: launch.json\n'
printf 'launch.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"0.2.0\",\\\\n  \"configurations\": [\\\\n' && find json -name \"*.launch.json*.part\" | sort | xargs cat && printf '  ],\\\\n}\\\\n') > \$@\n"

printf '.PHONY: tasks.json\n'
printf 'tasks.json:\n'
printf "\t(printf '{\\\\n  \"version\": \"2.0.0\",\\\\n  \"tasks\": [\\\\n' && find json -name \"*.tasks.json*.part\" | sort | xargs cat && printf '  ],\\\\n}\\\\n') > \$@\n"


# ==============================================================================
# util functions
# ==============================================================================

# list of source files
find_sources() {
  FIND_SOURCES_SRC_PATH="$1"

  (cd ../src && find "$FIND_SOURCES_SRC_PATH" -name '*.c' | grep -v /test/)
}

# list of objs for given lib
list_lib_objs() {
  LIST_LIB_OBJS_LIB_PATH="$1"
  LIST_LIB_OBJS_SUFFIX="$2"

  find_sources "lib/$LIST_LIB_OBJS_LIB_PATH" | sed 's#^#obj/#' | sed "s/\$/$LIST_LIB_OBJS_SUFFIX.o/"
}

# list of objs for given exe
list_exe_objs() {
  LIST_EXE_OBJS_EXE_NAME="$1"
  LIST_EXE_OBJS_SUFFIX="$2"

  find_sources "exe/$LIST_EXE_OBJS_EXE_NAME" | sed 's#^#obj/#' | sed "s/\$/$LIST_EXE_OBJS_SUFFIX.o/"
}

# map space-separated list of lib name to list of lib file name
libs_to_filenames() {
  LIBS_TO_FILENAMES_LIB_NAMES="$(echo "$1" | xargs -n 1 echo)"
  LIBS_TO_FILENAMES_SUFFIX="$2"

  echo "$LIBS_TO_FILENAMES_LIB_NAMES" | sed 's#^#out/a/libminirt_#' | sed "s/\$/$LIBS_TO_FILENAMES_SUFFIX.a/"
}

# map space-separated list of lib name to list of LDFLAGS
libs_to_ldlibs() {
  LIBS_TO_LDLIBS_LIB_NAMES="$(echo "$1" | xargs -n 1 echo)"
  LIBS_TO_LDLIBS_SUFFIX="$2"

  echo "$LIBS_TO_LDLIBS_LIB_NAMES" | sed 's/^/-lminirt_/' | sed "s/\$/$LIBS_TO_LDLIBS_SUFFIX/"
}

# emit obj rule
emit_o() {
  EMIT_O_SRC_PATH="$1"
  EMIT_O_SUFFIX="$2"
  EMIT_O_EXTRA_FLAGS="$3"

  printf 'obj/%s%s.o: ../src/%s\n' "$EMIT_O_SRC_PATH" "$EMIT_O_SUFFIX" "$EMIT_O_SRC_PATH"
  printf "\trm -f \$@ \$@.tmp\n"
  printf "\tmkdir -p \$(@D)\n"
  printf "\t(cd .. && \$(CC) \$(CPPFLAGS) \$(CFLAGS) %s -c -o build/\$@.tmp ./src/%s)\n" "$EMIT_O_EXTRA_FLAGS" "$EMIT_O_SRC_PATH"
  if [ "$USE_DEPS" = "1" ]; then
    printf '\tmkdir -p %s\n' "$(dirname "deps/$EMIT_O_SRC_PATH")"
    printf "\t\$(CC) \$(CPPFLAGS_INTERNAL) -MM -MT \$@ -MF deps/%s%s.d ../src/%s\n" "$EMIT_O_SRC_PATH" "$EMIT_O_SUFFIX" "$EMIT_O_SRC_PATH"
  fi
  printf "\tmv \$@.tmp \$@\n"
  if [ "$USE_DEPS" = "1" ]; then
    printf '%s deps/%s%s.d\n' '-include' "$EMIT_O_SRC_PATH" "$EMIT_O_SUFFIX"
  fi
}

# emit lib rule
emit_a() {
  EMIT_A_LIB_NAME="$1"
  EMIT_A_LIB_SOURCE="$2"
  EMIT_A_SUFFIX="$3"

  printf 'out/a/libminirt_%s%s.a: %s\n' "$EMIT_A_LIB_NAME" "$EMIT_A_SUFFIX" "$(list_lib_objs "$EMIT_A_LIB_SOURCE" "$EMIT_A_SUFFIX" | xargs)"
  printf '\trm -f $@ $@.tmp\n'
  printf "\tmkdir -p \$(@D)\n"
  printf '\tar cr $@.tmp %s\n' "$(list_lib_objs "$EMIT_A_LIB_SOURCE" "$EMIT_A_SUFFIX" | xargs)"
  printf '\tmv $@.tmp $@\n'
}

emit_so() {
  EMIT_SO_LIB_NAME="$1"
  EMIT_SO_LIB_SOURCES="$(echo "$2" | xargs -n 1 echo | while IFS= read -r lib_path;
    do
      list_lib_objs "$lib_path" ".-fPIC$3"
    done | xargs)"
  EMIT_SO_SUFFIX="$3"
  EMIT_SO_EXTRA_FLAGS="$4"

  FILENAME="libminirt_$EMIT_SO_LIB_NAME$EMIT_SO_SUFFIX.so"
  if [ "$FILENAME" = "libminirt_$EMIT_SO_SUFFIX.so" ]; then
    FILENAME="libminirt$EMIT_SO_SUFFIX.so"
  fi

  printf 'out/so/%s: %s\n' "$FILENAME" "$EMIT_SO_LIB_SOURCES"
  printf '\trm -f $@ $@.tmp\n'
  printf "\tmkdir -p \$(@D)\n"
  printf "\t\$(CC) \$(LDFLAGS) -shared %s -o \$@.tmp %s\n" "$EMIT_SO_EXTRA_FLAGS" "$EMIT_SO_LIB_SOURCES"
  printf '\tmv $@.tmp $@\n'
}

# emit exe rule
emit_exe() {
  EMIT_EXE_EXE_NAME="$1"
  EMIT_EXE_SUFFIX="$2"
  EMIT_EXE_DEPENDENCY_LIBS="$3"
  EMIT_EXE_EXTRA_FLAGS="$4"
  EMIT_EXE_EMIT_VSCODE_SETTINGS="$5"
  EMIT_EXE_DEBUG_ARGS="$6"
  if [ "$EMIT_EXE_DEBUG_ARGS" = "" ]; then
    EMIT_EXE_DEBUG_ARGS='[]'
  fi

  printf 'out/exe/%s%s.exe: %s\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX" "$(list_exe_objs "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX" | xargs) $(libs_to_filenames "$EMIT_EXE_DEPENDENCY_LIBS" "$EMIT_EXE_SUFFIX" | xargs)"
  printf '\trm -f $@ $@.tmp\n'
  printf "\tmkdir -p \$(@D)\n"
  printf "\t(cd .. && \$(CC) %s \$(LDFLAGS) -Lbuild/out/a %s %s -o build/\$@.tmp)\n" "$(list_exe_objs "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX" | sed 's#^#build/#' | xargs)" "$(libs_to_ldlibs "$EMIT_EXE_DEPENDENCY_LIBS" "$EMIT_EXE_SUFFIX" | xargs)" "$EMIT_EXE_EXTRA_FLAGS"
  printf '\tmv $@.tmp $@\n'
  printf '%s: out/exe/%s%s.exe\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
  printf '\trm -f $@\n'
  printf '\tln -s %s%s.exe $@\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"

  if [ "$EMIT_EXE_EMIT_VSCODE_SETTINGS" = "1" ]; then
    NAME="$EMIT_EXE_EXE_NAME ($(printf '%s' "$EMIT_EXE_SUFFIX" | sed s/^\\.//))"
    if [ "$NAME" = "$EMIT_EXE_EXE_NAME ()" ]; then
      NAME="$EMIT_EXE_EXE_NAME"
    fi

    printf 'launch.json: json/%s%s.launch.json.debug.part\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
    printf 'json/%s%s.launch.json.debug.part:\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
    printf '\trm -f $@ $@.tmp\n'
    printf "\tmkdir -p \$(@D)\n"
    printf "\tprintf '    {\\\\n      \"type\": \"lldb\",\\\\n      \"request\": \"launch\",\\\\n      \"name\": \"Debug %s\",\\\\n      \"program\": \"\$\${workspaceFolder}/build/out/exe/%s%s.exe\",\\\\n      \"cwd\": \"\$\${workspaceFolder}\",\\\\n      \"args\": %s,\\\\n      \"preLaunchTask\": \"Build %s\",\\\\n    },\\\\n' > \$@.tmp\n" "$NAME" "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX" "$EMIT_EXE_DEBUG_ARGS" "$NAME"
    printf '\tmv $@.tmp $@\n'

    printf 'tasks.json: json/%s%s.tasks.json.debug.part\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
    printf 'json/%s%s.tasks.json.debug.part:\n' "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
    printf '\trm -f $@ $@.tmp\n'
    printf "\tmkdir -p \$(@D)\n"
    printf "\tprintf '    {\\\\n      \"label\": \"Build %s\",\\\\n      \"type\": \"shell\",\\\\n      \"command\": \"make out/exe/%s%s.exe\",\\\\n      \"options\": {\\\\n        \"cwd\": \"\$\${workspaceFolder}\",\\\\n      },\\\\n      \"problemMatcher\": [\"\$\$gcc\"]\\\\n    },\\\\n' > \$@.tmp\n" "$NAME" "$EMIT_EXE_EXE_NAME" "$EMIT_EXE_SUFFIX"
    printf '\tmv $@.tmp $@\n'
  fi
}

# emut exe link rule
emit_link() {
  EMIT_LINK_EXE_NAME=$1
  EMIT_LINK_DEFAULT_SUFFIX=$2

  printf '%s: out/exe/%s%s.exe\n' "$EMIT_LINK_EXE_NAME" "$EMIT_LINK_EXE_NAME" "$EMIT_LINK_DEFAULT_SUFFIX"
  printf '\tln -s $< $@\n'
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
    emit_o "$SRC_PATH" ".-fPIC.$MINIRT_PRECISION" "-fPIC -DMINIRT_PRECISION=$MINIRT_PRECISION -O"
    emit_o "$SRC_PATH" ".-fPIC.$MINIRT_PRECISION.debug" "-fPIC -DMINIRT_PRECISION=$MINIRT_PRECISION -g"
    emit_o "$SRC_PATH" ".-fPIC.$MINIRT_PRECISION.debug.address" "-fPIC -DMINIRT_PRECISION=$MINIRT_PRECISION -g -fsanitize=address"
  }

  print_a() {
    LIB_NAME="$1"
    LIB_SOURCES="$2"

    emit_a "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION"
    emit_a "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION.debug"
    emit_a "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION.debug.address"
  }

  print_so() {
    LIB_NAME="$1"
    LIB_SOURCES="$2"

    emit_so "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION"
    emit_so "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION.debug"
    emit_so "$LIB_NAME" "$LIB_SOURCES" ".$MINIRT_PRECISION.debug.address" "-fsanitize=address"
  }

  print_exe() {
    EXE_NAME="$1"
    DEPENDENCY_LIBS="$2"

    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION" "$DEPENDENCY_LIBS"
    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION.debug" "$DEPENDENCY_LIBS" "" 1
    emit_exe "$EXE_NAME" ".$MINIRT_PRECISION.debug.address" "$DEPENDENCY_LIBS" "-fsanitize=address" 1
  }

  while IFS="=" read -r lib_name lib_path;
  do
    if [ "$lib_path" = "" ]; then
      lib_path="$lib_name"
    fi

    print_a "$lib_name" "$lib_path"
  done < ../data/a.properties

  while IFS="=" read -r lib_name lib_path;
  do
    print_so "$lib_name" "$lib_path"
  done < ../data/so.properties

  while IFS="=" read -r exe_name dependency_libs;
  do
    print_exe "$exe_name" "$dependency_libs"
  done < ../data/exe.properties

  find ../src/exe -name '*.c' | grep -v /test/ | cut -c 8- | sort | while IFS= read -r FILE
  do
    print_exe_obj "$FILE"
  done

  find ../src/lib -name '*.c' | grep -v /test/ | cut -c 8- | sort | while IFS= read -r FILE
  do
    print_lib_obj "$FILE"
  done

done

while IFS="=" read -r exe_name dependency_libs;
do
  emit_link "$exe_name" ".1"
done < ../data/exe.properties
