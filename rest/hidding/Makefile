flags=-Wall -s -O3
flags_obj=-c $(flags)
codes=1.cpp generate_key.cpp
objects=obj/hide.o obj/generate_key.o
headers=
targ1=hide
targ2=generate_key
compile=g++

all:$(targ1) $(targ2)

$(targ1): obj/hide.o
	$(compile) obj/hide.o $(flags) -o $(targ1)
$(targ2): obj/generate_key.o
	$(compile) obj/generate_key.o $(flags) -o $(targ2)
obj/generate_key.o: generate_key.cpp $(headers)
	$(compile) generate_key.cpp $(flags_obj) -o obj/generate_key.o
obj/hide.o: hide.cpp $(headers)
	$(compile) hide.cpp $(flags_obj) -o obj/hide.o