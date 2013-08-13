include ../var.mk
DIR = Calckit

.PHONY: clean
	
../$(DIR).o: calckit.cpp ../Variable-lib/var_base.hpp ../Main/spis.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR).o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o