cmake_minimum_required(VERSION 3.5)
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

file(GLOB_RECURSE SRC_LIB_COMMON "src/lib/common/*.c")
file(GLOB_RECURSE SRC_EXE_PACK "src/exe/pack/*.c")

foreach(MINIRT_PRECISION 0 1 2)

  add_library(minirt_common.${MINIRT_PRECISION} STATIC ${SRC_LIB_COMMON})
  target_compile_definitions(minirt_common.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${PRECISION})

  add_executable(pack.${MINIRT_PRECISION} ${SRC_EXE_PACK})
  target_compile_definitions(pack.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${PRECISION})
  target_link_libraries(pack.${MINIRT_PRECISION} minirt_common.${MINIRT_PRECISION})

endforeach()
