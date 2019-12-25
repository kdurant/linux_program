CC = clang
TARGET = a.out
INC_DIRS = ../lib
INC = -I$(INC_DIRS)
CFLAGS = -DTEST
CFLAGS = -std=c99 -g
CFLAGS = -lpthread

SRC_FILES = $(INC_DIRS)/get_num.c $(INC_DIRS)/ugid_functions.c $(INC_DIRS)/error_functions.c $(INC_DIRS)/file_perms.c

SRC_FILES += simple_thread.c

default:
	@$(CC) $(INC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)
	@#./$(TARGET)

clean:
	rm *.o

