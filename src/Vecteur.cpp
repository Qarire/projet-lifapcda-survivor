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

float Vecteur::getX() const {

    return x;
}

float Vecteur::getY() const {

    return y;
}


Vecteur Vecteur::operator+(float lambda) {
    
    Vecteur res;
    
    res.x = x + lambda;
    res.y = y + lambda;

    return res;
}
    
Vecteur Vecteur::operator-(float lambda) {
    
    Vecteur res;
    
    res.x = x - lambda;
    res.y = y - lambda;

    return res;
}

Vecteur Vecteur::operator*(float lambda){
    
    Vecteur res;
    
    res.x = x * lambda;
    res.y = y * lambda;

    return res;
}


Vecteur Vecteur::operator+(Vecteur v){
    
    Vecteur res;

    res.x = x + v.getX();
    res.y = y + v.getY();

    return res;
}

Vecteur Vecteur::operator-(Vecteur v){
    
    Vecteur res;

    res.x = x - v.getX();
    res.y = y - v.getY();

    return res;
}

