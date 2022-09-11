#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "niveau.h"
#include "Global.h"

///appel de la fonction du menu

void ecran_1(BITMAP* fond, BITMAP* fond2, BITMAP* page, BITMAP*regle, BITMAP* histoire, BITMAP* explosion, BITMAP* niveau1, BITMAP*niveau2, BITMAP*niveau3,BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent,BITMAP*maissa,BITMAP*coumba,BITMAP*gioia,BITMAP* gagne, BITMAP* perdu);



int main()
{
    /// initialisation d'allegro, création des variables et test de présence
    allegro_init();
    install_keyboard();
    install_mouse();
    BITMAP* fond;
    BITMAP* fond2;
    BITMAP*maissa;
    BITMAP*coumba;
    BITMAP*gioia;
    BITMAP* page;
    BITMAP* regle;
    BITMAP* histoire;
    BITMAP* niveau1;
    BITMAP* niveau2;
    BITMAP* niveau3;
    BITMAP* ketchup_bmp;
    BITMAP* frite_bmp;
    BITMAP* explosion;
    BITMAP* barre_jeu;
    BITMAP* argent;
    BITMAP* gagne;
    BITMAP* perdu;


    monnaieDebut=300; /// Rest Liveau
    monnaietot=300; ///Prix
    monnaie=300;
    gameOver=0;

    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1500,1060,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    page=create_bitmap(SCREEN_W,SCREEN_H);

    clear_bitmap(page);

    fond=load_bitmap("fondmenu.bmp",NULL);
    if(!fond)
    {
        allegro_message("probleme");
        exit(EXIT_FAILURE);
    }

    fond2=load_bitmap("fond2.bmp",NULL);

    gioia=load_bitmap("gioia.bmp",NULL);

    maissa=load_bitmap("maissa.bmp", NULL);

    coumba=load_bitmap("coumba.bmp", NULL);

    if(!gioia)
    {
        allegro_message("Pas pu trouver gioia");
        exit(EXIT_FAILURE);
    }
    if(!maissa)
    {
        allegro_message("Pas pu trouver maissa");
        exit(EXIT_FAILURE);
    }
    if(!coumba)
    {
        allegro_message("Pas pu trouver coumba");
        exit(EXIT_FAILURE);
    }

    regle=load_bitmap("regles.bmp", NULL);

    histoire=load_bitmap("histoire.bmp", NULL);

    niveau1=load_bitmap("niveau_1.bmp",NULL);

    niveau2=load_bitmap("niveau_2.bmp",NULL);

    niveau3=load_bitmap("niveau_3.bmp",NULL);

    if(!niveau1)
    {
        allegro_message("Pas pu trouver decor");
        exit(EXIT_FAILURE);
    }
    if(!niveau2)
    {
        allegro_message("Pas pu trouver decor");
        exit(EXIT_FAILURE);
    }

    if(!niveau3)
    {
        allegro_message("Pas pu trouver decor");
        exit(EXIT_FAILURE);
    }

    argent=load_bitmap("argent.bmp",NULL);

    ketchup_bmp=load_bitmap("ketchup.bmp",NULL);

    explosion=load_bitmap("explosion.bmp",NULL);

    if(!ketchup_bmp)

    {
        allegro_message("erreur ketchup");
        exit(EXIT_FAILURE);
    }

    frite_bmp=load_bitmap("frite.bmp",NULL);

    if(!frite_bmp)

    {
        allegro_message("erreur frite");
        exit(EXIT_FAILURE);
    }

    barre_jeu=load_bitmap("barre_jeu.bmp",NULL);

    if(!barre_jeu)

    {
        allegro_message("erreur barre de jeu");
        exit(EXIT_FAILURE);
    }

    gagne=load_bitmap("win.bmp", NULL);

    perdu=load_bitmap("game_over.bmp",NULL);


    ///appel de la fonction menu
    ecran_1(fond,  fond2, page, regle, histoire,explosion, niveau1, niveau2, niveau3, ketchup_bmp, frite_bmp, barre_jeu, argent,maissa, coumba, gioia, gagne, perdu);

    return 0;
}
END_OF_MAIN();

