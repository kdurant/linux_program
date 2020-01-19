CC = clang
TARGET = a.out
INC_DIRS = ./apue_lib
INC = -I$(INC_DIRS)
CFLAGS = -DTEST
CFLAGS = -std=c99 -g
CFLAGS = -lpthread

SRC_FILES += 11-13.c

default:
	@$(CC) $(INC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)
	@#./$(TARGET)

clean:
	rm *.o

