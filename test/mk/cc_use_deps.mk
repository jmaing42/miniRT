CC := $(shell (command -v clang > /dev/null && echo clang) || (command -v gcc > /dev/null && echo gcc) || (command -v cc > /dev/null && echo cc))
USE_DEPS ?= $(if $(filter gcc clang,$(CC)),1)
