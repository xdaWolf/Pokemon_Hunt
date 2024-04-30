CXX := g++
CXXFLAGS := -g -I src/include 
LDFLAGS := -L src/lib -L src/include
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
TEST_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -lpthread

SRCS := main.cpp Field.cpp Player.cpp Collectable.cpp BaseEntity.cpp EndOfGame.cpp Trainer.cpp Pokeball.cpp HealthBar.cpp PokeBox.cpp PokeCenter.cpp Obstacle.cpp Menu.cpp SurvivalGameMode.cpp NormalGameMode.cpp Sounds.cpp Observer.cpp Subject.cpp Button.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main
TEST_SRCS := Test_Subject_Observer.cpp Test_BaseEntity.cpp Test_Button.cpp Test_Field.cpp Test_Menu.cpp Test_NormalGameMode.cpp Test_SurvivalGameMode.cpp Test_Player.cpp
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
TEST_TARGET := test

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	.\clean.bat

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out main.o, $(OBJS))
	$(CXX) $(LDFLAGS) -o $@ $^ $(TEST_LIBS)

$(TEST_OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
