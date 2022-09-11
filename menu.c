#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#define LargeurMenu 200
#include "attaque.h"
#include "Global.h"


///appel des fonctions
void joueur( BITMAP* fond2, BITMAP*fond, BITMAP* page,BITMAP*niveau1, BITMAP*niveau2, BITMAP*niveau3,BITMAP* explosion, BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent, BITMAP* gagne, BITMAP* perdu);
void affichage(BITMAP* page, BITMAP* fond);
void acteurs(BITMAP* fond2,  BITMAP* page, BITMAP*maissa,BITMAP*coumba,BITMAP*gioia);
void regles(BITMAP* fond2, BITMAP* page, BITMAP* regle, BITMAP*histoire);

void ecran_1( BITMAP *fond,  BITMAP *fond2, BITMAP *page, BITMAP*regle, BITMAP*histoire,BITMAP*explosion, BITMAP*niveau1, BITMAP*niveau2, BITMAP*niveau3, BITMAP* ketchup_bmp, BITMAP* frite_bmp, BITMAP* barre_jeu, BITMAP*argent,BITMAP*maissa,BITMAP*coumba,BITMAP*gioia, BITMAP* gagne, BITMAP* perdu)
{
    int ritorno=0;
    show_mouse(screen);



    ///creation de la boucle de jeu
    while((!key[KEY_ESC]) && (ritorno==0))
    {
        blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);

        ///clique gauche pour se deplacer dans le menu
        if(mouse_b&1)
        {
            if((mouse_x>=620&&mouse_x<=620 + LargeurMenu ) && (mouse_y>=245&&mouse_y<=305)) /// Attention nombres magiques. Définir une hauteur et largeur de bouton en constante : (mouse_x>620&&mouse_x<620 + LARGEUR)
            {
                ///acces aux niveaux
                joueur(fond2, fond, page, niveau1, niveau2, niveau3, explosion, ketchup_bmp, frite_bmp, barre_jeu, argent, gagne, perdu);
                affichage(page, fond);
            }

            if((mouse_x>620&&mouse_x<620 + LargeurMenu ) && (mouse_y>320&&mouse_y<380))
            {
                ///acces au score (diventerà gli attori)
                acteurs(fond2, page,maissa,coumba,gioia);
                affichage(page, fond);
            }

            if((mouse_x>620&&mouse_x<620 + LargeurMenu ) &&(mouse_y>395&&mouse_y<450))
            {
                ///acces aux régles et l'histoire du jeu
                regles(fond2, page, regle, histoire);
                affichage( page, fond);

            }

            if((mouse_x>620&&mouse_x<620+LargeurMenu ) && (mouse_y>465&&mouse_y<520))
            {
                ///sortie / quitter
                ritorno = 1;
            }

        }
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}

void affichage(BITMAP* page, BITMAP* fond)
{
    ///affichage du menu
    blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    mouse_x=0;
    mouse_y=0;
}
