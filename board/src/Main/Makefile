CC=arm-linux-gcc
SRC=main.c log.c systeminfo.c thread.c socket.c socket_dev.c init.c serial.c 
OBJS=main.o log.o systeminfo.o thread.o socket.o socket_dev.o init.o serial.o
CFLAGS=-lpthread
INCPATH=-I ../../include
TARGET=Main

all:$(TARGET)
$(TARGET): 
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(INCPATH)

clean:
	rm $(TARGET)
