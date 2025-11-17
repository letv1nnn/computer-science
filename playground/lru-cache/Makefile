.SILENT:

CC = gcc
CFLAGS = -Wall -g

SRCS = src/node.c src/doublyLinkedList.c src/test.c src/hashTable.c src/lruCache.c
OBJS = $(SRCS:.c=.o)
TARGET = test_program

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test.o: test.c lruCache.h
	$(CC) $(CFLAGS) -c test.c

lruCache.o: lruCache.c lruCache.h
	$(CC) $(CFLAGS) -c lruCache.c

node.o: node.c lruCache.h
	$(CC) $(CFLAGS) -c node.c

doublyLinkedList.o: doublyLinkedList.c lruCache.h
	$(CC) $(CFLAGS) -c doublyLinkedList.c

hashTable.o: hashTable.c lruCache.h
	$(CC) $(CFLAGS) -c hashTable.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

help:
	echo "make       - build the program"
	echo "make run   - build and run"
	echo "make clean - clean"
	echo "make help  - this message"

.PHONY: clean run
