CXXFLAGS = -O0 -g -Wall -Wextra -Werror -Wpedantic -std=c++20 -Wno-error=unused-parameter -Wno-error=unused-but-set-variable -fPIE
LDFLAGS =

TARGET =
CXX = $(TARGET)g++

OBJS = main.o fromstring.o addressing_mode.o codec.o parser.o
HEADERS = $(wildcard *.h)

all: main

%.o: %.cc $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o *.elf *.bin *.out *.imem *.hex

.SUFFIXES:
.INTERMEDIATE:
.PHONY: all clean %.dump
