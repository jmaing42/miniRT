include common.mk

.NOTPARALLEL: $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

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
