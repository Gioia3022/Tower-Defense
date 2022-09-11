#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "attaque.h"
#include "def_tot.h"
#include "collisions.h"
#include "Global.h"


int selection=0;
int i=0;
int x=0;
int y=0;

void def(BITMAP* page, int *finished,BITMAP* tab[NIMG],t_defense* mesDefenses[NACTEURD], BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG])
{
    ///appel aux defenses et creation du tableau de structures
    chargerTousDefenses(animationd,animation2d,animation3d,tab);
    remplirTabActeurD(mesDefenses);
}

void defense(BITMAP*page, BITMAP* explosion,BITMAP* tabImgDef[NIMG],t_defense* mesDefenses[NACTEURD], BITMAP* ketchup_bmp,t_ketchup* ketchup[NACTEURD], BITMAP* frite_bmp, t_frites* frite[NACTEURD], BITMAP* barre_jeu, BITMAP*argent, BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG])
{
    ///creation du menu et de l'argent
    draw_sprite(page,barre_jeu,x,y);
    draw_sprite(page,argent,300,10);

    actualiserTabDefense(mesDefenses); ///actualisation de l'ensemble des tableaux de structure des defenses

    if(mouse_b&1)///choix du type de défenses à placer ///click
    {
        if((mouse_x>26)&&(mouse_x<84)&&(mouse_y>8)&&(mouse_y<83))///hamburgers
        {
            if(monnaie>=50)///verification d'avoir assez d'argent
            {
                i=0;
                selection=1;
                mouse_b=0;
            }
            else
                textout_ex(page,font,"t'es trop pauvre !",20,100,makecol(0,0,0),-1);
        }
        if((mouse_x>105)&&(mouse_x<159)&&(mouse_y>3)&&(mouse_y<80))///hotdogs
        {
            if(monnaie>=20)
            {
                i=1;
                selection=1;
                mouse_b=0;
            }
            else
                textout_ex(page,font,"t'es trop pauvre !",20,100,makecol(0,0,0),-1);
        }
        if((mouse_x>176)&&(mouse_x<266)&&(mouse_y>4)&&(mouse_y<81))///pizzas
        {
            if(monnaie>=15)
            {
                i=2;
                selection=1;
                mouse_b=0;
            }
            else
                textout_ex(page,font,"t'es trop pauvre !",20,100,makecol(0,0,0),-1);
        }
            /**************************************************************************/
        ///on avait esseyer de faire le click and drop avec l'argent mais nous avons du abbandoner l'idée
         /*if((mouse_x>300)&&(mouse_x<467)&&(mouse_y>0)&&(mouse_y<62)) /// argent/ production
           {
               if(monnaie>=10)
                 {
                     i=3;
                     selection=1;
                     mouse_b=0;
                }
           }*/
            /**************************************************************************/
    }

    if((selection==1)&&(mouse_b==0)&&(monnaie>=0))///drag
    {
        if(i==0)///si t'as assez d'argent et tu a choisi l'hamburger alors on l'affiche aux positions requises
        {
            draw_sprite(page,tabImgDef[0],(mouse_x-tabImgDef[0]->w/2),(mouse_y-tabImgDef[0]->h/2));
        }

        if(i==1)///si t'as assez d'argent et tu a choisi l'hotdog alors on l'affiche aux positions requises
        {
            draw_sprite(page,tabImgDef[1],(mouse_x-tabImgDef[1]->w/2),(mouse_y-tabImgDef[1]->h/2));
        }

        if(i==2)///si t'as assez d'argent et tu a choisi la pizzas alors on l'affiche aux positions requises
        {
            draw_sprite(page,tabImgDef[2],(mouse_x-tabImgDef[2]->w/2),(mouse_y-tabImgDef[2]->h/2));
        }

    }


    if((selection==1)&&(mouse_b==1)&&(monnaie>=0))///and drop
    {
        selection=0;
        mouse_b=0;
        if(mouse_y>=450)///tu peux pas posser en haut de l'ecran et que sur moitié de l'ecran en largeur
        {
            creer_perso(mesDefenses,mouse_x,mouse_y,i,tabImgDef);///appel de la fonction création
            if(i==0)
                monnaie-=50;///deduction de 50$ pour l'hamburger
                monnaieDebut=monnaie+monnaietot;

            if(i==1)
                monnaie-=20;///deduction de 20$ pour l'hotdog
                monnaieDebut=monnaie+monnaietot;
            if(i==2)
                monnaie-=15;///deduction de 15$ pour la pizza
                monnaieDebut=monnaie+monnaietot;

            /**************************************************************************/
          /* if(i==3)
           {
                monnaie-=10;
                monnaieDebut=monnaie+monnaietot;
           }*/

           /*
            draw_sprite(page,money[*imgcourante],(mouse_x-tabA[0]->w/2),(mouse_y-tabA[0]->h/2));

           else
            creer_perso(mesDefenses,mouse_x,mouse_y,i,tabImgDef);*/

            /**************************************************************************/
        }
    }

    dessinerTabDefense(page,mesDefenses,animationd,animation2d,animation3d);///appel le fonctions: dessiner l'annimation des défenses
    dessinerTabKetchup(page,ketchup_bmp,ketchup,mesDefenses);///appel la fonction de dessin pour le ketchup
    dessinerTabFrites(page,frite_bmp,frite,mesDefenses);///appel la fonction de dessin pour les frites

    if(monnaie<=0)  /// si vous n'avez plus d'argent alors:
        textout_ex(page,font,"t'es trop pauvre !",20,100,makecol(0,0,0),-1);

    else  ///sinon on vous informe sur votre situation économique:
        textprintf_ex(page, font, 440, 25, makecol(0, 0, 0),-1, "vous reste %d ", monnaie);
        textprintf_ex(page, font, 440, 40, makecol(0, 0, 0),-1, "      Prix %d ", monnaietot);

}
