CC = gcc
CFLAGS = -Wall -g
TARGET = program
SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)
#(TARGET): all
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)