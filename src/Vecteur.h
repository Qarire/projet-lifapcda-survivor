#ifndef _VECTEUR_H
#define _VECTEUR_H


class Vecteur {
private :
    float x,y;

public :

    float getX(); const
    //Recupere la coordonnée X

    float getY(); const
    //Recupere la coordonnée Y

    Vecteur make_vec(float x, float y);
    //Fabrique un vecteur de coordonnée x,y

    Vecteur operator+(Vecteur a, float lambda);
    //operation + avec un Vecteur et un réel

    Vecteur operator-(Vecteur a, float lambda);
    //operation - avec un Vecteur et un réel

    Vecteur operator*(Vecteur a, float lambda);
    //operation * avec un Vecteur et un réel

    Vecteur operator/(Vecteur a, float lambda);
    //operation / avec un Vecteyr et un réel


}

#endif
