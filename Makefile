all: compile link main

compile:
	g++ -I src/include -c game.cpp -o game.o
	g++ -I src/include -c main.cpp -o main.o
	g++ -I src/include -c field.cpp -o field.o
	g++ -I src/include -c enemy.cpp -o enemy.o
	g++ -I src/include -c player.cpp -o player.o
	g++ -I src/include -c collectable.cpp -o collectable.o

link:
	g++ player.o -o player field.o -o field enemy.o -o enemy game.o -o game collectable.o -o collectable main.o -o main -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
	
	g++ -o main main.o enemy.o field.o game.o player.o collectable.o -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
main:
	main