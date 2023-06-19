TARGET = \
	out/exe/minirt.0.exe \
	out/exe/minirt.1.exe \
	out/exe/minirt.2.exe \

EVERYTHING = $(TARGET)

all:
.PHONY: all

.PHONY: error_no_targets
error_no_targets:
	@[ -t ] && printf "\033[0;31m[ERROR]\033[0m" || printf "[ERROR]" && echo " targets.mk is not generated. run \`sh metamake.sh\` once."
	@false
everything: error_no_targets
