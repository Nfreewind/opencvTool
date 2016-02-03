TARGET = projectPoints

CXX = g++
CXXFLAGS = -g -O0 -Wall -W
LDFLAGS =
RM = rm -rf
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LIBS = opencv
ifneq ($(LIBS),)
CXXFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS += $(shell pkg-config --libs $(LIBS))
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.o $(TARGET)

