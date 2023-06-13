TARGET = minirt.exe libminirt.so

EXTRA_TARGET = \
	libminirt_bmp.a \
	libminirt_common.a \
	libminirt_core.a \
	libminirt_json.a \
	libminirt_plugin_rtinrt.a \
	libminirt_plugin_portal.a \
	libminirt_scene.a \
	minirt_validate.exe \

DEBUG_TARGET = \
	minirt.debug.exe \
	minirt.debug.address.exe \
	minirt_validate.debug.exe \
	minirt_validate.debug.address.exe \

EVERYTHING = $(TARGET) $(EXTRA_TARGET) $(DEBUG_TARGET)

all: $(TARGET)
.PHONY: all

.PHONY: everything
everything: $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -f $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: dev
dev: .vscode/launch.json .vscode/tasks.json

$(EVERYTHING): build
	(cd build && make $@)
	cp build/$@ .

.PHONY: norm
norm: build
	(cd build && make -k norm)

.PHONY: build
build:
	sh script/make_build.sh

.vscode/launch.json: build
	(cd build && make launch.json)
	cp build/launch.json .vscode/launch.json
.vscode/tasks.json: build
	(cd build && make tasks.json)
	cp build/tasks.json .vscode/tasks.json
