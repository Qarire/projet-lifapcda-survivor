#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

    private:
        int dimx, dimy;
        char * tabTerrain;


public:

    Terrain();
    //Constructeur par défaut;

    ~Terrain();
    //Destructeur ;

    void getDimx();
    //Recupere la dimension x du Terrain

    void getDimy();
    //Recupere la dimension du y du Terrain






};
