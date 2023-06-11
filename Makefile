TARGET = minirt.exe libminirt.so
EXTRA_TARGET = libminirt_core.a
ALL_TARGET = $(TARGET) $(EXTRA_TARGET)

all: $(TARGET)
.PHONY: all

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -f $(ALL_TARGET)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

$(ALL_TARGET): build
	cd build && make $@
	cp build/$@ .

build norm:
	sh script/make_$@.sh
