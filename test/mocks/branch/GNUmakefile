BASE_PATH := ../../..
CURRENT_PATH := test/mocks/branch

TARGET := out/mock_branch.a

OBJS := $(patsubst src/%.c,build/objs/%.o,$(shell find src -name "*.c"))

all: $(TARGET)
.PHONY: all

CPPFLAGS := -Iinclude -Isrc/include -I$(BASE_PATH)/test/branch/include
CFLAGS := -Wall -Wextra -Werror

include $(BASE_PATH)/test/mk/cc_use_deps.mk

build/objs/%.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.d $<
endif
	mv $@.tmp $@

$(TARGET): $(OBJS)
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	ar cr $@.tmp $^
	mv $@.tmp $@

.PHONY: clean
clean:
	rm -rf objs deps

.PHONY: fclean
fclean: clean
	rm -rf out

.PHONY: re
re: fclean
	$(MAKE) all

include $(BASE_PATH)/test/mk/norm.mk

ifeq ($(USE_DEPS), 1)
include $(shell [ ! -d build/deps ] || find build/deps -name "*.d")
endif
