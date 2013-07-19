include ../makefile-var
DIR = Numeric-lib

../$(DIR).o: num.cpp num.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR).o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o