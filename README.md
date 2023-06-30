# miniRT

**mini** scene renderer using **R**ay **T**racing.

## Usage

Using pack file, without options

```shell
minirt < myScene.pack > result.bmp
```

Using options

```shell
minirt --input="myScene.rt" --base=".." --output="result.bmp"
```

Use the `--help` option to see how to use individual executables.

## Build

Supported platforms are POSIX-like systems (such as Linux, macOS) and Windows

### POSIX-like systems

```shell
# optional
sh metamake.sh

# build
make MINIRT_PRECISION=1
```

If above fails (because your environment has fake gcc/clang), try below

```shell
echo "CC = cc" > common.mk

USE_DEPS=0 make
```

### Windows

Building on Windows requires CMake and a suitable build system.

```shell
# create CMakeLists.txt
metacmake

# for example
cmake -B builddir -G "Visual Studio 17 2022" -DMINIRT_PRECISION="double"

# build
cmake --build builddir
```

## Test

Testing is available if GNU Make and AddressSanitizer is available.

```shell
sh metamake.sh
V=1 gmake test -s
# or `make` instead of `gmake`
```
