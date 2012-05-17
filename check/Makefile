##
## Makefile for mml
## Made by nicuveo <crucuny@gmail.com>
##

include Makefile.rules



# VARS

PROJ = mml



# MAIN

all:
	./run $(TESTS)

$(TESTS):
	./run $@

clean:
	for e in $(TESTS) ; do (cd $$e && make clean) ; done

distclean:
	rm -f Makefile.rules
	for e in $(TESTS) ; do (cd $$e && make distclean) ; done

.PHONY: $(TESTS)
