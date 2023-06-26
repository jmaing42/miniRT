BASE_PATH := ../../../..
CURRENT_PATH := test/mocks/branch/test

include $(BASE_PATH)/test/mk/prelude.mk

.PHONY: default_target
default_target: test

.PHONY: test
test:
	echo */ | xargs -n 1 $(MAKE) -C
