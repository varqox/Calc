export
# Compile commands
ifeq ($(shell clang > /dev/null 2> /dev/null; echo $$?), $(shell echo 1))
CC = clang
else
CC = gcc
endif
ifeq ($(shell clang++ > /dev/null 2> /dev/null; echo $$?), $(shell echo 1))
CXX = clang++
LINK = clang++
else
CXX = g++
LINK = g++
endif

CFLAGS = -Wall -Wextra -Wabi -Weffc++ -Wshadow -Wfloat-equal -Wno-unused-result -O3 -c
CXXFLAGS := $(CFLAGS)
LFLAGS = -Wall -Wextra -Wabi -Weffc++ -Wshadow -Wfloat-equal -Wno-unused-result -s -O3

# Shell commands
MV = mv -f
CP = cp -f -r
UPDATE = $(CP) -u
RM = rm -f
MKDIR = mkdir -p

.PHONY: all debug clean

all: 1 jjj

debug:
	make all CC='$(CC) -DDEBUG' CXX='$(CXX) -DDEBUG' LINK='$(LINK) -DDEBUG'

1: 1.cpp
	$(LINK) $^ $(LFLAGS) -o $@

jjj: jjj.cpp
	$(LINK) $^ $(LFLAGS) -o $@

clean:
	$(RM) *.o

mrproper: clean
	$(RM) 1 jjj