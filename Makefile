CC = gcc
CFLAGS = -Wall -Wextra
TARGET = my3proc

$(TARGET): main3.c
	$(CC) $(CFLAGS) main3.c -o $(TARGET)

clean:
	rm -f $(TARGET)