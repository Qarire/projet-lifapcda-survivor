#include "Terrain.h"
#include<iostream>

using namespace std;


Terrain::Terrain(){
    dimx = 250;
    dimy = 250;
}

Terrain::Terrain(int x, int y){
    dimx = x;
    dimy = y;
}

Terrain::~Terrain(){
    dimx = nullptr;
    dimy = nullptr;
}

int Terrain::getDimx(){
    
    return dimx;
}

int Terrain::getDimy(){
    
    return dimy;
}
