##
## Makefile for mml
## Made by nicuveo <crucuny@gmail.com>
##

include Makefile.rules



# VARS

PROJ = mml



# MAIN

all: $(TOOLS)

$(TOOLS):
	cd $@ && make all

clean:
	for e in $(TOOLS) ; do (cd $$e && make clean) ; done

distclean:
	rm -f Makefile.rules
	for e in $(TOOLS) ; do (cd $$e && make distclean) ; done

.PHONY: $(TOOLS)
