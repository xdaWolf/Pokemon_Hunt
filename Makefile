all: compile link main

compile:
	g++ -I src/include -c game.cpp -o game.o
	g++ -I src/include -c main.cpp -o main.o
	g++ -I src/include -c field.cpp -o field.o
	g++ -I src/include -c enemy.cpp -o enemy.o

link:
	g++ field.o -o field enemy.o -o enemy game.o -o game main.o -o main -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

	g++ -o main main.o game.o field.o enemy.o -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
main:
	main