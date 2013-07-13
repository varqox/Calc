include ../makefile-var
DIR = Numeric-lib

../$(DIR).o: funkcje-v.o funkcje-d.o
	@echo "\033[01;31mLinking CXX object $(DIR).o\033[00m"
	@$(CXX) -Wl,-r $^ $(CXXFLAGS) -nostdlib -o $@

funkcje-v.o: funkcje-v.cpp ../Main/spis.hpp
	@echo "\033[00;32mBuilding CXX object $@\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

funkcje-d.o: funkcje-d.cpp ../Main/spis.hpp
	@echo "\033[00;32mBuilding CXX object $@\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o