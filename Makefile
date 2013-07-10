CPP=g++
ARCHITECTURE=64
OBJ=obj/var_base_$(ARCHITECTURE).o obj/main_$(ARCHITECTURE).o obj/funkcje-v_$(ARCHITECTURE).o obj/funkcje-k_$(ARCHITECTURE).o obj/funkcje-d_$(ARCHITECTURE).o
CXXFLAGS=-s -O3 -Wall -m$(ARCHITECTURE)
TARG=Calc$(ARCHITECTURE)
header1=spis.hpp
header2=var_base.hpp

all: obj $(TARG)

obj:
	mkdir -p obj/

$(TARG): $(OBJ)
	$(CPP) $(OBJ) -o $(TARG) $(CXXFLAGS)

obj/var_base_$(ARCHITECTURE).o: var_base.cpp $(header1) $(header2)
	$(CPP) -c var_base.cpp -o obj/var_base_$(ARCHITECTURE).o $(CXXFLAGS)

obj/main_$(ARCHITECTURE).o: main.cpp $(header1) $(header2)
	$(CPP) -c main.cpp -o obj/main_$(ARCHITECTURE).o $(CXXFLAGS)

obj/funkcje-v_$(ARCHITECTURE).o: funkcje-v.cpp $(header1)
	$(CPP) -c funkcje-v.cpp -o obj/funkcje-v_$(ARCHITECTURE).o $(CXXFLAGS)

obj/funkcje-k_$(ARCHITECTURE).o: funkcje-k.cpp $(header1) $(header2)
	$(CPP) -c funkcje-k.cpp -o obj/funkcje-k_$(ARCHITECTURE).o $(CXXFLAGS)

obj/funkcje-d_$(ARCHITECTURE).o: funkcje-d.cpp $(header1)
	$(CPP) -c funkcje-d.cpp -o obj/funkcje-d_$(ARCHITECTURE).o $(CXXFLAGS)
