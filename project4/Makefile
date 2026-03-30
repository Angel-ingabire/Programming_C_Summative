CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = toolkit
SRCS = main.c dataset.c file_io.c operations.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET).exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).exe dataset.dat results.txt

run: $(TARGET)
	./$(TARGET).exe

debug: CFLAGS += -g
debug: $(TARGET)

