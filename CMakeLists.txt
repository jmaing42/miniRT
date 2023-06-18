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

file(GLOB_RECURSE SRC_LIB_ARGS "src/lib/args/*.c")
file(GLOB_RECURSE SRC_LIB_BMP "src/lib/bmp/*.c")
file(GLOB_RECURSE SRC_LIB_COMMON "src/lib/common/*.c")
file(GLOB_RECURSE SRC_LIB_CORE "src/lib/core/*.c")
file(GLOB_RECURSE SRC_LIB_JSON "src/lib/json/*.c")
file(GLOB_RECURSE SRC_LIB_PACK "src/lib/pack/*.c")
file(GLOB_RECURSE SRC_LIB_PLUGIN_RTINRT "src/lib/plugin_rtinrt/*.c")
file(GLOB_RECURSE SRC_LIB_PLUGIN_PORTAL "src/lib/plugin_portal/*.c")
file(GLOB_RECURSE SRC_LIB_SCENE "src/lib/scene/*.c")

file(GLOB_RECURSE SRC_EXE_MINIRT "src/exe/minirt/*.c")
file(GLOB_RECURSE SRC_EXE_MINIRT_VALIDATE "src/exe/minirt_validate/*.c")
file(GLOB_RECURSE SRC_EXE_PACK "src/exe/pack/*.c")

foreach(MINIRT_PRECISION 0 1 2)


  add_library(minirt_args.${MINIRT_PRECISION} STATIC ${SRC_LIB_ARGS})
  target_compile_definitions(minirt_args.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_bmp.${MINIRT_PRECISION} STATIC ${SRC_LIB_BMP})
  target_compile_definitions(minirt_bmp.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_common.${MINIRT_PRECISION} STATIC ${SRC_LIB_COMMON})
  target_compile_definitions(minirt_common.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_core.${MINIRT_PRECISION} STATIC ${SRC_LIB_CORE})
  target_compile_definitions(minirt_core.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_json.${MINIRT_PRECISION} STATIC ${SRC_LIB_JSON})
  target_compile_definitions(minirt_json.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_pack.${MINIRT_PRECISION} STATIC ${SRC_LIB_PACK})
  target_compile_definitions(minirt_pack.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_plugin_portal.${MINIRT_PRECISION} STATIC ${SRC_LIB_PLUGIN_PORTAL})
  target_compile_definitions(minirt_plugin_portal.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_plugin_rtinrt.${MINIRT_PRECISION} STATIC ${SRC_LIB_PLUGIN_RTINRT})
  target_compile_definitions(minirt_plugin_rtinrt.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})

  add_library(minirt_scene.${MINIRT_PRECISION} STATIC ${SRC_LIB_SCENE})
  target_compile_definitions(minirt_scene.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})


  add_executable(minirt.${MINIRT_PRECISION} ${SRC_EXE_MINIRT})
  target_compile_definitions(minirt.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})
  target_link_libraries(minirt.${MINIRT_PRECISION} minirt_args.${MINIRT_PRECISION} minirt_bmp.${MINIRT_PRECISION} minirt_common.${MINIRT_PRECISION} minirt_core.${MINIRT_PRECISION} minirt_json.${MINIRT_PRECISION} minirt_plugin_portal.${MINIRT_PRECISION} minirt_plugin_rtinrt.${MINIRT_PRECISION} minirt_scene.${MINIRT_PRECISION})

  add_executable(minirt_validate.${MINIRT_PRECISION} ${SRC_EXE_MINIRT_VALIDATE})
  target_compile_definitions(minirt_validate.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})
  target_link_libraries(minirt_validate.${MINIRT_PRECISION} minirt_args.${MINIRT_PRECISION} minirt_common.${MINIRT_PRECISION} minirt_json.${MINIRT_PRECISION} minirt_plugin_portal.${MINIRT_PRECISION} minirt_plugin_rtinrt.${MINIRT_PRECISION} minirt_scene.${MINIRT_PRECISION})

  add_executable(pack.${MINIRT_PRECISION} ${SRC_EXE_PACK})
  target_compile_definitions(pack.${MINIRT_PRECISION} PRIVATE MINIRT_PRECISION=${MINIRT_PRECISION})
  target_link_libraries(pack.${MINIRT_PRECISION} minirt_args.${MINIRT_PRECISION} minirt_common.${MINIRT_PRECISION} minirt_pack.${MINIRT_PRECISION})


endforeach()
