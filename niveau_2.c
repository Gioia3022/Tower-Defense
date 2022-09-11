#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include "attaque.h"
#include "collisions.h"
#include "Global.h"


///prototypes des sous programes de défense
void def(BITMAP* page, int *finished,BITMAP*tab[NIMG],t_defense* mesDefenses[NACTEURD],BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG]);
void defense(BITMAP*page, BITMAP* explosion,BITMAP*tab[NIMG],t_defense* mesDefenses[NACTEURD], BITMAP* ketchup_bmp, t_ketchup* ketchup[NACTEURD], BITMAP* frite_bmp, t_frites* frite[NACTEURD], BITMAP* barre_jeu, BITMAP*argent,BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG]);


void niveau_2(int *livello, BITMAP* page, BITMAP* niveau2, BITMAP* explosion, BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent,int* rientra )
{
    srand(time(NULL));
    ///tableau des animations des tomates et des broccolis
    BITMAP* animation[NIMG];
    BITMAP* animation2[NIMG];
    ///tableau des animations des defenses (les memes que pour le niveau 1)
    BITMAP*animationd[NIMAG];
    BITMAP*animation2d[NIMAG];
    BITMAP*animation3d[NIMAG];
    BITMAP*tab[NIMG];

    int finished=0;
    int check=0;

    t_ennemi *mesEnnemis[NACTEUR];///structure des tomates
    t_ennemi2* mesEnnemis2[NACTEUR];///structure des broccolis
    t_defense* mesDefenses[NACTEURD];///structure des defenses
    t_frites* frite[NACTEURD]; ///structure des frites
    t_ketchup* ketchup[NACTEURD];///structure du ketchup

    chargerToutesAnimation_2(animation,animation2);///appel à la sous fonction d'animation des tomates et des brocolis
    chargerTousDefenses(animationd,animation2d,animation3d,tab);///appel à la sous fonction d'animation des tomates

    remplirToustab_2(mesEnnemis,mesEnnemis2);///creation des tomates et des broccolis
    remplirTabActeurD(mesDefenses);///creation des defenses
    remplirTabFrite(frite);///creation des frites
    remplirTabKetchup(ketchup);///creation du ketchup

    def(page,&finished,tab,mesDefenses,animationd,animation2d, animation3d);///charger et remplir le tableau de toutes les defenses

    int test=0;

    ///boucle du niveau 2
    while((finished==0)&&(!key[KEY_ESC]))
    {
        clear_bitmap(page);
        blit(niveau2,page,0,0,0,0,SCREEN_W, SCREEN_H);///decor du deuxième niveau
        defense(page, explosion,tab,mesDefenses, ketchup_bmp, ketchup,frite_bmp,frite, barre_jeu, argent,animationd,animation2d, animation3d);///gestion de l'argent et des dépenses et de la création des personages
        TomatesToFrite(mesEnnemis,frite, page);///collision tomates frites
        BrocolisToFrite(mesEnnemis2, frite, page);/// collision broccolis frites

        actualiserToutTabEnnemi2(mesEnnemis,mesEnnemis2, page);///actualisation des tomates et broccolis
        dessinerToutTabEnnemi2(page,mesEnnemis,animation,mesEnnemis2,animation2);///affichage des sprite
        actualiserTabFrites(frite,mesDefenses);///actualisation des frites
        actualiserTabKetchup(ketchup,mesDefenses);///actualisation du ketchup

        TabDefenseToTomate(mesEnnemis,mesDefenses, explosion,page);///collision tomates défenses
        TabDefenseToBroccolis(mesEnnemis2, mesDefenses,explosion,page);///collision broccolis défenses
        blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        *rientra=0;
        int ferma =0;
        if(gameOver==1) ///test de Game Over
        {
            *rientra=1;
            finished=1;
        }
        else
        {
            for(check=0; check<NACTEUR; check++)
            {
                if(mesEnnemis[check]->vie==2)
                {
                    test++;
                    if(test==10)
                    {
                        *rientra=1;
                        finished=1;
                    }
                }
            }
        }
        test=0;
    }
}
