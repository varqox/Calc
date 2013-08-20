include ../settings.mk
DIR = Numeric-lib

.PHONY: clean

../$(DIR).o: num.o num_core.o
	@echo "\033[01;31mLinking CXX object $(DIR).o\033[00m"
	@$(CXX) $^ $(CXXFLAGS) -Wl,-r -nostdlib -o $@

num.o: num.cpp num.hpp num_core.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR)/num.o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

num_core.o: num_core.cpp num_core.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR)/num_core.o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o