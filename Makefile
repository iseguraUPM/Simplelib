SHELL := /bin/bash

all-tests := $(addsuffix .test, $(basename $(wildcard tests/*.test-in)))

.PHONY : test all %.test

SOURCES := main.c simple_queue.c simple_stack.c simple_linked_list.c simple_btree.c

main : $(SOURCES)
	@gcc -Wall -o $@.out $(SOURCES) -I .

test : $(all-tests)

%.test : %.test-in %.test-cmp main
	@./main.out < $< 2>&1 | diff -q $(word 2, $?) - >/dev/null \
	|| (echo "Test $@ failed" && exit 1)

all : test 
	@echo "Success, all tests passed."

clean :
	@rm *.out 2> /dev/null || echo > /dev/null
	