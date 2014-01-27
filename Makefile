.PHONY: all install uninstall clean clean-all

all: Release-linux-x64

Release-linux-x64:
	make -B -C build-Release/ ARCHITECTURE=64
	mv build-Release/Calc Calc
Release-linux-x32:
	make -B -C build-Release/ ARCHITECTURE=32
	mv build-Release/Calc Calc
Release-win-x64:
	make -B -C build-Release/ CC=wine\ ../../TDM-GCC/bin/gcc.exe CXX=wine\ ../../TDM-GCC/bin/g++.exe LINK=wine\ ../../TDM-GCC/bin/g++.exe ARCHITECTURE=64
	mv build-Release/Calc.exe Calc.exe
Release-win-x32:
	make -B -C build-Release/ CC=wine\ ../../TDM-GCC/bin/gcc.exe CXX=wine\ ../../TDM-GCC/bin/g++.exe LINK=wine\ ../../TDM-GCC/bin/g++.exe ARCHITECTURE=32
	mv build-Release/Calc.exe Calc.exe

install:
	mkdir -p /opt/Calc
	cp Calc /opt/Calc
	printf "#!/bin/sh\n/opt/Calc/./Calc \$$*" > /usr/bin/Calc
	chmod -R 755 /opt/Calc
	chmod 755 /usr/bin/Calc

uninstall:
	rm -r -f /opt/Calc /usr/bin/Calc

clean:
	make -C build-Release/ clean
