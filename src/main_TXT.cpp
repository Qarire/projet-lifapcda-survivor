//sudo apt install python3 valgrind doxygen libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev imagemagick

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include "winTxt.h"
#include <vector>
#include "Jeu.h"

#include<time.h>
#include <ctime>

using namespace std;

void txtAff(WinTXT & win, const Jeu & jeu) {
	const Terrain &ter = jeu.getTerrain();
	const Personnage &per = jeu.getPersonnage();
	const vector<Monstre> &mon = jeu.getVectorMonstre();
	const vector<Projectile> &proj= jeu.getVectorProjectile();
	win.clear();
	
	//Affichage du Personnage
	win.print(per.getPos().getX(),per.getPos().getY(),'P');
	
	//Affichage des Monstres
	for(unsigned int i=0;i<mon.size();i++)	
	{
		//if(mon.at(i).enVie())
		//{
			win.print(mon.at(i).getPos().getX(),mon.at(i).getPos().getY(),'M');
		//}	
		
	}
	
	//Affichage des projectiles
	for(unsigned int i=0;i<proj.size();i++)
	{
		win.print(proj.at(i).getpos().getX(),proj.at(i).getpos().getY(),'.');
	}
		//win.print(proj.at(proj.size()-1).getpos().getX(),proj.at(proj.size()-1).getpos().getY(),'-');
	//Affichage du Terrain
	for(unsigned int i=0;i<ter.getDimx();i++) // 1ere ligne horizontale
	{
		win.print(i,0,'*');
	}

	for(unsigned int j=0;j<ter.getDimy();j++) //Les 2 lignes verticales
	{
		win.print(0,j,'*');
		win.print(ter.getDimx()-1,j,'*');
	}

	for(unsigned int i=0;i<ter.getDimx();i++) // 2e ligne horizontale
	{
		win.print(i,ter.getDimy()-1,'*');
	}
	
	win.draw();
}

void txtBoucle (Jeu & jeu) {

	WinTXT win (jeu.getTerrain().getDimx(),jeu.getTerrain().getDimy());

	bool stop = false;
	
	srand(time(NULL));
    clock_t debut = clock();
    
       
      

	do
	{
		txtAff(win,jeu);

		 #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32
		
		jeu.actionAutomatiques();
		
		clock_t fin = clock();
      	int duree = (int)(fin - debut) / 10000;
		if (duree>=1){
			debut=fin;
			jeu.genereMonstre(jeu.getTerrain());
		}	

		int c = win.getCh();
		switch (c) {
				case 'z':
				jeu.actionClavier('z');
				break;
			case 'q':
				jeu.actionClavier('q');
				break;
			case 'd':
				jeu.actionClavier('d');
				break;
			case 's':
				jeu.actionClavier('s');
				break;
			case 'o':
				jeu.actionClavier('o');
				break;
			case 'b':
				stop = true; 		//Touche b pour stoper le jeu
				break;	
		}

		if(!jeu.FinJeu(jeu.getPersonnage())) {
			stop = true;
		}

	} while (!stop);
	


}

int main(int argc, char** argv)
{
	
	
	
	
	termClear();
	Jeu jeu;
	txtBoucle(jeu);
	termClear();

	return 0;
}


