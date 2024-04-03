CXX := g++
CXXFLAGS := -g -I src/include
LDFLAGS := -L src/lib
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

SRCS := main.cpp Field.cpp Player.cpp Collectable.cpp BaseEntity.cpp EndOfGame.cpp Trainer.cpp Pokeball.cpp HealthBar.cpp PokeBox.cpp PokeCenter.cpp Obstacle.cpp Menu.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	.\clean.bat
