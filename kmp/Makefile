CC = g++
CFLAGS = -Wall -Wextra
LDLIBS = -lm

kmp: algo.cpp
	g++ algo.cpp -o test $(CFLAGS)

run: test

.PHONY: clean
clean:
	rm -rf test
