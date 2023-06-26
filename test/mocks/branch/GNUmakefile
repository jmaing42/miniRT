BASE_PATH := ../../..
CURRENT_PATH := test/mocks/branch

TARGET := \
	out/libmock_branch.a \
	out/libmock_branch.debug.a \
	out/libmock_branch.debug.address.a \

all: $(TARGET)
.PHONY: all

CPPFLAGS := -Iinclude -Isrc/include -I$(BASE_PATH)/test/branch/include
CFLAGS := -Wall -Wextra -Werror

MOCK_BRANCH_UNAME_S := $(shell uname -s)
ifeq ($(MOCK_BRANCH_UNAME_S),Linux)
else
ifeq ($(MOCK_BRANCH_UNAME_S),Darwin)
CPPFLAGS += -DMOCK_BRANCH_NO_WRAP
else
$(error Unrecognized OS: $(MOCK_BRANCH_UNAME_S))
endif
endif

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

build/objs/%.debug.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.d $<
endif
	mv $@.tmp $@

build/objs/%.debug.address.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -fsanitize=address -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.d $<
endif
	mv $@.tmp $@

%.a:
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	ar cr $@.tmp $^
	mv $@.tmp $@

out/libmock_branch.a: $(patsubst src/%.c,build/objs/%.o,$(shell find src -name "*.c"))
out/libmock_branch.debug.a: $(patsubst src/%.c,build/objs/%.debug.o,$(shell find src -name "*.c"))
out/libmock_branch.debug.address.a: $(patsubst src/%.c,build/objs/%.debug.address.o,$(shell find src -name "*.c"))

.PHONY: clean
clean:
	rm -rf build
	$(MAKE) -C test clean

.PHONY: fclean
fclean:
	rm -rf build out
	$(MAKE) -C test fclean

.PHONY: re
re: fclean
	$(MAKE) all

include $(BASE_PATH)/test/mk/norm.mk

ifeq ($(USE_DEPS), 1)
include $(shell [ ! -d build/deps ] || find build/deps -name "*.d")
endif
