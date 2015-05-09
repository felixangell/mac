FLAGS = -Wall -Wextra -g -std=c11
SRC_FILES = main.c

all:
	gcc ${SRC_FILES} ${FLAGS} -o mac

test:
	gcc ${SRC_FILES} ${FLAGS} -o mac
	./mac
