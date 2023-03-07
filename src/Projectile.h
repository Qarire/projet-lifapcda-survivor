#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Vecteur.h"

class Projectile {
    private :
	Vecteur pos, vit;
	
    public:

		Projectile();
		/** @brief Constructeur du projectile **/

		~Projectile();
		/** @brief Destructeur du projectile **/

		Vecteur getpos();
    	/** @brief recupere la position du projectile **/
    	
    	Vecteur getvit();
    	/** @brief recupere la vitesse du projectile **/
	
	

#endif
