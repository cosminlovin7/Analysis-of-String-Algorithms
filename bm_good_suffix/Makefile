CC = g++
CFLAGS = -Wall -Wextra
LDLIBS = -lm

build: algo.cpp
	g++ algo.cpp -o test $(CFLAGS)

run_tests: test
	./test

.PHONY: clean
clean:
	rm -rf test
