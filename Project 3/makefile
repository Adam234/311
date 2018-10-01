objects = interface db
CC=gcc
DEPS = db.h
all: $(objects)

$(objects): %: %.c
	gcc -o $@ $<