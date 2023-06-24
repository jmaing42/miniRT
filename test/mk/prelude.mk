all: default_target
.PHONY: all

.PHONY: clean
clean:

.PHONY: fclean
fclean: clean

.NOTPARALLEL: re
.PHONY: re
re: fclean
	$(MAKE) all
