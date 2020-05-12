CC = clang
TARGET = a.out
INC_DIRS = ./apue_lib
INC = -I$(INC_DIRS)
CFLAGS += -DTEST
CFLAGS += -g
CFLAGS += -pthread
CFLAGS += -std=c99

SRC_FILES += 11-5.c

default:
	@$(CC) $(INC) $(CFLAGS) -o $(TARGET) $(SRC_FILES) 
	@#./$(TARGET)

clean:
	rm *.o

