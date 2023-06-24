.PHONY: norm
norm: $(patsubst %,build/norm/%.norm,$(shell find . -name "*.c" -o -name "*.h" | cut -c 3-))

build/norm/%.norm: %
	(cd $(BASE_PATH) && norminette ./$(CURRENT_PATH)/$<)
	mkdir -p $(@D)
	touch $@

.PHONY: clean_norm
clean: clean_norm
clean_norm:
	rm -rf build/norm
