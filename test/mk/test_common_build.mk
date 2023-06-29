TARGET := out/libmain.a

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

$(TARGET): $(OBJS)
	rm -f $@ $@.tmp
	mkdir -p $(@D)
	ar cr $@.tmp $^
	mv $@.tmp $@

.PHONY: clean_test_build
clean: clean_test_build
clean_test_build:
	rm -rf build

.PHONY: fclean_test_build
fclean: fclean_test_build
fclean_test_build:
	rm -rf out

.PHONY: default_target
default_target: $(TARGET)
