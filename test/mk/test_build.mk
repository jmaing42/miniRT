TEST_EXE_PATH := build/test.exe

OBJS := $(patsubst src/%.c,build/objs/%.o,$(shell find src -name "*.c"))

include $(BASE_PATH)/test/mk/cc_use_deps.mk

build/objs/%.o: src/%.c
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@.tmp $<
ifeq ($(USE_DEPS), 1)
	mkdir -p $$(dirname "build/deps/$*.d")
	$(CC) $(CPPFLAGS) -MM -MT $@ -MF build/deps/$*.d $<
endif
	mv $@.tmp $@

$(TEST_EXE_PATH): $(OBJS) test_build_prelaunch_task
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@.tmp
	mv $@.tmp $@

.PHONY: clean_test_build
clean: clean_test_build
clean_test_build:
	rm -rf build
