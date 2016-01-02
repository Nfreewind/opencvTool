TARGET = playVideo

CC = g++
CFLAGS = -g -O0 -Wall -W
LDFLAGS =
RM = rm -rf
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LIBS = opencv
ifneq ($(LIBS),)
CFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS += $(shell pkg-config --libs $(LIBS))
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o $(TARGET)

