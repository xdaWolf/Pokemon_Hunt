all: compile link main

compile:
	g++ -I src/include -c game.cpp -o game.o
	g++ -I src/include -c main.cpp -o main.o
	g++ -I src/include -c field.cpp -o field.o
	g++ -I src/include -c enemy.cpp -o enemy.o
	g++ -I src/include -c player.cpp -o player.o
	g++ -I src/include -c collectable.cpp -o collectable.o
	g++ -I src/include -c enemy2.cpp -o enemy2.o

link:
	g++ -o main main.o enemy.o enemy2.o field.o game.o player.o collectable.o -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
main:
	main