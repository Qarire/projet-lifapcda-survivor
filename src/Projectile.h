#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Vecteur.h"
#include "Terrain.h"


class Projectile {
    private :
	
	Vecteur p,v;

    public:

		Projectile();
		/** @brief Constructeur par défaut du projectile **/

		Projectile(Vecteur pos, Vecteur vit);
		/** @brief Constructeur */

		~Projectile();
		/** @brief Destructeur du projectile **/

		Vecteur getpos() const;
    	/** @brief recupere la position du projectile **/
    	
		void depDroite (const Terrain &t);
		/** @brief deplacement droite projectile*/

		void depAuto (const Terrain &t);
		/** @brief deplacement auto projectile*/
		
    	Vecteur getvit() const;
    	/** @brief recupere la vitesse du projectile **/
	
	
};

#endif
