main:
	g++ -o main *.cpp -O3
debug:
	g++ -o main src/*.cpp -ggdb -g3
clear:
	del *o main.exe