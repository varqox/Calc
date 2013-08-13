include var.mk
OBJS = Main.o Variable-lib.o Numeric-lib.o Calckit.o
MFLAGS += --no-print-directory

.PHONY: all install uninstall clean clean-all

all: Calc

Calc: $(OBJS)
	@echo "\033[01;31mLinking execute Calc\033[00m"
	@$(CXX) $^ $(LDFLAGS) -o $@
	@echo "\033[01;34mBuild target Calc\033[00m"

Main.o: Main/*.cpp
	@make $(MFLAGS) -C Main
	@echo "\033[01;34mBuild target Main\033[00m"
Variable-lib.o: Variable-lib/*.cpp
	@make $(MFLAGS) -C Variable-lib
	@echo "\033[01;34mBuild target Variable-lib\033[00m"
Numeric-lib.o: Numeric-lib/*.cpp
	@make $(MFLAGS) -C Numeric-lib
	@echo "\033[01;34mBuild target Numeric-lib\033[00m"
Calckit.o: Calckit/*.cpp
	@make $(MFLAGS) -C Calckit
	@echo "\033[01;34mBuild target Calckit\033[00m"

install:
	mkdir -p /opt/Calc
	cp Calc /opt/Calc
	printf "#!/bin/sh\n/opt/Calc/./Calc \$$*" > /usr/bin/Calc
	chmod 777 /opt/Calc
	chmod 755 /usr/bin/Calc

uninstall:
	rm -r -f /opt/Calc /usr/bin/Calc

clean:
	@echo "\033[01;33mCleaning root directory...\033[00m"
	@$(RM) $(OBJS)
	@make $(MFLAGS) -C Main clean
	@make $(MFLAGS) -C Variable-lib clean
	@make $(MFLAGS) -C Numeric-lib clean
	@make $(MFLAGS) -C Calckit clean

clean-all: clean
	@$(RM) Calc