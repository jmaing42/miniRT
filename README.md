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

### Windows

Building on Windows requires CMake and a suitable build system.

```shell
# create CMakeLists.txt
metacmake

# setup CMake build directory
mkdir builddir
cd builddir
# for example
cmake .. -G "Visual Studio 17 2022" -DMINIRT_PRECISION=1
cd ..

# build
cmake --build builddir
```
