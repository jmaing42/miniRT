TARGET := \
	out/libbranch.a \
	out/libbranch.debug.a \
	out/libbranch.debug.address.a \

all: $(TARGET)
.PHONY: all

SRCS := $(shell find src -name "*.c")

CC := $(shell (command -v clang > /dev/null && echo clang) || (command -v gcc > /dev/null && echo gcc) || (command -v cc > /dev/null && echo cc))
USE_DEPS ?= $(if $(filter gcc clang,$(CC)),1)

CPPFLAGS := -Iinclude -Isrc/include
CFLAGS := -Wall -Wextra -Werror

%.a:
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	ar cr $@.tmp $^
	mv $@.tmp $@

out/libbranch.a: $(patsubst src/%.c,objs/%.o,$(SRCS))
out/libbranch.debug.a: $(patsubst src/%.c,objs/%.debug.o,$(SRCS))
out/libbranch.debug.address.a: $(patsubst src/%.c,objs/%.debug.address.o,$(SRCS))

objs/%.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF deps/$*.d $<
endif
	mv $@.tmp $@

objs/%.debug.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "deps/$*.debug.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF deps/$*.debug.d $<
endif
	mv $@.tmp $@

objs/%.debug.address.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -fsanitize=address -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "deps/$*.debug.address.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF deps/$*.debug.address.d $<
endif
	mv $@.tmp $@

.PHONY: norm
norm: $(patsubst %,norm/%.norm,$(shell find . -name "*.c" -o -name "*.h" | cut -c 3-))

norm/%.norm: %
	(cd ../.. && norminette ./test/branch/$<)
	mkdir -p $(@D)
	touch $@

.PHONY: clean
clean:
	rm -rf objs deps norm

.PHONY: fclean
fclean: clean
	rm -rf out

.PHONY: re
re: fclean
	$(MAKE) all

include $(shell [ ! -d deps ] || find deps -name "*.d")
