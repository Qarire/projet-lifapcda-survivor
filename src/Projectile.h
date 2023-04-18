#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#define PR_DIST 5
#include "Vecteur.h"
#include "Terrain.h"


class Projectile {
    private :
	
	Vecteur p,v;
	int p_pv;

    public:

		Projectile();
		/** @brief Constructeur par défaut du projectile **/

		Projectile(Vecteur pos, Vecteur vit, int hp);
		/** @brief Constructeur */

		~Projectile();
		/** @brief Destructeur du projectile **/

		Vecteur getpos() const;
    	/** @brief recupere la position du projectile **/
    	
		void depDroite (const Terrain &t);
		/** @brief deplacement droite projectile*/
		void depGauche (const Terrain &t);
		/** @brief deplacement droite projectile*/
		void depHaut (const Terrain &t);
		/** @brief deplacement droite projectile*/
		void depBas (const Terrain &t);
		/** @brief deplacement droite projectile*/
		void depAuto (const Terrain &t);
		/** @brief deplacement auto projectile*/
		
    	Vecteur getvit() const;
    	/** @brief recupere la vitesse du projectile **/
	
		void ProjectilePoursuiteMonstre(const Vecteur& arrivee, const Terrain &t);

		bool enVie() const;

		/** @brief accesseur pour récuperer les points de vie d'un monstre
     	**/
	int getPV() const;
	
	/** @brief Mutateur pour modifier les points de vie d'un monstre*/
	void setPV(int hp);
	
};

#endif
