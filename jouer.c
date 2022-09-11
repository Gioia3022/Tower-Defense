#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include "niveau.h"
#include "Global.h"


///sousfonction spécifique à l'écriture et l'affichage
void texte(BITMAP* page, BITMAP* nv1,BITMAP*nv2, BITMAP*nv3)
{
    ///nom des niveaux
    textout_ex(page,font,"Niveau 1",275,350,makecol(255,255,255),-1);
    textout_ex(page,font,"Niveau 2",725,350,makecol(255,255,255),-1);
    textout_ex(page,font,"Niveau 3",1190,350,makecol(255,255,255),-1);
    blit(nv1,page,0,0, 50,371,450,318);
    blit(nv2,page,0,0,525, 371,450,318);
    blit(nv3,page,0,0,1000, 371,450,318);
}

///appel de la fonction de jeu
void joueur( BITMAP* fond2, BITMAP*fond, BITMAP* page,BITMAP*niveau1, BITMAP*niveau2, BITMAP*niveau3, BITMAP* explosion, BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent,BITMAP* gagne, BITMAP* perdu)
{
    BITMAP*nv1; ///fond d'ecran des troix niveaux
    BITMAP*nv2;
    BITMAP*nv3;

    int livello=1; ///3 niveaux à difficulté croissante determiné par le switch
    int ritorno=0; ///retour au menu
    int rientra=1; /// pour enchainer les autres niveaux



    ///boucle de niveau/ jeu
    while((!key[KEY_ESC])&&(ritorno==0))
    {
        if(rientra==1)
        {
            switch(livello)
            {
            case 1:
                blit(fond2,page,0,0,0,0,SCREEN_W,SCREEN_H);

                monnaie = monnaieDebut;
                monnaieDebut=0;
                monnaietot=300; ///Prix

                nv1=load_bitmap("mignon_1.bmp",NULL); ///images en format reduit pour des questions d'esthethique
                nv2=load_bitmap("block_2.bmp",NULL);
                nv3=load_bitmap("block_3.bmp",NULL);

                texte(page, nv1,nv2, nv3);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                rientra=0;
                break;

            case 2:
                blit(fond2,page,0,0,0,0,SCREEN_W,SCREEN_H);

                monnaie = monnaieDebut;
                monnaieDebut=0;
                monnaietot=300; ///Prix

                nv1=load_bitmap("mignon_1.bmp",NULL);
                nv2=load_bitmap("mignon_2.bmp",NULL);
                nv3=load_bitmap("block_3.bmp",NULL);

                texte(page, nv1,nv2, nv3);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                rientra=0;
                break;

            case 3:
                blit(fond2,page,0,0,0,0,SCREEN_W,SCREEN_H);

                monnaie = monnaieDebut;
                monnaieDebut=0;
                monnaietot=300; ///Prix

                nv1=load_bitmap("mignon_1.bmp",NULL);
                nv2=load_bitmap("mignon_2.bmp",NULL);
                nv3=load_bitmap("mignon_3.bmp",NULL);

                texte(page, nv1,nv2, nv3);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                rientra=0;
                break;

            case 4:
                blit(gagne, page,0,0,0,0,SCREEN_W, SCREEN_H); ///affichage de l'ecran après avoir fini le 3e niveauù
                blit(page, screen,0,0,0,0,SCREEN_W, SCREEN_H);
                break;
            case 5:
                blit(perdu, page,0,0,0,0,SCREEN_W, SCREEN_H); ///affichage de l'ecran quand les ennemis ont envahi le royaume des frites
                blit(page, screen,0,0,0,0,SCREEN_W, SCREEN_H);
                break;
            }

        }

        if(mouse_b&1)
        {
            ///on peut jouer au premier niveau à n'importe quel moment tant qu'on clique sur la zone spécifique
            if((livello==1 || livello==2 || livello==3)&&((mouse_x>50 && mouse_x<500)&&(mouse_y>317 && mouse_y<689)))
            {
                niveau_1(&livello,page, niveau1,explosion, ketchup_bmp, frite_bmp, barre_jeu, argent, &rientra);
                rest(90);
            }

            ///on peut jouer au niveau 2 seulement si on le débloque
            if((livello==2 || livello==3)&& ((mouse_x>525 && mouse_x<975)&&(mouse_y>317 && mouse_y<689)))
            {
                niveau_2(&livello, page, niveau2, explosion,ketchup_bmp,frite_bmp,barre_jeu,argent, &rientra);
            }

            ///on peut jouer au niveau 3 seulement si on le débloque(en finissant le niveau 1)
            if((livello==3)&&((mouse_x>1000 && mouse_x<1450)&&(mouse_y>317 && mouse_y<689)))
            {
                niveau_3(&livello, page, niveau3, explosion,ketchup_bmp, frite_bmp,barre_jeu, argent, &rientra);
            }

            if(rientra==1)
            {
                mouse_x=0;
                mouse_y=0;
                livello++; ///enchainement du niveau après mort de tous les ennemis
            }

            if(gameOver==1) ///fin de partie après avoir perdu
            {
                livello=5;
            }

            if(livello==4) ///fin de partie après avoir gagne
            {
                blit(gagne, screen,0,0,0,0,SCREEN_W, SCREEN_H);
                printf("VICTOIRE");
            }
            if(livello==5)
            {
                blit(gagne, screen,0,0,0,0,SCREEN_W, SCREEN_H);
                printf("PERDU");
            }


            ///revenir au menu
            if ((mouse_x>1315 && mouse_x<1445) && (mouse_y>980 &&mouse_y<1025))
            {
                mouse_x=0;
                mouse_y=0;
                ritorno=1;

            }
        }


    }

}






