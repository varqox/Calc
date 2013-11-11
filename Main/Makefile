include ../settings.mk
DIR = Main

.PHONY: clean

../$(DIR).o: main.o stream.o
	@echo "\033[01;31mLinking CXX object $(DIR).o\033[00m"
	@$(CXX) $^ $(CXXFLAGS) -Wl,-r -nostdlib -o $@

main.o: main.cpp main.hpp stream.cpp ../Numeric-lib/num.hpp ../Calckit/calckit.hpp ../Variable-lib/var_base.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR)/num.o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

stream.o: stream.cpp stream.hpp
	@echo "\033[00;32mBuilding CXX object $(DIR)/stream.o\033[00m"
	@$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	@echo "\033[01;33mCleaning directory: $(DIR)...\033[00m"
	@$(RM) *.o