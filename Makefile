#
#PANAGIOTIS PAPATHEODOROPOULOS
#AM:2022202200160
#dit22160@go.uop.gr
#
#NIKOLAS GOGALIS
#AM: 2022202200031
#dit22031@go.uop.gr
#

# Compiler settings
CC = gcc
CFLAGS = -Wall -I./config -I./functions
LDFLAGS =

# Source files
SOURCES = $(wildcard *.c) $(wildcard functions/*.c) $(wildcard config/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = minesweeper

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(OBJECTS) $(LDFLAGS) -lm -o $@

%.o: %.c
    $(CC) $(CFLAGS) -std=c99 -c $< -o $@

clean:
    del /Q $(EXECUTABLE) $(OBJECTS)