#include "Terrain.h"
#include<iostream>
#include<math.h>
using namespace std;


Terrain::Terrain(){
    dimx = 50;
    dimy = 50;
}

Terrain::Terrain(unsigned int x,unsigned int y){ 
    dimx = x;
    dimy = y;
}


Terrain::~Terrain(){
   
}


unsigned int Terrain::getDimx() const {
    
    return dimx;
}

unsigned int Terrain::getDimy() const {
    
    return dimy;
}

bool Terrain::positionValide(const int x, const int y) const{
    return (((x>=0) && (x<=dimx)) && ((y>=0) && (y<=dimy)));
 }

float Terrain::getDistance (float x1, float y1, float x2, float y2) const 
{
    return (sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ));
}
