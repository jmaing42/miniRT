TARGET := \
	out/branch/g_mock_branch.o \
	out/branch/mock_branch_start.o \
	out/branch/mock_branch_stop.o \
	out/branch/mock_branch_pause.o \
	out/branch/mock_branch_resume.o \
	out/branch/malloc.o \
	out/branch/free.o \
	out/branch/open.o \
	out/branch/close.o \
	out/branch/read.o \
	out/branch/write.o \

all: $(TARGET)
.PHONY: all

out/branch/%.o:
	$(MAKE) -C branch out/$*.o
	mv -f branch/out/$*.o $@

.PHONY: clean
clean:
	$(MAKE) -C branch fclean

.PHONY: fclean
fclean: clean
	rm -rf out

.PHONY: re
re: fclean
	$(MAKE) all
