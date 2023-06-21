TARGET = \
	minirt \
	minirt_validate \
	pack \

EVERYTHING = $(TARGET)

-include targets.mk

all:
.PHONY: all

.PHONY: everything
everything: error_if_targets_not_included .vscode/launch.json .vscode/tasks.json

.PHONY: error_if_targets_not_included
error_if_targets_not_included:
	@$(FLAG_IF_TARGETS_INCLUDED)([ -t 1 ] && printf "\033[0;31m[ERROR]\033[0m" || printf "[ERROR]")
	@$(FLAG_IF_TARGETS_INCLUDED)echo " targets.mk is not generated. run \`sh metamake.sh\` once."
	@$(FLAG_IF_TARGETS_INCLUDED)false

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -rf out .vscode/launch.json .vscode/tasks.json targets.mk CMakeLists.txt

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: dev
dev: .vscode/launch.json .vscode/tasks.json
