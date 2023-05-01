#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

private:
    
    int dimx, dimy; /** @brief les deux dimension du terrain */

public:

    Terrain();
    /** @brief Constructeur par défaut; **/
    
    Terrain(unsigned int x, unsigned int y);
    /** @brief Constructeur par copie */
    
    ~Terrain();
    /** @brief Destructeur par défaut **/

    unsigned int getDimx() const;
    /** @brief Recupere la dimension x du Terrain **/

    unsigned int getDimy() const;
    /** @brief Recupere la dimension du y du Terrain **/

    bool positionValide(const int x, const int y) const;
    /** @brief renvoie un boolean pour érifier si le personnage est bien positionner dans les limites du terrain 
     * @param une position en x et en y*/

    float getDistance (float x1, float y1, float x2, float y2) const ;
	/** @brief fonction qui permet de calculer et retourné la distance entre deux points sur le terrain 
     * @param quatres entiers pour le deux vecteurs position **/	 
};

#endif
