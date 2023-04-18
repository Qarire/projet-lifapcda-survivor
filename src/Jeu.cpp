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
   map = Terrain(1900, 950); /* map = Terrain(500.1, 500.1); */ // map = Terrain(10000, 10000);
    /*joueur = Personnage(Vecteur(250, 250), 100);*/joueur = Personnage(Vecteur(1900/2, 950/2), 100);// joueur = Personnage(Vecteur(950, 475), 100);
    mob.push_back(Monstre(Vecteur(200, 205), 1));
    proj.push_back(Projectile(joueur.getPos(), Vecteur(), 1));
}
Jeu::~Jeu()
{
}
/*
int Jeu::gettemps() const
{
    return temps;
}

void Jeu::settemps(int t)
{
    temps=t;
}
*/

Personnage Jeu::getPersonnage() const
{

    return joueur;
}

Terrain Jeu::getTerrain() const
{

    return map;
}
/*
Monstre Jeu::getMonstre() const {

    return mob;
}*/

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

    // Si la distance entre le monstre et le personnage est <= 27 on inflige des degats
    //abs --> pour prendre la valeur absolue
    if (abs(joueur.getPos().getX() - mob.getPos().getX()) <= 27 && abs(joueur.getPos().getY() - mob.getPos().getY() <= 27)) // 12+25
    {
        new_pv_joueur = joueur.getPV() - 20; // joueur prend x points de degats par mob
        joueur.setPV(new_pv_joueur);

        new_pv_mob = mob.getPV() - 1; // mob prend x points de degats
        mob.setPV(new_pv_mob);
    }
}

void Jeu::degats_collision_proj(const Terrain &map, Monstre &mob, Projectile &proj)
{ // monstre & proj

    int new_pv_mob, new_pv_proj;
    // Si la distance entre le monstre et le projectil est <= 15 on inflige des degats
    if (abs( proj.getpos().getX() - mob.getPos().getX()) <=15 && abs( proj.getpos().getY() - mob.getPos().getY()<=15))
    {
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


void Jeu::verifierLimitesJoueur(const Terrain &map)
{
    // Vérifier si le joueur a atteint les limites de l'écran
    if (joueur.getPos().getX() >= map.getDimx()) {
        // Si le joueur atteint le bord droit, le faire réapparaître sur le bord gauche
        joueur.setPos(Vecteur(1, joueur.getPos().getY()));
    }
    else if (joueur.getPos().getX() <= 0) {
        // Si le joueur atteint le bord gauche, le faire réapparaître sur le bord droit
        joueur.setPos(Vecteur(map.getDimx()-1, joueur.getPos().getY()));
    }
    else if (joueur.getPos().getY() >= map.getDimy()) {
        // Si le joueur atteint le bord bas, le faire réapparaître sur le bord haut
        joueur.setPos(Vecteur(joueur.getPos().getX(), 1));
    }
    else if (joueur.getPos().getY() <= 0) {
        // Si le joueur atteint le bord haut, le faire réapparaître sur le bord bas
        joueur.setPos(Vecteur(joueur.getPos().getX(), map.getDimy()-1));
    }
   // cout <<"Jx= "<<joueur.getPos().getX()<<endl;
   // cout <<"Jy= "<<joueur.getPos().getY()<<endl;
   // cout <<"Mx= "<<map.getDimx()<<endl;
   // cout <<"My= "<<map.getDimy()<<endl;
}




/*void Jeu::actionAutomatiques()
{
    // parcourir les monstres
    cout<<"On parcour les monstres :"<<endl;
    for (auto it = mob.begin(); it != mob.end();)
    {
        // si le monstre est mort, le supprimer
        if (!it->enVie())
        {
            it = mob.erase(it);
        }
        else
        {
            // poursuivre le personnage
            it->poursuitePerso(map, joueur);     cout<<"Le monstre suit le perso :"<<endl;
            // infliger des dégâts au personnage en cas de collision
            degats_collision_mob(map, *it, joueur); cout<<" degat colision monstre :"<<endl;
            // trouver le projectile le plus proche du monstre
            double distance_min = std::numeric_limits<double>::infinity();
            int index_proj_proche = -1;

            // Boucle sur les projectiles
            cout<<" boucle sur les projectiles :"<<endl;
             for (auto it_p = proj.begin(); it_p != proj.end();) 
             {
                if (!it_p->enVie()) 
                {   cout<<" on vrifier si le projectile a touché un monstre pour l'effacer :"<<endl;
                    it_p = proj.erase(it_p);
                }
                else{
                    double distance = map.getDistance(it->getPos().getX(), it->getPos().getY(), it_p->getpos().getX(), it_p->getpos().getY());
                    
                if (distance < distance_min)
                {
                    distance_min = distance;
                    index_proj_proche = std::distance(proj.begin(), it_p);
                     cout<<"Le monstre le plus proche est loin de : "<<distance_min<<" px"<<endl;
                     cout<<" sont index est  :"<<index_proj_proche<<endl;
                }
                    else cout<<"Dans le else"<<endl;
                    return;
                }
            } cout<<" Sortie boucle proj :"<<endl;
            // si un projectile est trouvé, envoyer le projectile sur le monstre
            if (index_proj_proche != -1)
            {
                cout<<" avant proj poursuit monstre :"<<endl;
                proj[index_proj_proche].ProjectilePoursuiteMonstre(it->getPos(), map);
                cout<<" aprés proj poursuit monstre :"<<endl;
                // infliger des dégâts au monstre
                degats_collision_proj(map, *it, proj[index_proj_proche]);
            }
            else
            {
                // déplacement automatique du monstre
                it->poursuitePerso(map, joueur);
            }
            ++it; 
        }
    }
}*/

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
            int index_proj_proche = -1;

            // Boucler sur les projectiles pour trouver le projectile le plus proche
            for (auto it_p = proj.begin(); it_p != proj.end(); ++it_p)
            {
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

                double distance = map.getDistance(it_m->getPos().getX(), it_m->getPos().getY(), it_p->getpos().getX(), it_p->getpos().getY());
                if (distance < distance_min /*&& map.getDistance(joueur.getPos().getX(), joueur.getPos().getY(), it_m->getPos().getX(), it_m->getPos().getY()) <=300 */)
                {
                    distance_min = distance;
                    index_proj_proche = std::distance(proj.begin(), it_p);
                }
            }

            // Si un projectile est trouvé, envoyer le projectile sur le monstre
            if (index_proj_proche != -1)
            {
                // Envoyer le projectile sur le monstre
                proj[index_proj_proche].ProjectilePoursuiteMonstre(it_m->getPos(), map);

                // Infliger des dégâts au monstre en cas de collision
                degats_collision_proj(map, *it_m, proj[index_proj_proche]);
            }

            // Déplacer automatiquement le monstre
           // it_m->deplacementAuto(map);

            // Passer au monstre suivant
            ++it_m;
        }
    }
}


/*
Vecteur Jeu::tirerProjectile( const Personnage &p, const Terrain &t,
Monstre &mob, Projectile &proj )
{monstres
    // Trouver le monstre le plus proche
    double distance_min = std::numeric_limits<double>::infinity(); // initialisation avec une valeur très grande
    int index_monstre_proche = -1; // initialisation à -1 pour vérifier si on a trouvé un monstre
    for (long unsigned int i = 0; i < mob.size(); i++)
    {
        double distance = t.getDistance(p.getPos().getX(), p.getPos().getY(), monstres[i].getPos().getX(), monstres[i].getPos().getY());
        if (distance < distance_min) {
            distance_min = distance;
            index_monstre_proche = i;
            proj.ProjectilePoursuiteMonstre(mob[index_monstre_proche].getPos(),t);
        }
    }
    cout<<"Le monstre le plus proche est loin de : "<<distance_min<<" px"<<endl;
    // Si on a trouvé un monstre, créer un projectile qui le vise

}
*/