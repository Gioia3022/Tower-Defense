#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define NBRFRITES 5
#include <allegro.h>
#include "def_tot.h"

///prototypes et stuctures des collisions

typedef struct frites
{
    int dx;
    int x,y;
    int tx,ty;
    int nbr;
    int vie;

} t_frites;

typedef struct ketchup
{
    int x,y;
    int tx,ty;

} t_ketchup;

t_frites*creerFrites();
void remplirTabFrite(t_frites*frite[NACTEURD]);
void actualiserFrites(t_frites*frite,t_defense*defense);
void actualiserTabFrites(t_frites*frite[NACTEURD],t_defense*defense[NACTEURD]);
void dessinerFrites(BITMAP*page,BITMAP*frite,t_frites*missile,t_defense*defense);
void dessinerTabFrites(BITMAP*page,BITMAP*frite,t_frites*missile[NACTEURD],t_defense*tab[NACTEURD]);
float frand(float min, float max);
t_frites * ajouterMissile(t_frites *la[NACTEURD]);

t_ketchup*creerKetchup();
void remplirTabKetchup(t_ketchup*tab[NACTEURD]);
void actualiserKetchup(t_ketchup*ketchup,t_defense*defense);
void actualiserTabKetchup(t_ketchup*tab[NACTEURD],t_defense*tab2[NACTEURD]);
void dessinerKetchup(BITMAP*page,BITMAP*ketchup,t_ketchup*missile,t_defense*defense);
void dessinerTabKetchup(BITMAP*page,BITMAP*ketchup,t_ketchup*tab[NACTEURD],t_defense*tab2[NACTEURD]);



#endif // COLLISIONS_H_INCLUDED
