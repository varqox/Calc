flags = -Wall -s -O3
targ1 = hide
targ2 = generate_key
CXX = g++

.PHONY: all

all: $(targ1) $(targ2)

$(targ1): obj/hide.o
	$(CXX) obj/hide.o $(flags) -o $(targ1)
$(targ2): obj/generate_key.o
	$(CXX) obj/generate_key.o $(flags) -o $(targ2)
obj/generate_key.o: generate_key.cpp
	$(CXX) generate_key.cpp -c $(flags) -o obj/generate_key.o
obj/hide.o: hide.cpp
	$(CXX) hide.cpp -c $(flags) -o obj/hide.o