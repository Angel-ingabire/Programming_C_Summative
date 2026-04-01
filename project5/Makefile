CC = gcc
CFLAGS = -O2 -Wall -std=c11
LDFLAGS = -lcurl -lpthread

TARGET = mt_scraper
OBJS = main.o scraper.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.c scraper.h
	$(CC) $(CFLAGS) -c main.c

scraper.o: scraper.c scraper.h
	$(CC) $(CFLAGS) -c scraper.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
