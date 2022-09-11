#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include "attaque.h"
#include "collisions.h"
#include "Global.h"


///prototypes des sous programes de défense
void def(BITMAP* page, int *finished,BITMAP*tab[NIMG],t_defense* mesDefenses[NACTEURD],BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG]);
void defense(BITMAP*page, BITMAP* explosion,BITMAP* tabImgDef[NIMG],t_defense* mesDefenses[NACTEURD], BITMAP* ketchup_bmp,t_ketchup* ketchup[NACTEURD], BITMAP* frite_bmp, t_frites* frite[NACTEURD], BITMAP* barre_jeu, BITMAP*argent, BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG]);


void niveau_1(int *livello, BITMAP* page, BITMAP*niveau1, BITMAP* explosion, BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent,int *rientra)
{
    srand(time(NULL));
    ///tableau des animations des tomates
    BITMAP* animation[NIMG];
    ///tableau des animations des defenses
    BITMAP*animationd[NIMAG];///hamburgers
    BITMAP*animation2d[NIMAG];///hotdogs
    BITMAP*animation3d[NIMAG];///pizzas
    BITMAP*tab[NIMG]; ///tableau de l'ensemble des défenses
   // BITMAP*money_bmp[NIMG];///argent


    int finished=0;
    int check=0;


    t_ennemi* mesEnnemis[NACTEUR]; ///structure des tomates
    t_frites* frite[NACTEURD]; ///structure des frites
    t_ketchup* ketchup[NACTEURD];///structure du ketchup
    t_defense* mesDefenses[NACTEURD];///structure des defenses
    // t_money* tabA[NACTEUR];


    chargerAnimation(animation); ///appel à la sous fonction d'animation des tomates
    // chargerMoney(money_bmp); ///appel à la sous fonction d'animation des argent
    chargerTousDefenses(animationd,animation2d,animation3d,tab); ///appel à la sous fonction d'animation des defenses

    remplirTabActeur(mesEnnemis);///creation des tomates
    remplirTabActeurD(mesDefenses);///creation des défenses
    remplirTabFrite(frite);///creation des frites
    remplirTabKetchup(ketchup);///creation du ketchup
    //remplirTabMoney(tabA);///creation du -------


    def(page,&finished,tab,mesDefenses,animationd,animation2d, animation3d);///charger et remplir le tableau de toutes les defenses

    int test=0;

    ///boucle du niveau 1
    while((finished==0)&&(!key[KEY_ESC]))
    {
        clear_bitmap(page);
        blit(niveau1,page,0,0,0,0,SCREEN_W, SCREEN_H);///decor du premier niveau
        defense(page, explosion,tab,mesDefenses, ketchup_bmp, ketchup,frite_bmp,frite, barre_jeu, argent,animationd,animation2d, animation3d);///gestion de l'argent et des dépenses et de la création des personages

        TomatesToFrite(mesEnnemis,frite, page);///collision tomates frites

        actualiserTabEnnemi(mesEnnemis,page);///actualisation des tomates
        dessinerTabEnnemi(page,mesEnnemis, animation);///affichage des sprite
        actualiserTabFrites(frite,mesDefenses);///actualisation des frites
        actualiserTabKetchup(ketchup,mesDefenses);///actualisation du ketchup


        TabDefenseToTomate(mesEnnemis,mesDefenses, explosion,page);///collision tomates défenses

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
