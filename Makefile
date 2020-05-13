SHELL 		:= /bin/bash

RM			:= rm -vf

CC			:= gcc

SRC 		:= 	src/simple_queue.c \
				src/simple_stack.c \
				src/simple_linked_list.c \
				src/simple_bin_tree.c \
				src/simple_linked_bin_tree.c \
				src/simple_hash_table.c \
				src/simple_hash_set.c \
				src/transform.c

OBJ 		:= $(subst src/,obj/,$(subst .c,.o,$(SRC)))

LDFLAGS		:= -lsimplelib -lm

CFLAGS		:= -O0 -g -Lbin -std=c99 -pedantic -Wextra -Wall -Wconversion -Iinclude 

ALL_TESTS 	:= $(addsuffix .test, $(basename $(wildcard tests/*.test-in)))

TEST_SRC	:= tests/src/main.c

TEST_OBJ	:= $(subst tests/src,tests/obj,$(subst .c,.o,$(TEST_SRC)))

obj/%.o : src/%.c
	gcc -c $< -g -o $@

simplelib : $(OBJ)
	ar rcs bin/lib$@.a $(OBJ)

tests/obj/%.o : tests/src/%.c
	gcc -c $< $(CFLAGS) -o $@

tests/bin/main.out : $(TEST_OBJ) simplelib
	gcc $< $(CFLAGS) $(LDFLAGS) -o $@

test : $(ALL_TESTS)

%.test : %.test-in %.test-cmp tests/bin/main.out
	@$(word 3, $?) < $< 2>&1 | diff -q $(word 2, $?) - >/dev/null \
	|| (echo "Test $@ failed" && exit 1)

all : test 
	@echo "Success, all tests passed."

clean :
	$(RM) $(OBJ) $(TEST_OBJ) *~

.PHONY : test all %.test clean
	