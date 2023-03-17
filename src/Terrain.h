#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

private:
    
    int dimx, dimy;

public:

    Terrain();
    /** @brief Constructeur par défaut; **/
    
    Terrain(unsigned int x, unsigned int y);
    /** @brief Constructeur */
    
    ~Terrain();
    /** @brief Destructeur ; **/

    unsigned int getDimx() const;
    /** @brief Recupere la dimension x du Terrain **/

    unsigned int getDimy() const;
    /** @brief Recupere la dimension du y du Terrain **/
    bool positionValide(const int x, const int y) const;

};

#endif
