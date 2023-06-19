#!/bin/sh

set -e

cd "$(dirname "$0")"

echo '# ################ AUTO-GENERATED ################ #

cmake_minimum_required(VERSION 2.8.12)
project(miniRT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
if (CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()
if (MSVC)
  add_compile_options(/W4 /WX)
endif()

include_directories(include)
include_directories(src/include)


file(GLOB_RECURSE SRC_LIB "src/lib/*.c")
add_library(minirt.${MINIRT_PRECISION} ${SRC_LIB})

'

cat ../data/a.properties | while IFS="=" read -r lib_name lib_path;
do
  printf 'file(GLOB_RECURSE SRC_A_%s "src/lib/%s/*.c")\n' "$lib_name" "$lib_path"
  printf 'foreach(MINIRT_PRECISION 0 1 2)\n'
  printf '  add_library(a_minirt_%s.${MINIRT_PRECISION} STATIC ${SRC_A_%s})\n' "$lib_name" "$lib_name"
  printf '  target_compile_definitions(a_minirt_%s.${MINIRT_PRECISION} PUBLIC MINIRT_PRECISION=${MINIRT_PRECISION})\n' "$lib_name"
  printf '  set_target_properties(a_minirt_%s.${MINIRT_PRECISION} PROPERTIES OUTPUT_NAME "minirt_%s")\n' "$lib_name" "$lib_name"
  printf 'endforeach()\n'
done

cat ../data/so.properties | while IFS="=" read -r lib_name lib_paths;
do
  FULL_LIB_NAME="minirt_$lib_name"
  if [ "FULL_LIB_NAME" = "minirt_" ]; then
    FULL_LIB_NAME="minirt"
  fi

  printf 'file(GLOB_RECURSE SRC_SO_%s %s)\n' "$lib_name" "$(echo "$lib_paths" | xargs -n 1 echo | sed 's#^#"src/lib/#' | sed 's#$#/*.c"#' | xargs)"
  printf 'foreach(MINIRT_PRECISION 0 1 2)\n'
  printf '  add_library(so_%s.${MINIRT_PRECISION} STATIC ${SRC_SO_%s})\n' "$FULL_LIB_NAME" "$lib_name"
  printf '  target_compile_definitions(so_%s.${MINIRT_PRECISION} PUBLIC MINIRT_PRECISION=${MINIRT_PRECISION})\n' "$FULL_LIB_NAME"
  printf '  set_target_properties(so_%s.${MINIRT_PRECISION} PROPERTIES OUTPUT_NAME "%s")\n' "$FULL_LIB_NAME" "$FULL_LIB_NAME"
  printf 'endforeach()\n'
done

cat ../data/exe.properties | while IFS="=" read -r exe_name dependencies;
do
  printf 'file(GLOB_RECURSE SRC_EXE_%s "src/exe/%s/*.c")\n' "$exe_name" "$exe_name"
  printf 'foreach(MINIRT_PRECISION 0 1 2)\n'
  printf '  add_executable(%s.${MINIRT_PRECISION} ${SRC_EXE_%s})\n' "$exe_name" "$exe_name"
  printf '  target_compile_definitions(%s.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})\n' "$exe_name"
  printf '  target_link_libraries(%s.${MINIRT_PRECISION} %s)\n' "$exe_name" "$(echo "$dependencies" | xargs -n 1 echo | sed s/^/a_minirt_/ | sed 's/$/.\${MINIRT_PRECISION}/' | xargs)"
  printf 'endforeach()\n'
done
