MOCK_BRANCH_UNAME_S := $(shell uname -s)
ifeq ($(MOCK_BRANCH_UNAME_S),Linux)
MOCK_BRANCH_LDFLAGS := -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=close -Wl,--wrap=read -Wl,--wrap=write
else
ifeq ($(MOCK_BRANCH_UNAME_S),Darwin)
MOCK_BRANCH_CPPFLAGS := -DMOCK_BRANCH_NO_WRAP
MOCK_BRANCH_LDFLAGS := -ldl
else
$(error Unrecognized OS: $(MOCK_BRANCH_UNAME_S))
endif
endif
