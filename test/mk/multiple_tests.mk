.PHONY: default_target
default_target: test

.PHONY: test
test:
	echo */ | xargs -n 1 $(MAKE) -C

clean:
	echo */ | xargs -n 1 $(MAKE) clean -C

fclean:
	echo */ | xargs -n 1 $(MAKE) fclean -C
