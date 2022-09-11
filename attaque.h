#ifndef ATTAQUE_H_INCLUDED
#define ATTAQUE_H_INCLUDED

#define NIMG 3
#define LARGEUR 70
#define LARGEUR2 53
#define LARGEUR3 62
#define HAUTEUR 82
#define NACTEUR 10
#include "collisions.h"
#include "def_tot.h"

///prototypes et stuctures d'attaque


typedef struct ennemi
{
    int x,y;
    int dx,dy;
    int tx,ty;
    int imgcourante;
    int cptimg;
    int tmpimg;
    int vie;
    //  BITMAP *tab[nmb];

} t_ennemi;

typedef struct ennemi2
{
    int x2,y2;
    int dx2,dy2;
    int tx2,ty2;
    int imgcourante2;
    int cptimg2;
    int tmpimg2;
    int vie2;
    //  BITMAP *tab[nmb];

} t_ennemi2;

typedef struct ennemi3
{
    int x3,y3;
    int dx3,dy3;
    int tx3,ty3;
    int imgcourante3;
    int cptimg3;
    int tmpimg3;
    int vie3;

} t_ennemi3;

void remplirToustab_3(t_ennemi*mesEnnemis[NACTEUR],t_ennemi2*mesEnnemis2[NACTEUR],t_ennemi3*mesEnnemis3[NACTEUR]);
void remplirToustab_2(t_ennemi*mesEnnemis[NACTEUR],t_ennemi2*mesEnnemis2[NACTEUR]);
void chargerToutesAnimation_3(BITMAP*animation[NIMG],BITMAP*animation2[NIMG],BITMAP*animation3[NIMG]);
void chargerToutesAnimation_2(BITMAP*animation[NIMG],BITMAP*animation2[NIMG]);
void actualiserToutTabEnnemi2(t_ennemi *tab[NACTEUR],t_ennemi2*tab2[NACTEUR], BITMAP* page);
void actualiserToutTabEnnemi3(t_ennemi *tab[NACTEUR],t_ennemi2*tab2[NACTEUR],t_ennemi3*tab3[NACTEUR], BITMAP* page);
void dessinerToutTabEnnemi2(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG],t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG]);
void dessinerToutTabEnnemi3(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG],t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG],t_ennemi3*tab3[NACTEUR],BITMAP*animation3[NIMG]);

void chargerAnimation(BITMAP*animation[NIMG]);
void chargerAnimation2(BITMAP*animation2[NIMG]);
void chargerAnimation3(BITMAP*animation3[NIMG]);

t_ennemi*creer();
t_ennemi2*creer2();
t_ennemi3*creer3();

void remplirTabActeur(t_ennemi*tab[NACTEUR]);
void remplirTabActeur2(t_ennemi2*tab2[NACTEUR]);
void remplirTabActeur3(t_ennemi3*tab3[NACTEUR]);

void actualiser_ennemi(t_ennemi*ennemi, BITMAP* page);
void actualiser_ennemi2(t_ennemi2*ennemi, BITMAP* page);
void actualiser_ennemi3(t_ennemi3*ennemi,BITMAP* page);

void actualiserTabEnnemi(t_ennemi*tab[NACTEUR], BITMAP* page);
void actualiserTabEnnemi2(t_ennemi2*tab[NACTEUR], BITMAP* page);
void actualiserTabEnnemi3(t_ennemi3*tab[NACTEUR], BITMAP* page);

void dessinerEnnemi(BITMAP*bmp,t_ennemi*ennemi,BITMAP*animation[NIMG]);
void dessinerEnnemi2(BITMAP*bmp,t_ennemi2*ennemi,BITMAP*animation2[NIMG]);
void dessinerEnnemi3(BITMAP*bmp,t_ennemi3*ennemi,BITMAP*animation3[NIMG]);

void dessinerTabEnnemi(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG]);
void dessinerTabEnnemi2(BITMAP*bmp,t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG]);
void dessinerTabEnnemi3(BITMAP*bmp,t_ennemi3*tab3[NACTEUR],BITMAP*animation3[NIMG]);

void DefenseToTomate(t_ennemi* ennemi, t_defense* defense);
void TabDefenseToTomate(t_ennemi*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page);
int collisionEnemy(t_ennemi*ennemi[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses);
void TabDefenseToBroccolis(t_ennemi2*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page);
int collisionEnemy2(t_ennemi2*ennemi[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses);
void TabDefenseToPommeDeTerre(t_ennemi3*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page);
int collisionEnemy3(t_ennemi3*ennemi[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses);
void TomatesToFrite(t_ennemi* ennemi[NACTEUR], t_frites* frite[NACTEURD],BITMAP* page);
int collisionFrite(t_ennemi*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page);
void BrocolisToFrite(t_ennemi2* ennemi[NACTEUR], t_frites* frite[NACTEURD],BITMAP* page);
int collisionFrite2(t_ennemi2*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page);
void PommeDeTerreToFrite(t_ennemi3* ennemi[NACTEUR], t_frites* frite[NACTEURD],BITMAP* page);
int collisionFrite3(t_ennemi3*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page);

#endif // ATTAQUE_H_INCLUDED
