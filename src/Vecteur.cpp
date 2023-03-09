#include "Vecteur.h"
#include <iostream>

using namespace std;


Vecteur::Vecteur(){
    x = 0;
    y = 0;
}

Vecteur::Vecteur(float a, float b) {
    x = a;
    y = b;
}

void Vecteur::getX() const {

    return x;
}

void Vecteur::getY() const {

    return y;
}


Vecteur Vecteur::operator+(float lambda){
    
    x = x + lambda;
    y = y + lambda;

    return this;
}
    
Vecteur Vecteur::operator-(float lambda){
    
    x = x - lambda;
    y = y - lambda;

    return this;
}

Vecteur Vecteur::operator*(float lambda){
    
    x = x * lambda;
    y = y * lambda;

    return this;
}


Vecteur Vecteur::operator+(Vecteur v){
    x = x + v.getX();
    y = y + v.getY();

    return this;
}

Vecteur Vecteur::operator-(Vecteur v){
    x = x - v.getX();
    y = y - v.getY();

    return this;
}

