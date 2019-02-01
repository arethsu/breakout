CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -Wno-unused-parameter
SDL_FLAGS=`sdl2-config --libs --cflags` -lSDL2_image
SRC_DIR=src

main : $(SRC_DIR)/main.o $(SRC_DIR)/ball.o $(SRC_DIR)/player.o $(SRC_DIR)/brick.o $(SRC_DIR)/game.o $(SRC_DIR)/sprite.o $(SRC_DIR)/playstate.o $(SRC_DIR)/menustate.o $(SRC_DIR)/menuitem.o $(SRC_DIR)/scorestate.o $(SRC_DIR)/powerup.o $(SRC_DIR)/heart.o $(SRC_DIR)/background.o
	@ $(CXX) $(CXXFLAGS) main.o ball.o player.o brick.o game.o sprite.o playstate.o menustate.o menuitem.o scorestate.o powerup.o heart.o background.o -o breakout $(SDL_FLAGS)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $<

#all: main ball area


#main: $(SRC_DIR)/main.cc
#	g++ $(CXXFLAGS) $(SRC_DIR)/main.cc -o main $(SDL_FLAGS)

#ball: $(SRC_DIR)/ball.cc
#	g++ $(CXXFLAGS) $(SRC_DIR)/ball.cc -o ball $(SDL_FLAGS)

#area: $(SRC_DIR)/area.cc
#	g++ $(CXXFLAGS) $(SRC_DIR)/area.cc -o area $(SDL_FLAGS)

.PHONY clean:
	rm -f main.o ball.o player.o brick.o game.o sprite.o playstate.o menustate.o menuitem.o scorestate.o powerup.o heart.o background.o
