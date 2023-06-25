MOCK_BRANCH_UNAME_S := $(shell uname -s)
ifneq ($(MOCK_BRANCH_UNAME_S),Linux)
MOCK_BRANCH_CPPFLAGS := -DMOCK_BRANCH_NO_WRAP
MOCK_BRANCH_LDFLAGS := -ldl
else
ifeq (($(MOCK_BRANCH_UNAME_S)),Darwin)
MOCK_BRANCH_LDFLAGS := -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=close -Wl,--wrap=read -Wl,--wrap=write
endif
$(error Unrecognized OS)
endif
