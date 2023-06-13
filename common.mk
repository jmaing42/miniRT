TARGET = \
	minirt.0.exe \
	minirt.1.exe \
	minirt.2.exe \
	libminirt.0.so \
	libminirt.1.so \
	libminirt.2.so \

EXTRA_TARGET = \
	libminirt_bmp.0.a \
	libminirt_bmp.1.a \
	libminirt_bmp.2.a \
	libminirt_common.0.a \
	libminirt_common.1.a \
	libminirt_common.2.a \
	libminirt_core.0.a \
	libminirt_core.1.a \
	libminirt_core.2.a \
	libminirt_json.0.a \
	libminirt_json.1.a \
	libminirt_json.2.a \
	libminirt_plugin_rtinrt.0.a \
	libminirt_plugin_rtinrt.1.a \
	libminirt_plugin_rtinrt.2.a \
	libminirt_plugin_portal.0.a \
	libminirt_plugin_portal.1.a \
	libminirt_plugin_portal.2.a \
	libminirt_scene.0.a \
	libminirt_scene.1.a \
	libminirt_scene.2.a \
	minirt_validate.0.exe \
	minirt_validate.1.exe \
	minirt_validate.2.exe \

DEBUG_TARGET = \
	minirt.0.debug.exe \
	minirt.1.debug.exe \
	minirt.2.debug.exe \
	minirt.0.debug.address.exe \
	minirt.1.debug.address.exe \
	minirt.2.debug.address.exe \
	minirt_validate.0.debug.exe \
	minirt_validate.1.debug.exe \
	minirt_validate.2.debug.exe \
	minirt_validate.0.debug.address.exe \
	minirt_validate.1.debug.address.exe \
	minirt_validate.2.debug.address.exe \

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
