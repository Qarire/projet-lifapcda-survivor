LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL
INCLUDE_DIR_SDL = -I/usr/include/SDL2
LDFLAGS  =
CCOPTIONS = -Wall -ggdb 
CC = g++ $(CCOPTIONS)
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = -Isrc


all: $(BIN_DIR)/main_SDL $(BIN_DIR)/main_TXT


$(BIN_DIR)/main_SDL: $(OBJ_DIR)/main_SDL.o $(OBJ_DIR)/Personnage.o $(OBJ_DIR)/Monstre.o $(OBJ_DIR)/Projectile.o $(OBJ_DIR)/Terrain.o $(OBJ_DIR)/Vecteur.o $(OBJ_DIR)/Jeu.o $(OBJ_DIR)/winSdl.o
	$(CC) $(OBJ_DIR)/main_SDL.o $(OBJ_DIR)/Personnage.o $(OBJ_DIR)/Monstre.o $(OBJ_DIR)/Projectile.o $(OBJ_DIR)/Terrain.o $(OBJ_DIR)/Vecteur.o $(OBJ_DIR)/Jeu.o $(OBJ_DIR)/winSdl.o -o $(BIN_DIR)/main_SDL $(LIBS_SDL)


$(BIN_DIR)/main_TXT: $(OBJ_DIR)/main_TXT.o $(OBJ_DIR)/Personnage.o $(OBJ_DIR)/Monstre.o $(OBJ_DIR)/Projectile.o $(OBJ_DIR)/Terrain.o $(OBJ_DIR)/Vecteur.o $(OBJ_DIR)/Jeu.o $(OBJ_DIR)/winTxt.o
	$(CC) $(OBJ_DIR)/main_TXT.o $(OBJ_DIR)/Personnage.o $(OBJ_DIR)/Monstre.o $(OBJ_DIR)/Projectile.o $(OBJ_DIR)/Terrain.o $(OBJ_DIR)/Vecteur.o $(OBJ_DIR)/Jeu.o $(OBJ_DIR)/winTxt.o  -o $(BIN_DIR)/main_TXT $(LDFLAGS)


	
$(OBJ_DIR)/Vecteur.o: $(SRC_DIR)/Vecteur.cpp $(SRC_DIR)/Vecteur.h
	$(CC) -c $(SRC_DIR)/Vecteur.cpp -o $(OBJ_DIR)/Vecteur.o

$(OBJ_DIR)/winTxt.o: $(SRC_DIR)/winTxt.cpp $(SRC_DIR)/winTxt.h
	$(CC) -c $(SRC_DIR)/winTxt.cpp -o $(OBJ_DIR)/winTxt.o

$(OBJ_DIR)/Terrain.o: $(SRC_DIR)/Terrain.cpp $(SRC_DIR)/Terrain.h
	$(CC) -c $(SRC_DIR)/Terrain.cpp -o $(OBJ_DIR)/Terrain.o

$(OBJ_DIR)/Projectile.o: $(SRC_DIR)/Projectile.cpp $(SRC_DIR)/Projectile.h $(SRC_DIR)/Vecteur.h
	$(CC) -c $(SRC_DIR)/Projectile.cpp -o $(OBJ_DIR)/Projectile.o

$(OBJ_DIR)/Personnage.o: $(SRC_DIR)/Personnage.cpp $(SRC_DIR)/Personnage.h $(SRC_DIR)/Projectile.h $(SRC_DIR)/Terrain.h $(SRC_DIR)/Vecteur.h
	$(CC) -c $(SRC_DIR)/Personnage.cpp -o $(OBJ_DIR)/Personnage.o

$(OBJ_DIR)/Monstre.o: $(SRC_DIR)/Monstre.cpp $(SRC_DIR)/Monstre.h $(SRC_DIR)/Personnage.h $(SRC_DIR)/Terrain.h $(SRC_DIR)/Vecteur.h
	$(CC) -c $(SRC_DIR)/Monstre.cpp -o $(OBJ_DIR)/Monstre.o

$(OBJ_DIR)/Jeu.o: $(SRC_DIR)/Jeu.cpp $(SRC_DIR)/Jeu.h $(SRC_DIR)/Projectile.h $(SRC_DIR)/Terrain.h $(SRC_DIR)/Vecteur.h $(SRC_DIR)/Personnage.h $(SRC_DIR)/Monstre.h
	$(CC) -c $(SRC_DIR)/Jeu.cpp -o $(OBJ_DIR)/Jeu.o

$(OBJ_DIR)/main_SDL.o: $(SRC_DIR)/Personnage.cpp $(SRC_DIR)/Personnage.h $(SRC_DIR)/Projectile.h $(SRC_DIR)/Terrain.h $(SRC_DIR)/Vecteur.h $(SRC_DIR)/main_SDL.cpp
	$(CC) -c $(SRC_DIR)/main_SDL.cpp -o $(OBJ_DIR)/main_SDL.o

$(OBJ_DIR)/main_TXT.o: $(SRC_DIR)/main_TXT.cpp $(SRC_DIR)/Jeu.h $(SRC_DIR)/winTxt.h
	$(CC) -c $(SRC_DIR)/main_TXT.cpp -o $(OBJ_DIR)/main_TXT.o


$(OBJ_DIR)/winSdl.o : $(SRC_DIR)/winSdl.cpp $(SRC_DIR)/winSdl.h $(SRC_DIR)/Jeu.h
	$(CC) -c $(INCLUDE_DIR_SDL) $(SRC_DIR)/winSdl.cpp -o $(OBJ_DIR)/winSdl.o
	
#docu: doc/XXX
#	cd doc ; doxygen XXX


clean:
	rm $(OBJ_DIR)/*.o

veryclean:
	rm $(BIN_DIR)/*
