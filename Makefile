##############################################################################
#                                                                            #
# This is POSIX-compliant version. for general use, see GNUmakefile instead. #
#                                                                            #
##############################################################################

include common.mk

all: $(TARGET)
everything: $(EVERYTHING)

-include include.mk

$(EVERYTHING): build
	(cd build && $(MAKE) $@)
	mkdir -p $(@D)
	cp build/$@ $@

.PHONY: norm
norm: build
	(cd build && $(MAKE) -k norm)

.PHONY: build
build:
	mkdir -p build && sh script/build_refresh_makefile.sh

.vscode/launch.json: build
	(cd build && $(MAKE) launch.json)
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	(cd build && $(MAKE) tasks.json)
	cp build/tasks.json .vscode/tasks.json
