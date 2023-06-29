include $(BASE_PATH)/test/mk/prelude.mk

.PHONY: default_target
default_target: test

include $(BASE_PATH)/test/mk/test_build.mk

TEST_TYPE := inout_args_diff
TEST_DATA_PATH := ./data

include $(BASE_PATH)/test/mocks/branch/mock_branch_include.debug.mk

CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -I$(BASE_PATH)/include
LDFLAGS := $(MOCK_BRANCH_LDFLAGS)
LOADLIBES := -L$(BASE_PATH)/build/out/a -L$(BASE_PATH)/test/branch/out -L$(BASE_PATH)/test/mocks/branch/out -L../0_common/out
LDLIBS := -lmain $(MOCK_BRANCH_LDLIBS) -lminirt_args.$(MINIRT_PRECISION) -lminirt_common.$(MINIRT_PRECISION) -lmock_branch.debug -lbranch.debug

include $(BASE_PATH)/test/mk/test.mk

.NOTPARALLEL: test_build_prelaunch_task
test_build_prelaunch_task:
	$(MAKE) -C $(BASE_PATH) build/out/a/libminirt_common.$(MINIRT_PRECISION).a build/out/a/libminirt_args.$(MINIRT_PRECISION).a
	$(MAKE) -C $(BASE_PATH)/test/branch
	$(MAKE) -C $(BASE_PATH)/test/mocks/branch
	$(MAKE) -C ../0_common
