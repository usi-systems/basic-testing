# PROGRAMS = diamond # we need to treat the binary file as an object, to be able to link on it with the --wrap option
OBJECTS=diamond.o
LDFLAGS=-Wl,--wrap=main

# TODO: check if it's still required!
TESTS_IO:=$(wildcard $(TESTS_DIR)/*.in)
TESTS_IO_NAMES:=$(sort $(patsubst $(TESTS_DIR)/%.in, %, $(TESTS_IO)))

include ../../basic_testing.mk
