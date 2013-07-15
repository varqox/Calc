include makefile-var
OBJECTS = Main.o Variable-lib.o Numeric-lib.o Calckit.o
MFLAGS += --no-print-directory

all: Calc

Calc: $(OBJECTS)
	@echo "\033[01;31mLinking execute Calc\033[00m"
	@$(CXX) $^ $(LDFLAGS) -o $@
	@echo "\033[01;34mBuild target Calc\033[00m"

Main.o:
	@make $(MFLAGS) -C Main
	@echo "\033[01;34mBuild target Main\033[00m"
Variable-lib.o:
	@make $(MFLAGS) -C Variable-lib
	@echo "\033[01;34mBuild target Variable-lib\033[00m"
Numeric-lib.o:
	@make $(MFLAGS) -C Numeric-lib
	@echo "\033[01;34mBuild target Numeric-lib\033[00m"
Calckit.o:
	@make $(MFLAGS) -C Calckit
	@echo "\033[01;34mBuild target Calckit\033[00m"

.PHONY install
install:
	mkdir -p /opt/Calc
	cp Calc /opt/Calc
	printf "" > /usr/bin/Calc

.PHONY uninstall
uninstall:
	rm -r -f /opt/Calc /usr/bin/Calc

.PHONY: clean
clean:
	@echo "\033[01;33mCleaning root directory...\033[00m"
	@$(RM) $(OBJECTS)
	@make $(MFLAGS) -C Main clean
	@make $(MFLAGS) -C Variable-lib clean
	@make $(MFLAGS) -C Numeric-lib clean
	@make $(MFLAGS) -C Calckit clean

.PHONY: clean-all
clean-all: clean
	@$(RM) Calc