include makefile-var
OBJECTS = Main.o Variable-lib.o Numeric-lib.o Calckit.o
#MFLAGS += --no-print-directory

all: Calc

Calc: $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

Main.o:
	make $(MFLAGS) -C Main
Variable-lib.o:
	make $(MFLAGS) -C Variable-lib
Numeric-lib.o:
	make $(MFLAGS) -C Numeric-lib
Calckit.o:
	make $(MFLAGS) -C Calckit

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: clean-all
clean-all:
	$(RM) Calc* $(OBJECTS)