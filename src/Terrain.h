#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

private:
    
    int dimx, dimy;

public:

    Terrain();
    /** @brief Constructeur par défaut; **/
    
    Terrain(int x, int y);
    /** @brief Constructeur */
    
    ~Terrain();
    /** @brief Destructeur ; **/

    int getDimx() const;
    /** @brief Recupere la dimension x du Terrain **/

    int getDimy() const;
    /** @brief Recupere la dimension du y du Terrain **/
    bool positionValide(const int x, const int y) const;

};

#endif
