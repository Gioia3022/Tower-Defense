#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "attaque.h"
#include "def_tot.h"
#include "Global.h"


///lignes sur lesquelles on peut placer les deffenses
int ligneDef[5]= {500,600,700,800,900};


void chargerFichier(BITMAP* tab[NIMG])///charge l'ensemble des images

{

    int j;

    char nomfichier[256];

    for(j=0; j<NIMG; j++)

    {
        sprintf(nomfichier,"defense%d.bmp",j);
        tab[j]=load_bitmap(nomfichier,NULL);
        if(!tab[j])
        {
            allegro_message("Pb de mode graphique") ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
}

void chargerFichier2(BITMAP*animation[NIMAG])///charge les hamburgers
{
    int j;

    char nomfichier[256];

    for(j=0; j<NIMAG; j++)

    {

        sprintf(nomfichier,"defenses/hamburgers/hamburger%d.bmp",j);

        animation[j]=load_bitmap(nomfichier,NULL);

        if(!animation[j])
        {
            allegro_message("Pb de mode graphique") ;

            allegro_exit();

            exit(EXIT_FAILURE);
        }
    }
}

void chargerFichier3(BITMAP*animation[NIMAG])///charge les hotdogs
{
    int j;
    char nomfichier[256];
    for(j=0; j<NIMAG; j++)
    {
        sprintf(nomfichier,"defenses/hot_dogs/hot_dog%d.bmp",j);
        animation[j]=load_bitmap(nomfichier,NULL);
        if(!animation[j])
        {
            allegro_message("Pb de hot dog%d",j) ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
}

void chargerFichier4(BITMAP*animation[NIMAG])///charge les pizzas
{
    int j;
    char nomfichier[256];
    for(j=0; j<NIMAG; j++)
    {
        sprintf(nomfichier,"defenses/pizzas/pizza%d.bmp",j);
        animation[j]=load_bitmap(nomfichier,NULL);
        if(!animation[j])
        {
            allegro_message("Pb de hot dog%d",j) ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
}


/**************************************************************************/

/*void chargerMoney(BITMAP* money[NIMG])///charge l'ensemble des images
{
    int j;
    char nomfichier[256];
    for(j=0; j<NIMG; j++)
    {
        sprintf(nomfichier,"argent/argent%d.bmp",j);
        money[j]=load_bitmap(nomfichier,NULL);
        if(!money[j])
        {
            allegro_message("Pb de mode graphique") ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }

    }
}
*/
/**************************************************************************/

void chargerTousDefenses(BITMAP*animationd[NIMG],BITMAP*animation2d[NIMG],BITMAP*animation3d[NIMG],BITMAP*tab[NIMG])
///fonction qui appelles l'intégralité des fonctions pour charger
{
    chargerFichier(tab);
    chargerFichier2(animationd);
    chargerFichier3(animation2d);
    chargerFichier4(animation3d);
}



t_defense*creerD()///création de toutes les défenses
{
    t_defense*defense;
    defense=(t_defense*)malloc(NIMAG*sizeof(t_defense));///allocation dynamique (faite aussi pour les ennemis)
    defense->cptimg=0;
    defense->tmpimg=6;
    defense-> imgcourante=rand()%NIMAG;
    defense->presence=0;
    defense->tx=23;
    defense->ty=56;
    defense->vie=1;
    defense->y=0;
    defense->x=0;
    return defense;
}
/**************************************************************************/

/*
t_money*creerM()///création de toutes les défenses
{
    t_money*money;
    money=(t_money*)malloc(NIMAG*sizeof(t_money));///allocation dynamique (faite aussi pour les ennemis)
    money->cptimg=0;
    money->tmpimg=6;
    money-> imgcourante=rand()%NIMG;
    money->presence=0;
    money->tx=23;
    money->ty=56;
    money->vie=1;
    money->y=0;
    money->x=0;
    money->timer=0;
    return money;
}
*/
/**************************************************************************/


void remplirTabActeurD(t_defense*tab[NACTEURD])///création de toutes les défenses
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        tab[i]=creerD();
    }
    for(i=0; i<NACTEURD; i++)
    {
        tab[i]->creer=0;
    }
}

/**************************************************************************/
/*
void remplirTabMoney(t_money*tabA[NACTEUR])///création de toutes les défenses
{
    int i;
    for(i=0; i<NACTEUR; i++)
    {
        tabA[i]=creerM();
    }
    for(i=0; i<NACTEUR; i++)
    {
        tabA[i]->creer=0;
    }
}
*/
/**************************************************************************/

void actualiser_defense(t_defense*defense)///actualisation d'une défense
{
    if((defense->vie)==1) ///tant que elle existe alors on incrémente les images de l'animation
    {
        defense->cptimg++;

        if(defense->cptimg>=defense->tmpimg)///pour l'animation
        {
            defense->cptimg=0;
            defense->imgcourante++;
            if(defense->imgcourante>=NIMAG)
                defense->imgcourante=0;
        }
    }
}

/**************************************************************************/
/*
void actualiser_money(t_money*money)///actualisation d'une défense
{
    if((money->vie)==1) ///tant que elle existe alors on incrémente les images de l'animation
    {
        money->cptimg++;

        if(money->cptimg>=money->tmpimg)///pour l'animation
        {
            money->cptimg=0;
            money->imgcourante++;
            if(money->imgcourante>=NIMG)
                money->imgcourante=0;
        }
    }
}
*/
/**************************************************************************/

void actualiserTabDefense(t_defense*tab[NACTEURD])///actualisation pour l'ensemble des défenses
{
    for (int i=0; i<NACTEURD; i++)
    {
        actualiser_defense(tab[i]);
    }
}

/**************************************************************************/
/*
void actualiserTabMoney(t_money*tabA[NACTEUR])///actualisation pour l'ensemble des défenses
{
    for (int i=0; i<NACTEUR; i++)
    {
        actualiser_money(tabA[i]);
    }
}
*/
/**************************************************************************/

void dessinerDefense(BITMAP*bmp,t_defense*defense,BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG])///dessin d'une défense

{
    if(defense->creer==1&&defense->vie==1)/// tant quelle existe et quelle est crée
    {
        if(defense->type == 0)///hamburger
        {
            if(defense->y>300)
            {
                masked_blit(animationd[defense->imgcourante],bmp,0,0,defense->x,defense->y,animationd[defense->imgcourante]->w,animationd[defense->imgcourante]->h);
            }
        }
        if(defense->type == 1)///hotdog

        {
            if(defense->y>300)
            {
                masked_blit(animation2d[defense->imgcourante],bmp,0,0,defense->x,defense->y,animation2d[defense->imgcourante]->w,animation2d[defense->imgcourante]->h);
            }
        }
        if(defense->type == 2)///pizza
        {
            if(defense->y>300)
            {
                masked_blit(animation3d[defense->imgcourante],bmp,0,0,defense->x,defense->y,animation3d[defense->imgcourante]->w,animation3d[defense->imgcourante]->h);
            }
        }
    }
}

/**************************************************************************/
/*
void dessinerMoney(BITMAP*bmp,t_money*money,BITMAP*money_bmp[NIMG])///dessin d'une défense
{
    if(money->creer==1&&money->vie==1)/// tant quelle existe et quelle est crée
    {
        if(money->timer <= 10000)///hamburger
        {
            if(money->y>300)
            {
                masked_blit(money_bmp[money->imgcourante],bmp,0,0,money->x,money->y,money_bmp[money->imgcourante]->w,money_bmp[money->imgcourante]->h);
            }
        }
    }
}
*/
/*
void dessinerTabMoney(BITMAP*bmp,t_money*tabA[NACTEUR],BITMAP*money_bmp[NIMG])
{
    int i ;
    for (i=0; i<NACTEUR; i++)
        dessinerMoney(bmp,tabA[i],money_bmp);
}
*/
/**************************************************************************/

void dessinerTabDefense(BITMAP*bmp,t_defense*tab[NACTEURD],BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG])///dessiner l'ensemble des defenses
{
    int i;
    for (i=0; i<NACTEURD; i++)
        dessinerDefense(bmp,tab[i],animationd,animation2d,animation3d);
}

int valAbs(int val)///fonction pour la valeur absolu=> afin que la defense soit posée forcement sur une ligne où les ennemis sont présences
{
    if(val<0)
        return -val; ///ligne inférieur
    else
        return val; ///ligne superieur
}

int DefPos(int py) ///la position en y de la défense est donc determiner par :
{
    int diff=1000; ///un ecran d'environ 1000 pixels
    int Line=0;
    int i=0;
    int courentDiff=0;
    for(i=0; i<5; i++) ///5 lignes possibles
    {
        courentDiff=valAbs(py-ligneDef[i]);///la position de la defense en fonction de la fonction absolue
        if(courentDiff<diff) ///tant que ca rentre dans l'ecran
        {
            diff=courentDiff;
            Line=i; ///la ligne sur laquel on se trouve est donc retourné
        }
    }
    return Line;
}

void creer_perso(t_defense *mesDefenses[NACTEURD],int x,int y, int type,BITMAP* *tab)///creation de la défense
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        if(mesDefenses[i]->creer==0) ///si elle n'existe pas encore on la crée
        {
            {
                mesDefenses[i]->x = (mouse_x-tab[2]->w/2);
                mesDefenses[i]->y =ligneDef[DefPos(y)]; ///en fonction des lignes où elle peut se placer
                mesDefenses[i]->type = type;
                mesDefenses[i]->creer = 1;
                mesDefenses[i]->presence = 1;
                i=NACTEURD;
            }
        }
    }
}

/**************************************************************************/
/*
void creer_money(t_money *money[NACTEUR],int x,int y, int timer,BITMAP* *tab)///creation de la défense
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        if(money[i]->creer==0) ///si elle n'existe pas encore on la crée
        {
            {
                money[i]->x = (mouse_x-tab[2]->w/2);
                money[i]->y =ligneDef[DefPos(y)]; ///en fonction des lignes où elle peut se placer
                money[i]->timer = timer;
                money[i]->creer = 1;
                money[i]->presence = 1;
                money[i]->vie = 1;
                i=NACTEUR;
            }
        }
    }
}
*/
/**************************************************************************/
