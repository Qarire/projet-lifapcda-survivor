#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

    private:
        int dimx, dimy;


public:

    Terrain();
    /** @brief Constructeur par défaut; **/

    ~Terrain();
    /** @brief Destructeur ; **/

    int getDimx() const;
    /** @brief Recupere la dimension x du Terrain **/

    int getDimy() const;
    /** @brief Recupere la dimension du y du Terrain **/


};

#endif
