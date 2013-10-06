include ../settings.mk
DIR = Main

.PHONY: clean

../$(DIR).o: main.cpp main.hpp ../Numeric-lib/num.hpp ../Calckit/calckit.hpp ../Variable-lib/var_base.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR).o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o