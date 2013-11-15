ARCHITECTURE = 64
CC = clang
CXX = clang++
LINK = clang++
CFLAGS = -Wall -g -m$(ARCHITECTURE)
CXXFLAGS = -Wall -g -m$(ARCHITECTURE)
LFLAGS = -m$(ARCHITECTURE)
RM = rm -f
CP = cp -f
ROOT = ../

.PHONY: all clean

all: Calc

Calc: $(ROOT)Main/all-d.o $(ROOT)Calckit/all-d.o $(ROOT)Numeric-lib/all-d.o $(ROOT)Variable-lib/all-d.o
	$(LINK) $(LFLAGS) $^ -o $@

# Main
$(ROOT)Main/all-d.o: $(ROOT)Main/main-d.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Main/main-d.o: $(ROOT)Main/main.cpp $(ROOT)Main/main.hpp $(ROOT)Variable-lib/var_base.hpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Calckit/calckit.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Calckit
$(ROOT)Calckit/all-d.o: $(ROOT)Calckit/calckit-d.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Calckit/calckit-d.o: $(ROOT)Calckit/calckit.cpp $(ROOT)Calckit/calckit.hpp $(ROOT)Main/main.hpp $(ROOT)Variable-lib/var_base.hpp $(ROOT)Numeric-lib/num.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Numeric-lib
$(ROOT)Numeric-lib/all-d.o: $(ROOT)Numeric-lib/num-d.o $(ROOT)Numeric-lib/num_core-d.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Numeric-lib/num-d.o: $(ROOT)Numeric-lib/num.cpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Numeric-lib/num_core.hpp $(ROOT)Main/main.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ROOT)Numeric-lib/num_core-d.o: $(ROOT)Numeric-lib/num_core.cpp $(ROOT)Numeric-lib/num.hpp $(ROOT)Numeric-lib/num_core.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Variable-lib
$(ROOT)Variable-lib/all-d.o: $(ROOT)Variable-lib/var_base-d.o
	$(LINK) $(LFLAGS) -Wl,-r -nostdlib $^ -o $@

$(ROOT)Variable-lib/var_base-d.o: $(ROOT)Variable-lib/var_base.cpp $(ROOT)Variable-lib/var_base.hpp  $(ROOT)Numeric-lib/num.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# clean
clean:
	$(RM) $(ROOT)Main/*.o
	$(RM) $(ROOT)Calckit/*.o
	$(RM) $(ROOT)Numeric-lib/*.o
	$(RM) $(ROOT)Variable-lib/*.o