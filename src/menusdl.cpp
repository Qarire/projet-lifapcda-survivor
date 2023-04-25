#include <cstdio>
#include "menu.h"



const int MENU_MAX = 4;

void menuAff()
{
	printf("\nSURVIVOR\n");
	printf("1 : Jouer\n");
	//printf("2 : Description\n");
	printf("0 : Quitter\n");
	fflush(stdout);
}




ChoixMenu menuQuestion()
{
	menuAff();
	ChoixMenu cm;
	int i;
	char dum[32];
	bool ok=false;
	do
	{
		if (scanf("%d",&i)!=1) scanf("%s",dum);
		cm=((ChoixMenu)(i));
		if ((cm<0) || (cm>=MENU_MAX)) 
			printf("Erreur choix menu\n");
		else ok=true;
		fflush(stdout);
	} while(!ok);
	printf("\n"); fflush(stdout);
	return cm;
}




void menuRun()
{
	
	SDLSimple j;
	ChoixMenu ch;
	do
	{
		menuAff();
		scanf("%d", &ch);// ca marche parce que enum=entier
		switch(ch)
		{
			case MENU_Choix1 : j.sdlBoucle(); break;
			//case MENU_Choix2 : Description(); break;
			//case MENU_Quit : libereMemoire(); break;
			//default: erreurAff(); break;
		}
		//resultatAff();
	} while( ch!= MENU_Quit );
}