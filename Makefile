all: program

program: shared_lib src/main.cpp
	cd src; gcc -Wall -I../my_shared_lib -L../my_shared_lib main.cpp -lmySharedLib -o main

shared_lib: lib
	cd my_shared_lib; gcc -shared mySharedLib.o -o libmySharedLib.so

lib: my_shared_lib/mySharedLib.cpp my_shared_lib/mySharedLib.h
	cd my_shared_lib; gcc -Wall -c mySharedLib.cpp -o mySharedLib.o

clean:
	rm -rf **/*.o
	rm -rf **/*.so
	rm -rf **/*.a
	rm -rf **/*.dylib
	rm -rf **/*.cpp.*
	rm -rf src/main

run: program
	./src/main
