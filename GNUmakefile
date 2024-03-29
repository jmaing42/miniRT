include common.mk

.NOTPARALLEL: $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

MINIRT_PRECISION ?= $(shell [ -f  .MINIRT_PRECISION.flag ] && cat .MINIRT_PRECISION.flag || printf "1")

ifeq ($(filter $(MINIRT_PRECISION),0 1 2),)
	$(error MINIRT_PRECISION must be set to 0, 1, or 2)
endif

TMP := $(shell printf "%s" "$(MINIRT_PRECISION)" > .MINIRT_PRECISION.flag)

export MINIRT_PRECISION

clean: clean_minirt_precision_flag
.PHONY: clean_minirt_precision_flag
clean_minirt_precision_flag:
	rm -f .MINIRT_PRECISION.flag

EVERYTHING := $(if $(filter $(FLAG_IF_TARGETS_INCLUDED), true), $(EVERYTHING), $(TARGET))
EVERYTHING := $(shell echo $(EVERYTHING) | xargs -n 1 echo | grep \\.$(MINIRT_PRECISION) | xargs) $(shell echo $(EVERYTHING) | xargs -n 1 echo | grep -v \\. | xargs)
TARGET := $(shell echo $(TARGET) | xargs -n 1 echo | grep \\.$(MINIRT_PRECISION) | xargs) $(shell echo $(TARGET) | xargs -n 1 echo | grep -v \\. | xargs)

all: $(TARGET)
everything: $(EVERYTHING)

-include include.mk

MAKEFLAGS = -j 1

MAKE_J = $(MAKE) -j $(shell sh script/nproc.sh)

$(EVERYTHING): build
	$(MAKE_J) -C build -f $(MINIRT_PRECISION).mk $@
	mkdir -p $(@D)
	cp build/$@ $@

.PHONY: norm
norm: build
	$(MAKE_J) -C build -f $(MINIRT_PRECISION).mk -k norm

.PHONY: build
build:
	mkdir -p build && sh script/build_refresh_gnumakefile.sh $(MINIRT_PRECISION)

.PHONY: clean_targets
clean: clean_targets
clean_targets:
	rm -f $(TARGET)

.PHONY: clean_test
clean: clean_test
clean_test:
	$(MAKE) -C test clean
	find src -name test -type d | xargs -n 1 $(MAKE) clean -C

.PHONY: fclean_test
fclean: fclean_test
fclean_test:
	$(MAKE) -C test fclean
	find src -name test -type d | xargs -n 1 $(MAKE) fclean -C

.vscode/launch.json: build
	$(MAKE_J) -C build -f $(MINIRT_PRECISION).mk launch.json
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	$(MAKE_J) -C build -f $(MINIRT_PRECISION).mk tasks.json
	cp build/tasks.json .vscode/tasks.json

.PHONY: test
test:
	$(MAKE) -C test
	find src -type d -name test | sort | xargs -L1 $(MAKE) -C
