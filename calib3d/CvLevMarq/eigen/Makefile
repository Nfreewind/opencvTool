TARGET = runLevenbergMarquardt

CXX = g++
#CXXFLAGS = -g -O0 -Wall -W -std=c++11
CXXFLAGS = -Wno-write-strings -std=c++11
ifeq ($(OS),Windows_NT)
    CXXFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CXXFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CXXFLAGS += -D IA32
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CXXFLAGS += -D LINUX
		CXXFLAGS += -I/usr/include/eigen3/
    endif
    ifeq ($(UNAME_S),Darwin)
        CXXFLAGS += -D OSX
		CXXFLAGS += -I/usr/local/Cellar/eigen/3.2.3/include/eigen3/
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CXXFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CXXFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CXXFLAGS += -D ARM
    endif
endif

LDFLAGS =
RM = rm -rf
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LIBS =
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

