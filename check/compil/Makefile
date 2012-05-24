include Makefile.rules


# VARIABLES

EXE   = test
OBJS  = $(notdir $(CFIL:.cc=.o))
DEPS  = $(notdir $(CFIL:.cc=.d))


# MAIN

all: $(EXE)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXE) $(DEPS) Makefile.rules out err compil.out compil.err


# COMPIL

includes:
	find ../../include -type f -iname "*.hh" \! -path ".*svn.*" | sed "s%../../include/\(.*\)%#include \"\1\"%" > includes.hh

$(EXE): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXE)

$(OBJS):
	$(CC) $(CFLAGS) -M $< -MP -MT $@ -MF $(@:.o=.d)
	$(CC) $(CFLAGS) -c $< -o $@

test.o: test.cc includes
