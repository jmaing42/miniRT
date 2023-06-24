BASE_PATH := ../../../../..
CURRENT_PATH := test/mocks/branch/test/1_malloc_free_ok

include $(BASE_PATH)/test/mk/prelude.mk

.PHONY: default_target
default_target: test

include $(BASE_PATH)/test/mk/test_build.mk

TEST_TYPE := out_diff
TEST_DATA_PATH := ./data.txt

CFLAGS := -fsanitize=address -g
CPPFLAGS := -I../../include -I../../../../branch/include
LDFLAGS := -fsanitize=address
LOADLIBES := -L../../out -L../../../../branch/out
LDLIBS := -lmock_branch.debug.address -lbranch.debug.address

include $(BASE_PATH)/test/mk/test.mk

.NOTPARALLEL: test_build_prelaunch_task
test_build_prelaunch_task:
	$(MAKE) -C ../..
	$(MAKE) -C ../../../../branch
