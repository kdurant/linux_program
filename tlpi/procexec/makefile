CC = gcc -std=c99 -g
TARGET = a.out
INC_DIRS = ../lib
INC = -I$(INC_DIRS)
SYMBOLS = -DTEST

SRC_FILES = $(INC_DIRS)/get_num.c $(INC_DIRS)/ugid_functions.c $(INC_DIRS)/error_functions.c $(INC_DIRS)/file_perms.c

SRC_FILES += t_fork.c

default:
	@$(CC) $(INC) $(SYMBOLS) $(SRC_FILES) -o $(TARGET)
	@#./$(TARGET)

clean:
	rm *.o

