
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I../include -I../src/include

libminirt.so: $(OBJS_LIB_FPIC)
	rm -f $@
	$(CC) $(LDFLAGS) -shared -o $@ $<

libminirt_bmp.a: $(OBJS_LIB_BMP)
	rm -f $@
	ar cr $@ $^
libminirt_core.a: $(OBJS_LIB_CORE)
	rm -f $@
	ar cr $@ $^

minirt.exe: $(OBJS_EXE_MINIRT) libminirt.so
	rm -f $@
	$(CC) $(LDFLAGS) -L. -lminirt -o $@ $(OBJS_EXE_MINIRT)

