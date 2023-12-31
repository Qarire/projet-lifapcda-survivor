#include "Jeu.h"
#include <limits>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

Jeu::Jeu()
{
   map = Terrain(1800, 900); /* map = Terrain(500.1, 500.1); */
    /*joueur = Personnage(Vecteur(250, 250), 100);*/joueur = Personnage(Vecteur(1800/2, 900/2), 100);
    mob.push_back(Monstre(Vecteur(200, 205), 1));
    proj.push_back(Projectile(joueur.getPos(), Vecteur(), 1));
}
Jeu::~Jeu()
{
}

Personnage Jeu::getPersonnage() const
{

    return joueur;
}

Terrain Jeu::getTerrain() const
{

    return map;
}

vector<Monstre> Jeu::getVectorMonstre() const
{
    return mob;
}

vector<Projectile> Jeu::getVectorProjectile() const
{
    return proj;
}

void Jeu::genereMonstre(const Terrain &map)
{
    // Création d'un monstre avec x pv aleatoirement sur la map en fin de tableau
    mob.push_back(Monstre(Vecteur(rand() % map.getDimx(), rand() % map.getDimy()), 1));
}

void Jeu::genereProjectile(const Personnage &joueur)
{
    // Création d'un projectile sur la position du joueur avec une vitesse par défaut
    proj.push_back(Projectile(joueur.getPos(), Vecteur(), 1));
}

void Jeu::degats_collision_mob(const Terrain &map, Monstre &mob, Personnage &joueur)
{ // monstre & perso

    int new_pv_mob;
    int new_pv_joueur;

    int degats = rand() % 6 + 6; //Dégats aléatoire pour le personnage

    // Calcul de la distance entre le personnage et le monstre
    float distance = map.getDistance(joueur.getPos().getX(), joueur.getPos().getY(), mob.getPos().getX(), mob.getPos().getY());

    // Si la distance entre le monstre et le personnage est <= 20 on inflige des degats
    if (distance <= 20) 
    {
        new_pv_joueur = joueur.getPV() - degats; // joueur prend x points de degats par mob
        joueur.setPV(new_pv_joueur);

        new_pv_mob = mob.getPV() - 1; // mob prend x points de degats
        mob.setPV(new_pv_mob);
    }
}



void Jeu::degats_collision_proj(const Terrain &map, Monstre &mob, Projectile &proj)
{ // monstre & proj

    int new_pv_mob, new_pv_proj;
    // Si la distance entre le monstre et le projectil est <= 15 on inflige des degats
    if (abs( proj.getpos().getX() - mob.getPos().getX()) <=5 && abs( proj.getpos().getY() - mob.getPos().getY()<=5)) //15
    {
        proj.col_proj_mob=true;
        new_pv_mob = mob.getPV() - 1; // monstre prend x points de degats par projectile
        mob.setPV(new_pv_mob);

        new_pv_proj = proj.getPV() - 1; // proj prend x points de degats par monstre
        proj.setPV(new_pv_proj);
    }
}

bool Jeu::FinJeu(const Personnage &joueur)
{
    return (joueur.enVie());
}

bool Jeu::actionClavier(const char touche)
{
    switch (touche)
    {
    case 'z':
        joueur.depHaut(map);
        break;

    case 'd':
        joueur.depDroite(map);
        break;

    case 'q':
        joueur.depGauche(map);
        break;

    case 's':
        joueur.depBas(map);
        break;

    case 'o':
        genereProjectile(joueur);
        break;
    }

    return false;
}


void Jeu::actionAutomatiques()
{   
    // Parcourir les monstres
    for (auto it_m = mob.begin(); it_m != mob.end();)
    {
        // Vérifier si le monstre est mort et le supprimer s'il est mort
        if (!it_m->enVie())
        {
            it_m = mob.erase(it_m);
        }
        else
        {
            // Faire poursuivre le personnage par le monstre
            it_m->poursuitePerso(map, joueur);
            // it->deplacementNaturel(map);
            // Infliger des dégâts au personnage en cas de collision
            degats_collision_mob(map, *it_m, joueur);

            // Trouver le projectile le plus proche du monstre
            double distance_min = std::numeric_limits<double>::infinity();
            int index_monstre_proche = -1;

            // Boucler sur les projectiles pour trouver le projectile le plus proche
            for (auto it_p = proj.begin(); it_p != proj.end(); ++it_p)
            {
                // Vérifier si le projectile a déjà une cible
                if (it_p->getTarget())
                {
                    continue; // Passer directement au projectile suivant
                }

                // Vérifier si le projectile est mort et le supprimer s'il est mort
                if (!it_p->enVie())
                {
                    it_p = proj.erase(it_p);
                    // Si on supprime un projectile, on doit repartir depuis le début de la boucle
                    // pour ne pas sauter d'éléments
                    if (it_p == proj.end())
                    {
                        break;
                    }
                }

                 // Condition pour vérifier si le projectile n'a pas de cible (ne fonctionne pas correctement!)
                /*if (!it_p->getTarget())
                {
                    it_p->setpos(joueur.getPos()); // Si le projectile n'a pas de cible, coller au personnage
                }*/

                double distance = map.getDistance(it_m->getPos().getX(), it_m->getPos().getY(), it_p->getpos().getX(), it_p->getpos().getY());
                if (distance < distance_min && (!it_p->getTarget())  && distance<=350 )
                {
                    distance_min = distance;
                    index_monstre_proche = std::distance(proj.begin(), it_p); //Récupérer l'indice du projectile
                }
                
            }

            // Si un projectile est trouvé, envoyer le projectile sur le monstre
            if (index_monstre_proche != -1)
            {
        
                // Envoyer le projectile sur le monstre
                proj[index_monstre_proche].ProjectilePoursuiteMonstre(it_m->getPos(), map);
                proj[index_monstre_proche].setTarget(true); // Marquer le projectile comme ayant une cible
                proj[index_monstre_proche].setTarget(false); // Mettre hasTarget à false
                // Infliger des dégâts au monstre en cas de collision
                degats_collision_proj(map, *it_m, proj[index_monstre_proche]);
            }

            // Déplacer automatiquement le monstre
            // it_m->deplacementAuto(map);

            // Passer au monstre suivant
            ++it_m;
        }
    }
}

void Jeu::verifierLimitesJoueur(const Terrain &map)
{
    // Vérifier si le joueur a atteint les limites de l'écran
    if (joueur.getPos().getX() >= map.getDimx() && joueur.getPos().getY() >= map.getDimy()/3 && joueur.getPos().getY() <= map.getDimy()*2/3) {
        // Si le joueur atteint le bord droit, le faire réapparaître dans le tunnel gauche
        joueur.setPos(Vecteur(1, joueur.getPos().getY()));
    }
    else if (joueur.getPos().getX() <= 0 && joueur.getPos().getY() >= map.getDimy()/3 && joueur.getPos().getY() <= map.getDimy()*2/3) {
        // Si le joueur atteint le bord gauche, le faire réapparaître dans le tunnel droit
        joueur.setPos(Vecteur(map.getDimx()-1, joueur.getPos().getY()));
    }
    else if (joueur.getPos().getY() >= map.getDimy() && joueur.getPos().getX() >= map.getDimx()/3 && joueur.getPos().getX() <= map.getDimx()*2/3) {
        // Si le joueur atteint le bord bas, le faire réapparaître dans la zone supérieure
        joueur.setPos(Vecteur(joueur.getPos().getX(), 1));
    }
    else if (joueur.getPos().getY() <= 0 && joueur.getPos().getX() >= map.getDimx()/3 && joueur.getPos().getX() <= map.getDimx()*2/3) {
        // Si le joueur atteint le bord haut, le faire réapparaître dans la zone inférieure
        joueur.setPos(Vecteur(joueur.getPos().getX(), map.getDimy()-1));
    }
    else if (joueur.getPos().getY() >= map.getDimy() && joueur.getPos().getX() < map.getDimx()/3) {
        // Si le joueur atteint le bord bas gauche, le faire réapparaître dans la zone supérieure droite
        joueur.setPos(Vecteur(map.getDimx()+1, map.getDimy()/3));
    }
    else if (joueur.getPos().getY() <= 0 && joueur.getPos().getX() < map.getDimx()/3) {
        // Si le joueur atteint le bord haut gauche, le faire réapparaître dans la zone inférieure droite
        joueur.setPos(Vecteur(map.getDimx()+1, map.getDimy()*2/3));
    }
    else if (joueur.getPos().getY() >= map.getDimy() && joueur.getPos().getX() > map.getDimx()*2/3) {
        // Si le joueur atteint le bord bas droit, le faire réapparaître dans la zone supérieure gauche
        joueur.setPos(Vecteur(1, map.getDimy()/3));
    }
    else if (joueur.getPos().getY() <= 0 && joueur.getPos().getX() > map.getDimx()*2/3) {
        // Si le joueur atteint le bord haut droit, le faire réapparaître dans la zone inférieure gauche
        joueur.setPos(Vecteur(1, map.getDimy()*2/3));
    }
}