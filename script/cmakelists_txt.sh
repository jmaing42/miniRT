#!/bin/sh

set -e

cd "$(dirname "$0")"

echo "# ################ AUTO-GENERATED ################ #

cmake_minimum_required(VERSION 2.8.12)
project(miniRT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
if (CMAKE_C_COMPILER_ID MATCHES \"Clang\" OR CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()
if (MSVC)
  add_compile_options(/W4 /WX /wd4200)
endif()

include_directories(include)
include_directories(src/include)


option(MINIRT_PRECISION \"precision to use in miniRT (valid values: float, double, long double)\" \"\")

if (NOT MINIRT_PRECISION)
  set(MINIRT_PRECISION_VALUE 1)
elseif (MINIRT_PRECISION STREQUAL \"float\")
  set(MINIRT_PRECISION_VALUE 0)
elseif (MINIRT_PRECISION STREQUAL \"double\")
  set(MINIRT_PRECISION_VALUE 1)
elseif (MINIRT_PRECISION STREQUAL \"long double\")
  set(MINIRT_PRECISION_VALUE 2)
else()
  message(FATAL_ERROR \"Invalid value for MINIRT_PRECISION. Valid values are: float, double, or long double.\")
endif()

add_definitions(-DMINIRT_PRECISION=\${MINIRT_PRECISION_VALUE})

"

while IFS="=" read -r lib_name lib_path;
do
  if [ "$lib_path" = "" ]; then
    lib_path="$lib_name"
  fi

  printf 'file(GLOB_RECURSE SRC_A_%s "src/lib/%s/*.c")\n' "$lib_name" "$lib_path"
  printf "add_library(a_minirt_%s.\${MINIRT_PRECISION_VALUE} STATIC \${SRC_A_%s})\n" "$lib_name" "$lib_name"
  printf "set_target_properties(a_minirt_%s.\${MINIRT_PRECISION_VALUE} PROPERTIES OUTPUT_NAME \"minirt_%s.\${MINIRT_PRECISION_VALUE}\")\n" "$lib_name" "$lib_name"
done < ../data/a.properties

while IFS="=" read -r lib_name lib_paths;
do
  FULL_LIB_NAME="minirt_$lib_name"
  if [ "$FULL_LIB_NAME" = "minirt_" ]; then
    FULL_LIB_NAME="minirt"
  fi

  printf 'file(GLOB_RECURSE SRC_SO_%s %s)\n' "$lib_name" "$(echo "$lib_paths" | xargs -n 1 echo | sed 's#^#"src/lib/#' | sed 's#$#/*.c"#' | xargs)"
  printf "add_library(so_%s.\${MINIRT_PRECISION_VALUE} STATIC \${SRC_SO_%s})\n" "$FULL_LIB_NAME" "$lib_name"
  printf "set_target_properties(so_%s.\${MINIRT_PRECISION_VALUE} PROPERTIES OUTPUT_NAME \"%s.\${MINIRT_PRECISION_VALUE}\")\n" "$FULL_LIB_NAME" "$FULL_LIB_NAME"
done < ../data/so.properties

while IFS="=" read -r exe_name dependencies;
do
  printf 'file(GLOB_RECURSE SRC_EXE_%s "src/exe/%s/*.c")\n' "$exe_name" "$exe_name"
  printf "add_executable(%s.\${MINIRT_PRECISION_VALUE} \${SRC_EXE_%s})\n" "$exe_name" "$exe_name"
  printf "target_link_libraries(%s.\${MINIRT_PRECISION_VALUE} %s)\n" "$exe_name" "$(echo "$dependencies" | xargs -n 1 echo | sed s/^/a_minirt_/ | sed "s/$/.\${MINIRT_PRECISION_VALUE}/" | xargs)"
done < ../data/exe.properties
