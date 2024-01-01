@echo off

cd "%~dp0"

echo ^# ################ AUTO-GENERATED ################ #
echo.
echo cmake_minimum_required(VERSION 2.8.12)
echo project(miniRT C)
echo.
echo set(CMAKE_C_STANDARD 99)
echo set(CMAKE_C_STANDARD_REQUIRED ON)
echo if (CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCC^)
echo   add_compile_options(-Wall -Wextra -Werror -pedantic^)
echo endif(^)
echo if (MSVC^)
echo   add_compile_options(/W4 /WX /wd4200^)
echo endif(^)
echo.
echo include_directories(include)
echo include_directories(src/include)
echo.
echo.
echo option(MINIRT_PRECISION "precision to use in miniRT (valid values: float, double, long double)" ""^)
echo.
echo if (NOT MINIRT_PRECISION^)
echo   set(MINIRT_PRECISION_VALUE 1^)
echo elseif (MINIRT_PRECISION STREQUAL "float"^)
echo   set(MINIRT_PRECISION_VALUE 0^)
echo elseif (MINIRT_PRECISION STREQUAL "double"^)
echo   set(MINIRT_PRECISION_VALUE 1^)
echo elseif (MINIRT_PRECISION STREQUAL "long double"^)
echo   set(MINIRT_PRECISION_VALUE 2^)
echo else(^)
echo   message(FATAL_ERROR "Invalid value for MINIRT_PRECISION. Valid values are: float, double, or long double."^)
echo endif(^)
echo.
echo add_definitions(-DMINIRT_PRECISION=${MINIRT_PRECISION_VALUE}^)
echo.
echo.

setlocal enabledelayedexpansion

for /f "usebackq delims== tokens=1,2" %%A in ("..\data\a.properties") do (
  if "%%B"=="" (
    set LIB_PATH=%%A
  ) else (
    set LIB_PATH=%%B
  )
  echo file(GLOB_RECURSE SRC_A_%%A "src/lib/!LIB_PATH!/*.c"^)
  echo add_library(a_minirt_%%A.${MINIRT_PRECISION_VALUE} STATIC ${SRC_A_%%A}^)
  echo set_target_properties(a_minirt_%%A.${MINIRT_PRECISION_VALUE} PROPERTIES OUTPUT_NAME "minirt_%%A.${MINIRT_PRECISION_VALUE}"^)
)

for /f "usebackq delims== tokens=1,2" %%A in ("..\data\so.properties") do (
  if "%%B"=="" (
    set LIB_NAME=
    set DEPENDENCIES=%%A
  ) else (
    set LIB_NAME=%%A
    set DEPENDENCIES=%%B
  )

  set FULL_LIB_NAME=minirt_!LIB_NAME!
  if "!FULL_LIB_NAME!"=="minirt_" set FULL_LIB_NAME=minirt
  set SOURCES=
  for %%G in (!DEPENDENCIES!) do set SOURCES=!SOURCES! "src/lib/%%G/*.c"

  echo file(GLOB_RECURSE SRC_SO_!LIB_NAME!!SOURCES!^)
  echo add_library(so_!FULL_LIB_NAME!.${MINIRT_PRECISION_VALUE} STATIC ${SRC_SO_!LIB_NAME!}^)
  echo set_target_properties(so_!FULL_LIB_NAME!.${MINIRT_PRECISION_VALUE} PROPERTIES OUTPUT_NAME "!FULL_LIB_NAME!.${MINIRT_PRECISION_VALUE}"^)
)

for /f "usebackq delims== tokens=1,2" %%A in ("..\data\exe.properties") do (
  set DEPENDENCIES=
  for %%G in (%%B) do set DEPENDENCIES=!DEPENDENCIES! a_minirt_%%G.${MINIRT_PRECISION_VALUE}

  echo file(GLOB_RECURSE SRC_EXE_%%A "src/exe/%%A/*.c"^)
  echo add_executable(%%A.${MINIRT_PRECISION_VALUE} ${SRC_EXE_%%A}^)
  echo target_link_libraries(%%A.${MINIRT_PRECISION_VALUE}!DEPENDENCIES!^)
)
