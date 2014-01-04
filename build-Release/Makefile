# Compile commands
ifeq ($(shell clang > /dev/null 2> /dev/null; echo $$?), $(shell echo 1))
export CC = clang
else
export CC = gcc
endif
ifeq ($(shell clang++ > /dev/null 2> /dev/null; echo $$?), $(shell echo 1))
export CXX = clang++
export LINK = clang++
else
export CXX = g++
export LINK = g++
endif

export ARCHITECTURE = # default
export CFLAGS = -Wall -O3 -c
export CXXFLAGS = -Wall -O3 -c
export LFLAGS = -Wall -s -O3
export RM = rm -f
export CP = cp -f
ROOT = ../

.PHONY: all clean

all: Calc

Calc: $(ROOT)Main/all.o $(ROOT)Calckit/all.o $(ROOT)Numeric-lib/all.o $(ROOT)Variable-lib/all.o
	$(LINK) $(LFLAGS) $^ -o $@

# Main
$(ROOT)Main/all.o: $(ROOT)Main/main.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Main/main.o: $(ROOT)Main/main.cpp $(ROOT)Main/main.hpp $(ROOT)Variable-lib/var_base.hpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Calckit/calckit.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Calckit
$(ROOT)Calckit/all.o: $(ROOT)Calckit/calckit.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Calckit/calckit.o: $(ROOT)Calckit/calckit.cpp $(ROOT)Calckit/calckit.hpp $(ROOT)Main/main.hpp $(ROOT)Variable-lib/var_base.hpp $(ROOT)Numeric-lib/num.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Numeric-lib
$(ROOT)Numeric-lib/all.o: $(ROOT)Numeric-lib/num.o $(ROOT)Numeric-lib/num_core.o
		$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Numeric-lib/num.o: $(ROOT)Numeric-lib/num.cpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Numeric-lib/num_core.hpp $(ROOT)Main/main.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ROOT)Numeric-lib/num_core.o: $(ROOT)Numeric-lib/num_core.cpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Numeric-lib/num_core.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Variable-lib
$(ROOT)Variable-lib/all.o: $(ROOT)Variable-lib/var_base.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Variable-lib/var_base.o: $(ROOT)Variable-lib/var_base.cpp $(ROOT)Variable-lib/var_base.hpp  $(ROOT)Numeric-lib/num.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# clean
clean:
	$(RM) $(ROOT)Main/*.o
	$(RM) $(ROOT)Calckit/*.o
	$(RM) $(ROOT)Numeric-lib/*.o
	$(RM) $(ROOT)Variable-lib/*.o