MOCK_BRANCH_UNAME_S := $(shell uname -s)
ifeq ($(MOCK_BRANCH_UNAME_S),Linux)
MOCK_BRANCH_LDFLAGS := -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=close -Wl,--wrap=read -Wl,--wrap=write
else
ifeq ($(MOCK_BRANCH_UNAME_S),Darwin)
MOCK_BRANCH_LDLIBS := -ldl $(BASE_PATH)/test/mocks/branch/out/libmock_branch.debug.a
else
$(error Unrecognized OS: $(MOCK_BRANCH_UNAME_S))
endif
endif
