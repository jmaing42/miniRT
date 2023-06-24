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

.PHONY: build
build:
	mkdir -p build && sh script/build_refresh_makefile.sh

.PHONY: clean_targets
clean: clean_targets
clean_targets:
	rm -f $(TARGET)

.vscode/launch.json: build
	(cd build && $(MAKE) launch.json)
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	(cd build && $(MAKE) tasks.json)
	cp build/tasks.json .vscode/tasks.json

.PHONY: test norm
test norm:
	[ -t 2 ] && printf "\033[0;31m[ERROR]\033[0m" 1>&2 || printf "[ERROR]" 1>&2
	printf ' test is only available for GNU Make\n' 1>&2
