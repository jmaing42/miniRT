include $(BASE_PATH)/test/mk/prelude.mk

.PHONY: default_target
default_target: test

include $(BASE_PATH)/test/mk/test_build.mk

TEST_TYPE := inout_args_diff
TEST_DATA_PATH := ./data

include $(BASE_PATH)/test/mocks/branch/mock_branch_include.debug.mk

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
CPPFLAGS := -I$(BASE_PATH)/include
LDFLAGS := $(MOCK_BRANCH_LDFLAGS) -fsanitize=address
LOADLIBES := -L$(BASE_PATH)/build/out/a -L$(BASE_PATH)/test/branch/out -L$(BASE_PATH)/test/mocks/branch/out -L../0_common/out
LDLIBS := -lmain $(MOCK_BRANCH_LDLIBS) -lminirt_args.$(MINIRT_PRECISION).debug.address -lminirt_common.$(MINIRT_PRECISION).debug.address -lmock_branch.debug.address -lbranch.debug.address

include $(BASE_PATH)/test/mk/test.mk

.NOTPARALLEL: test_build_prelaunch_task
test_build_prelaunch_task:
	$(MAKE) -C $(BASE_PATH) out/a/libminirt_common.$(MINIRT_PRECISION).debug.address.a out/a/libminirt_args.$(MINIRT_PRECISION).debug.address.a
	$(MAKE) -C $(BASE_PATH)/test/branch out/libbranch.debug.address.a
	$(MAKE) -C $(BASE_PATH)/test/mocks/branch out/libmock_branch.debug.address.a
	$(MAKE) -C ../0_common
