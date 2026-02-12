# Makefile for Lexical Analyzer

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = lexer
SRC = lexical_analyzer.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.exe

test: $(TARGET)
	./$(TARGET) sample.c

.PHONY: all clean test
