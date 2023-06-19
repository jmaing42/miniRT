include targets.mk

all: $(TARGET)
.PHONY: all

.PHONY: everything
everything: $(EVERYTHING) .vscode/launch.json .vscode/tasks.json

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -rf out .vscode/launch.json .vscode/tasks.json

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: dev
dev: .vscode/launch.json .vscode/tasks.json
