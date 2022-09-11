#include "collisions.h"
#include "def_tot.h"
#include "Global.h"

t_frites*creerFrites()///creation d'une frite
{
    t_frites* frite;
    frite=(t_frites*)malloc(sizeof(t_frites)*1);
    frite->dx=4;
    frite->tx=30;
    frite->ty=8;
    frite->nbr=0;
    frite->vie=0;
    return frite;
}

void remplirTabFrite(t_frites* frite[NACTEURD])/// creation de toutes les frites
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        frite[i]=creerFrites();
    }
}



void actualiserFrites(t_frites*  frite,t_defense* defense)///actualisation
{
    if(frite->nbr==0) ///si condition validé alors frite à la meme position que la défense
    {
        frite->x=defense->x;
        frite->y=defense->y;

    }

    if(frite->nbr==1) ///si condition validé alors frite avance
    {
        frite->x+=frite->dx;
        if(frite->x>=SCREEN_W)
        {
            frite->vie=0;
            frite->nbr=0;

        }
    }
    if(mouse_b&1)
    {
        if((mouse_x>=defense->x&&mouse_x<(defense->x+250))&&(mouse_y>=defense->y&&mouse_y<defense->y+100)) ///si on clique sur l'hamburger et la condition frite->nbr==0 est validé alors la frite existe
        {
            if(frite->nbr==0)
            {
                frite->nbr=1;
                frite->vie=1;
            }
        }
    }
}




void actualiserTabFrites(t_frites* frite[NACTEURD],t_defense* defense[NACTEURD])///on actualise toutes les frites
{
    int i;
    for (i=0; i<NACTEURD; i++)
    {
        actualiserFrites(frite[i],defense[i]);
    }
}


void dessinerFrites(BITMAP*page,BITMAP*frite_bmp,t_frites*frites,t_defense*defense)///on dessine une frite
{
    if((defense->type==0)&&frites->vie==1)
    {
        draw_sprite(page,frite_bmp,frites->x,frites->y);
    }
}



void dessinerTabFrites(BITMAP*page,BITMAP*frite_bmp,t_frites*frites[NACTEURD],t_defense*defense[NACTEURD])///on les dessines toutes
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        dessinerFrites(page,frite_bmp,frites[i],defense[i]);
    }
}



t_ketchup*creerKetchup() ///création du ketchup (pour une defense)
{
    t_ketchup* ketchup;
    ketchup=((t_ketchup*)malloc(sizeof(t_ketchup)*1));
    ketchup->tx=193;
    ketchup->ty=180;
    return ketchup;
}
void remplirTabKetchup(t_ketchup*tab[NACTEURD])/// pour tout les ketchups
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        tab[i]=creerKetchup();
    }
}


void actualiserKetchup(t_ketchup*ketchup,t_defense*defense)///le ketchup est actualisé un peu éloigné de l'hotdog
{
    ketchup->x=defense->x+50;
    ketchup->y=defense->y-50;
}

void actualiserTabKetchup(t_ketchup* tab[NACTEURD],t_defense*tab2[NACTEURD])///on le fait pour tous
{
    int i;
    for (i=0; i<NACTEURD; i++)
    {
        actualiserKetchup(tab[i],tab2[i]);
    }
}

void dessinerKetchup(BITMAP*page,BITMAP*ketchup_bmp,t_ketchup*ketchup,t_defense*defense)///on dessine le ketchup pour les hotdogs seulement
{
    if((defense->type==1))
        draw_sprite(page,ketchup_bmp,ketchup->x,ketchup->y);
}


void dessinerTabKetchup(BITMAP*page,BITMAP*ketchup_bmp,t_ketchup*ketchup[NACTEURD],t_defense*defense[NACTEURD])///on le fait pour tous
{
    int i;
    for(i=0; i<NACTEURD; i++)
    {
        dessinerKetchup(page,ketchup_bmp,ketchup[i],defense[i]);
    }
}
