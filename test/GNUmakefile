include mk/prelude.mk

clean:
	$(MAKE) -C branch clean
	$(MAKE) -C mocks clean

fclean:
	$(MAKE) -C branch fclean
	$(MAKE) -C mocks fclean

.PHONY: default_target
default_target: test

.PHONY: test
test:
	find . -type d -name test | sort | xargs -L1 $(MAKE) -C
