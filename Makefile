# Makefile for Lexical Analyzer

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = lexer
SRC = lexical_analyzer.c

# OS and Shell Detection
ifeq ($(OS),Windows_NT)
    EXE = .exe
    ifneq (,$(findstring sh,$(SHELL)))
        # Windows with Unix-like shell (e.g., Git Bash, MinGW sh)
        RM = rm -f
        TEST_EXEC = ./$(TARGET)$(EXE)
    else
        # Windows with CMD
        RM = del /Q /F
        TEST_EXEC = $(TARGET)$(EXE)
    endif
else
    # Linux/Mac settings
    RM = rm -f
    EXE =
    TEST_EXEC = ./$(TARGET)$(EXE)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE) $(SRC)

clean:
	-$(RM) $(TARGET)$(EXE)

test: $(TARGET)
	$(TEST_EXEC) sample.c

.PHONY: all clean test
