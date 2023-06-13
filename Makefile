##############################################################################
#                                                                            #
# This is POSIX-compliant version. for general use, see GNUmakefile instead. #
#                                                                            #
##############################################################################

include common.mk

$(EVERYTHING): build
	(cd build && $(MAKE) $@)
	cp build/$@ .

.PHONY: norm
norm: build
	(cd build && $(MAKE) -k norm)

.PHONY: build
build:
	sh script/make_build.sh

.vscode/launch.json: build
	(cd build && $(MAKE) launch.json)
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	(cd build && $(MAKE) tasks.json)
	cp build/tasks.json .vscode/tasks.json
