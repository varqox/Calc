CXX = clang++ #g++
ARCH = 64
CXXFLAGS = -O3 -Wall -m$(ARCH)
LDFLAGS = -s $(CXXFLAGS)
RM = rm -f
