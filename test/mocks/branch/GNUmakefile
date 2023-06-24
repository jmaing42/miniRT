BASE_PATH := ../../..
CURRENT_PATH := test/mocks/branch

TARGET := \
	out/mock_branch_internal.o \
	out/mock_branch_start.o \
	out/mock_branch_stop.o \
	out/mock_branch_pause.o \
	out/mock_branch_resume.o \
	out/malloc.o \
	out/free.o \
	out/open.o \
	out/close.o \
	out/read.o \
	out/write.o \

all: $(TARGET)
.PHONY: all

SRCS := $(shell find src -name "*.c")

CPPFLAGS := -Iinclude -Isrc/include -I$(BASE_PATH)/test/branch/include
CFLAGS := -Wall -Wextra -Werror

out/%.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF deps/$*.d $<
endif
	mv $@.tmp $@

.PHONY: clean
clean:
	rm -rf deps

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
