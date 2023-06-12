TARGET = minirt.exe libminirt.so
EXTRA_TARGET = libminirt_bmp.a libminirt_core.a
EVERYTHING = $(TARGET) $(EXTRA_TARGET)

all: $(TARGET)
.PHONY: all

.PHONY: everything
everything: $(EVERYTHING)

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -f $(EVERYTHING)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

$(EVERYTHING): build
	cd build && make $@
	cp build/$@ .

.PHONY: norm
norm: build
	cd build && make -k norm

.PHONY: build
build:
	sh script/make_build.sh
