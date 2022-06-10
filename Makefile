all: compile link

compile:
	g++ -I src/include -c game.cpp
	g++ -I src/include -c main.cpp
	g++ -I src/include -c Window.cpp
link:
	g++ window.o -o window game.o -o game main.o -o main -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio