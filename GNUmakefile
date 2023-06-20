include common.mk

.NOTPARALLEL: $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

MINIRT_PRECISION ?= $(shell [ -f  .MINIRT_PRECISION.flag ] && cat .MINIRT_PRECISION.flag || printf "1")

ifeq ($(filter $(MINIRT_PRECISION),0 1 2),)
$(error MINIRT_PRECISION must be set to 0, 1, or 2)
endif

TMP := $(shell printf "%s" "$(MINIRT_PRECISION)" > .MINIRT_PRECISION.flag)

EVERYTHING := $(if $(filter $(FLAG_IF_TARGETS_INCLUDED), true), $(EVERYTHING), $(TARGET))
TARGET := $(shell echo $(EVERYTHING) | xargs -n 1 echo | grep \\.$(MINIRT_PRECISION) | xargs)

clean: clean_minirt_precision_flag
.PHONY: clean_minirt_precision_flag
clean_minirt_precision_flag:
	rm -f .MINIRT_PRECISION.flag

all: $(TARGET)

-include include.mk

MAKEFLAGS = -j 1

MAKE_J = $(MAKE) -j $(shell sh script/nproc.sh)

$(EVERYTHING): build
	$(MAKE_J) -C build $@
	mkdir -p $(@D)
	cp build/$@ $@

.PHONY: norm
norm: build
	$(MAKE_J) -C build -k norm

.PHONY: build
build:
	sh script/make_build.sh

.vscode/launch.json: build
	$(MAKE_J) -C build launch.json
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	$(MAKE_J) -C build tasks.json
	cp build/tasks.json .vscode/tasks.json
