TARGET = RATIO
SOURCES = main.cpp
DIR_INCLUDE = include/
DIR_BUILD = build/
CC = clang++
C_FLAGS = -std=c++11 -g -Wall

all:
	$(CC) $(C_FLAGS) -I$(DIR_INCLUDE) -o $(DIR_BUILD)$(TARGET) $(SOURCES)

clean:
	rm $(DIR_BUILD)$(TARGET)
