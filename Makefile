all: program

program: src/main.cpp
	cd src; gcc -Wall main.cpp -o main

clean:
	rm -rf **/*.o
	rm -rf **/*.so
	rm -rf **/*.a
	rm -rf **/*.dylib
	rm -rf **/*.cpp.*
	rm -rf src/main

run: program
	./src/main
