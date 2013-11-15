.PHONY: all install uninstall clean clean-all

all: Release-linux-x64

Release-linux-x64:
	make -B -C build-Release/ CC=clang CXX=clang++ LINK=clang++ ARCHITECTURE=64
	mv build-Release/Calc Calc
Release-linux-x32:
	make -B -C build-Release/ CC=clang CXX=clang++ LINK=clang++ ARCHITECTURE=32
	mv build-Release/Calc Calc
Release-win-x64:
	make -B -C build-Release/ CC=wine\ ../../MinGW64/bin/gcc.exe CXX=wine\ ../../MinGW64/bin/g++.exe LINK=wine\ ../../MinGW64/bin/g++.exe ARCHITECTURE=64
	mv build-Release/Calc.exe Calc.exe
Release-win-x32:
	make -B -C build-Release/ CC=wine\ ../../MinGW64/bin/gcc.exe CXX=wine\ ../../MinGW64/bin/g++.exe LINK=wine\ ../../MinGW64/bin/g++.exe ARCHITECTURE=32
	mv build-Release/Calc.exe Calc.exe

install:
	mkdir -p /opt/Calc
	cp Calc /opt/Calc
	printf "#!/bin/sh\n/opt/Calc/./Calc \$$*" > /usr/bin/Calc
	chmod 777 /opt/Calc
	chmod 755 /usr/bin/Calc

uninstall:
	rm -r -f /opt/Calc /usr/bin/Calc

clean:
	make -C build-Release/ clean