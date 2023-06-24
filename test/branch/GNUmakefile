BASE_PATH := ../..
CURRENT_PATH := test/branch

TARGET := \
	out/libbranch.a \
	out/libbranch.debug.a \
	out/libbranch.debug.address.a \

all: $(TARGET)
.PHONY: all

SRCS := $(shell find src -name "*.c")

include $(BASE_PATH)/test/mk/cc_use_deps.mk

CPPFLAGS := -Iinclude -Isrc/include
CFLAGS := -Wall -Wextra -Werror

%.a:
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	ar cr $@.tmp $^
	mv $@.tmp $@

out/libbranch.a: $(patsubst src/%.c,build/objs/%.o,$(SRCS))
out/libbranch.debug.a: $(patsubst src/%.c,build/objs/%.debug.o,$(SRCS))
out/libbranch.debug.address.a: $(patsubst src/%.c,build/objs/%.debug.address.o,$(SRCS))

build/objs/%.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.d $<
endif
	mv $@.tmp $@

build/objs/%.debug.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.debug.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.debug.d $<
endif
	mv $@.tmp $@

build/objs/%.debug.address.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -fsanitize=address -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.debug.address.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.debug.address.d $<
endif
	mv $@.tmp $@

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -rf out

.PHONY: re
re: fclean
	$(MAKE) all

include $(BASE_PATH)/test/mk/norm.mk

ifeq ($(USE_DEPS), 1)
include $(shell [ ! -d deps ] || find deps -name "*.d")
endif
