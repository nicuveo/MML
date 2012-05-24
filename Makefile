##
## Makefile for mml
## Made by nicuveo <crucuny@gmail.com>
##



# MAIN

PROJ = mml

$(PROJ): all

sinclude Makefile.rules



# VARIABLES

EXE   = bin/$(PROJ)
LIBA  = bin/lib$(PROJ).a
LIBSO = bin/lib$(PROJ).so
DYLIB = bin/lib$(PROJ).dylib

OBJS  = $(addprefix build/, $(notdir $(CFIL:.cc=.o)))
DEPS  = $(addprefix build/, $(notdir $(CFIL:.cc=.d)))

CLEAN += '*~' '\#*' '.\#*' '.DS_Store' '.gdb_history' '*.stackdump' \
'.gdb_history' 'gmon.out' '*.dSYM'



# ALL

all: $(TARGETS)

install: all
	if [ -x ./install ] ; then ./install "$(PREFIX)" ; else cp $(TARGETS) $(PREFIX) ; fi



# COMPIL

$(EXE): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXE)

$(LIBA): $(LIBS) $(OBJS)
	ar -scr $(LIBA) $(OBJS)

$(LIBSO): $(LIBS) $(OBJS)
	$(CC) -shared $(OBJS) $(LDFLAGS) -o $(LIBSO)

$(DYLIB): $(LIBS) $(OBJS)
	$(CC) -dynamiclib $(OBJS) $(LDFLAGS) -o $@

$(OBJS):
	$(CC) $(CFLAGS) -M $< -MP -MT $@ -MF $(@:.o=.d)
	$(CC) $(CFLAGS) -c $< -o $@



# DISPATCH

$(LIBS): libs

libs:
	for l in $(LIBS_DIRS) ; do (cd $$l && make) ; done

conf_libs:
	for l in $(LIBS_DIRS) ; do (cd $$l && ./configure $(CONF_LIBS)) ; done

clean: do_clean
	for l in $(LIBS_DIRS) ; do (cd $$l && make -k clean) ; done
	cd ./check/    && make -k clean
	cd ./examples/ && make -k clean

distclean: do_distclean
	for l in $(LIBS_DIRS) ; do (cd $$l && make -k distclean) ; done
	cd ./check/    && make -k distclean
	cd ./examples/ && make -k distclean

check: all
	cd ./check/ && make all

examples: all
	cd ./examples/ && make all



# CLEAN

do_clean:
	for f in ${CLEAN} ; do find . -name "$$f" | xargs rm -Rf ; done
	rm -f $(OBJS)

do_distclean: do_clean
	rm -Rf doc/doxygen/*
	rm -f $(EXE) $(LIBA) $(LIBSO) $(DYLIB) $(DEPS)
	rm -f Makefile.rules



# DOC

doc:
	./doc/input/regen
	doxygen Doxyfile

export:
	./scripts/export



# SELF

sinclude $(DEPS)

dependency_rule = build/$(notdir $(1:.cc=.o)): $1
$(foreach file,$(CFIL),$(eval $(call dependency_rule,$(file))))

Makefile.rules:
	./configure $(CONFIGURE_ARGS)



# MISC

flower:
	@cat ./scripts/flower

todo:
	@./scripts/todo



# SPECIALS

.PHONY: todo flower doc export $(LIBS_DIRS)
