#ifndef _VECTEUR_H
#define _VECTEUR_H


class Vecteur {

private :
    
    float x,y;

public :

    Vecteur();
    /** @brief constructeur par défaut*/

    Vecteur(float a, float b);
    /** @brief constructeur */

    ~Vecteur();
    /** @brief destructeur */
    
    float getX() const;
    /** @brief Recupere la coordonnée X */

    float getY() const;
    /** @brief Recupere la coordonnée Y */

    Vecteur operator+(float lambda);
    /** @brief operation + avec un Vecteur et un réel */

    Vecteur operator-(float lambda);
    /** @brief operation - avec un Vecteur et un réel */

    Vecteur operator*(float lambda);
    /** @brief operation * avec un Vecteur et un réel */


    Vecteur operator+(Vecteur v);
    /** @brief operation + avec deux Vecteurs */

    Vecteur operator-(Vecteur v);
    /** @brief operation - avec deux Vecteurs */

    bool operator==(Vecteur v);
    /** @brief Operateur d'egalite entre deux vecteurs */

 	void setX(float x);
 	/** @brief modifier la coordonnée X du vecteur */
 	
 	void setY(float y);
	/** @brief modifier la coordonnée Y du vecteur */

};
#endif
