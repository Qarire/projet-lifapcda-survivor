#include "Terrain.h"
#include<iostream>

using namespace std;


Terrain::Terrain(){
    dimx = 50;
    dimy = 50;
}

Terrain::Terrain(int x, int y){
    dimx = x;
    dimy = y;
}


Terrain::~Terrain(){
   
}


int Terrain::getDimx() const {
    
    return dimx;
}

int Terrain::getDimy() const {
    
    return dimy;
}

bool Terrain::positionValide(const int x, const int y) const{
    return (((x>=0) && (x<=dimx)) && ((y>=0) && (y<=dimy)));
 }
