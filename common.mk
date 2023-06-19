TARGET = \
	out/exe/minirt.0.exe \
	out/exe/minirt.1.exe \
	out/exe/minirt.2.exe \
	out/exe/minirt_validate.0.exe \
	out/exe/minirt_validate.1.exe \
	out/exe/minirt_validate.2.exe \
	out/exe/pack.0.exe \
	out/exe/pack.1.exe \
	out/exe/pack.2.exe \
	out/so/libminirt.0.so \
	out/so/libminirt.1.so \
	out/so/libminirt.2.so \
	out/so/libminirt_plugin_portal.0.so \
	out/so/libminirt_plugin_portal.1.so \
	out/so/libminirt_plugin_portal.2.so \
	out/so/libminirt_plugin_rtinrt.0.so \
	out/so/libminirt_plugin_rtinrt.1.so \
	out/so/libminirt_plugin_rtinrt.2.so \

EXTRA_TARGET = \
	out/a/libminirt_bmp.0.a \
	out/a/libminirt_bmp.1.a \
	out/a/libminirt_bmp.2.a \
	out/a/libminirt_common.0.a \
	out/a/libminirt_common.1.a \
	out/a/libminirt_common.2.a \
	out/a/libminirt_core.0.a \
	out/a/libminirt_core.1.a \
	out/a/libminirt_core.2.a \
	out/a/libminirt_json.0.a \
	out/a/libminirt_json.1.a \
	out/a/libminirt_json.2.a \
	out/a/libminirt_plugin_rtinrt.0.a \
	out/a/libminirt_plugin_rtinrt.1.a \
	out/a/libminirt_plugin_rtinrt.2.a \
	out/a/libminirt_plugin_portal.0.a \
	out/a/libminirt_plugin_portal.1.a \
	out/a/libminirt_plugin_portal.2.a \
	out/a/libminirt_scene.0.a \
	out/a/libminirt_scene.1.a \
	out/a/libminirt_scene.2.a \

DEBUG_TARGET = \
	out/exe/minirt.0.debug.exe \
	out/exe/minirt.1.debug.exe \
	out/exe/minirt.2.debug.exe \
	out/exe/minirt.0.debug.address.exe \
	out/exe/minirt.1.debug.address.exe \
	out/exe/minirt.2.debug.address.exe \
	out/exe/minirt_validate.0.debug.exe \
	out/exe/minirt_validate.1.debug.exe \
	out/exe/minirt_validate.2.debug.exe \
	out/exe/minirt_validate.0.debug.address.exe \
	out/exe/minirt_validate.1.debug.address.exe \
	out/exe/minirt_validate.2.debug.address.exe \
	out/exe/pack.0.debug.exe \
	out/exe/pack.1.debug.exe \
	out/exe/pack.2.debug.exe \
	out/exe/pack.0.debug.address.exe \
	out/exe/pack.1.debug.address.exe \
	out/exe/pack.2.debug.address.exe \
	out/so/libminirt.0.debug.so \
	out/so/libminirt.1.debug.so \
	out/so/libminirt.2.debug.so \
	out/so/libminirt.0.debug.address.so \
	out/so/libminirt.1.debug.address.so \
	out/so/libminirt.2.debug.address.so \
	out/so/libminirt_plugin_portal.0.debug.so \
	out/so/libminirt_plugin_portal.1.debug.so \
	out/so/libminirt_plugin_portal.2.debug.so \
	out/so/libminirt_plugin_portal.0.debug.address.so \
	out/so/libminirt_plugin_portal.1.debug.address.so \
	out/so/libminirt_plugin_portal.2.debug.address.so \
	out/so/libminirt_plugin_rtinrt.0.debug.so \
	out/so/libminirt_plugin_rtinrt.1.debug.so \
	out/so/libminirt_plugin_rtinrt.2.debug.so \
	out/so/libminirt_plugin_rtinrt.0.debug.address.so \
	out/so/libminirt_plugin_rtinrt.1.debug.address.so \
	out/so/libminirt_plugin_rtinrt.2.debug.address.so \

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
