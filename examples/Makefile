##
## Makefile for mml
## Made by nicuveo <crucuny@gmail.com>
##

include Makefile.rules



# VARS

PROJ = mml



# MAIN

all: $(EXAMPLES)

$(EXAMPLES):
	cd $@ && make all

clean:
	for e in $(EXAMPLES) ; do (cd $$e && make clean) ; done

distclean:
	rm -f Makefile.rules
	for e in $(EXAMPLES) ; do (cd $$e && make distclean) ; done

.PHONY: $(EXAMPLES)
