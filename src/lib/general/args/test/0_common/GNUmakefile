BASE_PATH := ../../../../../..
CURRENT_PATH := src/lib/general/args/test/0_common

include $(BASE_PATH)/test/mk/prelude.mk

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
CPPFLAGS := -I$(BASE_PATH)/include -I$(BASE_PATH)/test/branch/include -I$(BASE_PATH)/test/mocks/branch/include

include $(BASE_PATH)/test/mk/test_common_build.mk
