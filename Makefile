CC = gcc
CFLAGS = -O2 -Wall -lm -static -std=gnu90 -DONLINE_JUDGE -DBOJ
CXX = g++
CXXFLAGS = -O2 -Wall -lm -static -std=gnu++17 -DONLINE_JUDGE -DBOJ
TARGET = $(basename $(SRC)).out
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -f $(TARGET)


