#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "Global.h"

///affichage des acteurs


void acteurs(BITMAP*fond2, BITMAP* page, BITMAP*maissa,BITMAP*coumba,BITMAP*gioia)
{
    int ritorno=0;
    blit(fond2,page,0,0,0,0,SCREEN_W,SCREEN_H);

    blit(coumba, page,0,0,50,218, SCREEN_W, SCREEN_H);
    textout_ex(page,font,"Coumba Gaye", 200, 800, makecol(255,255,255),-1);
    blit(gioia, page,0,0,525,218, SCREEN_W, SCREEN_H);
    textout_ex(page,font,"Gioia Galiazzo", 650, 800, makecol(255,255,255),-1);
    blit(maissa, page,0,0,1000,218, SCREEN_W, SCREEN_H);
    textout_ex(page,font,"Maissa Ait-chabane", 1100, 800, makecol(255,255,255),-1);
    blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    while(!key[KEY_ESC] && ritorno==0 )
    {
        if(mouse_b&1)
        {
            if ((mouse_x>1315 && mouse_x<1445) && (mouse_y>980 &&mouse_y<1025))
            {
                mouse_x=0;
                mouse_y=0;
                ritorno=1;

            }
        }
    }
}
