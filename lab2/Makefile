TARGET = RATIO
SOURCES = Main.cpp
DIR_INCLUDE = include/
DIR_BUILD = build/
CC = clang++
C_FLAGS = -g -Wall -Werror -pedantic

all:
	$(CC) $(C_FLAGS) -I$(DIR_INCLUDE) -o $(DIR_BUILD)$(TARGET) $(SOURCES)

clean:
	rm $(DIR_BUILD)$(TARGET)
