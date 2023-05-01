#ifndef _VECTEUR_H
#define _VECTEUR_H


class Vecteur {

private :
    
    float x,y;   /** @brief deux réels pour pour désigner des coordonnées*/

public :

    Vecteur();
    /** @brief constructeur par défaut*/

    Vecteur(float a, float b);
    /** @brief constructeur par copie */

    ~Vecteur();
    /** @brief destructeur par défaut */
    
    float getX() const;
    /** @brief Recupere la coordonnée X */

    float getY() const;
    /** @brief Recupere la coordonnée Y */

    Vecteur operator+(float lambda);
    /** @brief operation + avec un Vecteur et un réel 
    * @param un réel pour l'additionner au vecteur    */

    Vecteur operator-(float lambda);
    /** @brief operation - avec un Vecteur et un réel 
      * @param un réel pour le soustraire du vecteur    */

    Vecteur operator*(float lambda);
    /** @brief operation * avec un Vecteur et un réel */


    Vecteur operator+(Vecteur v);
    /** @brief operation + avec deux Vecteurs 
      * @param un deuxiéme vecteur pour l'additionner   */

    Vecteur operator-(Vecteur v);
    /** @brief operation - avec deux Vecteurs 
    * @param un deuxiéme vecteur pour le soustraire   */

    bool operator==(Vecteur v);
    /** @brief Operateur d'egalite entre deux vecteurs 
    * @param un deuxiéme vecteur pour l'affecter   */

 	void setX(float x);
 	/** @brief modifier la coordonnée X du vecteur
    * @param un réel pour la coordonné x */
 	
 	void setY(float y);
	/** @brief modifier la coordonnée Y du vecteur 
    * @param un réel pour la coordonné y */

};
#endif
