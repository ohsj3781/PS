CC = gcc
CFLAGS = -O2 -Wall -lm -static -std=gnu90 -DONLINE_JUDGE -DBOJ
CXX = g++
CXXFLAGS = -O2 -Wall -lm -static -std=gnu++17 -DONLINE_JUDGE -DBOJ
TARGET = $(basename $(SRC)).out
SRC = $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -f $(TARGET)


