#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "Global.h"


///reglement du jeu
void regles(BITMAP* fond2, BITMAP* page, BITMAP* regle, BITMAP* histoire)
{
    int ritorno=0;
    //int retour=0;
    blit(fond2,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(regle,page,0,0,250,135,SCREEN_W, SCREEN_H);
    blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    while(!key[KEY_ESC] && ritorno==0 )
    {
        ///histoire du jeu
        if(mouse_b&1)
        {
            if((mouse_x>645&& mouse_x<825)&&(mouse_y>875&&mouse_y<900))
            {
                clear_bitmap(page);
                blit(histoire,page,0,0,0,0,SCREEN_W,SCREEN_H);
                blit(page, screen,0,0,0,0,SCREEN_W,SCREEN_H);
                while(!key[KEY_ESC]&& ritorno==0)
                {
                    ///revenir au menu principal à partire de la page de l'histoire
                    if(mouse_b&1)
                    {
                        if((mouse_x>230&&mouse_x<460)&&(mouse_y>905&&mouse_y<985))
                        {
                            mouse_x=0;
                            mouse_y=0;
                            ritorno=1;
                        }
                    }

                }
            }

            if ((mouse_x>1315 && mouse_x<1445) && (mouse_y>980 &&mouse_y<1025))
            {
                ///retourner au menu principale
                mouse_x=0;
                mouse_y=0;
                ritorno=1;

            }
        }


    }
}
