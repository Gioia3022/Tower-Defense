#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "attaque.h"
#include "collisions.h"
#include "def_tot.h"
#include "Global.h"


///lignes sur lesquelles les ennemis vont apparaitre
int ligne[5]= {500,600,700,800,900};

///vagues des trois types d'ennemis
int vagues[5]= {1500,2300,3100,3900,4700};///tomate
int vagues2[5]= {2200,3000,3800, 4600, 5400};///broccolis
int vagues3[5]= {1800,2600,3000, 3800, 4600};///pommes de terre

///fonction pour les vitesses très faibles
float frand(float min, float max)
{
    return 0.001*(rand()%1000)*(max-min) + min;
}

/*****************************************************************************/
void chargerAnimation(BITMAP* animation[NIMG])///chargement des images pour les tomates
{
    int i;
    char nomfichier[256];
    for(i=0; i<NIMG; i++)
    {
        sprintf(nomfichier,"tomates/tomate%d.bmp",i);
        animation[i]=load_bitmap(nomfichier,NULL);

        if(!animation[i])
        {
            allegro_message("Pb de mode graphique") ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

}
void chargerAnimation2(BITMAP*animation2[NIMG])///pour les broccolis
{
    int i;
    char nomfichier[256];
    for(i=0; i<NIMG; i++)
    {
        sprintf(nomfichier,"broccolis/broccolis%d.bmp",i);
        animation2[i]=load_bitmap(nomfichier,NULL);
        if(!animation2[i])
        {
            allegro_message("Pb de mode graphique") ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

}
void chargerAnimation3(BITMAP*animation3[NIMG])///pour les pommes de terre
{
    int i;
    char nomfichier[256];
    for(i=0; i<NIMG; i++)
    {
        sprintf(nomfichier,"patates/patate%d.bmp",i);
        animation3[i]=load_bitmap(nomfichier,NULL);
        if(!animation3[i])
        {
            allegro_message("Pb de mode graphique") ;
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

}


void chargerToutesAnimation_2(BITMAP*animation[NIMG],BITMAP*animation2[NIMG])///fonction d'appel des autres: pour le niveau 2
{
    chargerAnimation(animation);
    chargerAnimation2(animation2);

}

void chargerToutesAnimation_3(BITMAP*animation[NIMG],BITMAP*animation2[NIMG],BITMAP*animation3[NIMG])///fonction d'appel des autres: pour le niveau 3
{
    chargerAnimation(animation);
    chargerAnimation2(animation2);
    chargerAnimation3(animation3);

}
/*****************************************************************************/
t_ennemi*creer()///creation d'une tomate
{
    t_ennemi*ennemi;
    ennemi=(t_ennemi*)malloc(NIMG*sizeof(t_ennemi));
    ennemi->tx=LARGEUR;
    ennemi->ty=HAUTEUR;
    ennemi->x=vagues[rand()%(4-0+1)+0];
    ennemi->y=ligne[rand()%(4-0+1)+0];
    ennemi->dx=2;
    ennemi->cptimg=0;
    ennemi->tmpimg=7;
    ennemi-> imgcourante=rand()%NIMG;
    ennemi->vie=1;
    return ennemi;
}
t_ennemi2*creer2()///creation d'un broccolis
{
    t_ennemi2*ennemi2;
    ennemi2=(t_ennemi2*)malloc(NIMG*sizeof(t_ennemi2));
    ennemi2->tx2=LARGEUR;
    ennemi2->ty2=HAUTEUR;
    ennemi2->x2=vagues2[rand()%(4-0+1)+0];
    ennemi2->y2=ligne[rand()%(4-0+1)+0];
    ennemi2->dx2=3;
    ennemi2->cptimg2=0;
    ennemi2->tmpimg2=7;
    ennemi2-> imgcourante2=rand()%NIMG;
    ennemi2->vie2=1;
    return ennemi2;
}
t_ennemi3*creer3()///creation d'une pomme de terre
{
    t_ennemi3* ennemi3;
    ennemi3=(t_ennemi3*)malloc(NIMG*sizeof(t_ennemi3));
    ennemi3->tx3=LARGEUR3;
    ennemi3->ty3=HAUTEUR;
    ennemi3->x3=vagues3[rand()%(4-0+1)+0];
    ennemi3->y3=ligne[rand()%(4-0+1)+0];
    ennemi3->dx3=2;
    ennemi3->cptimg3=0;
    ennemi3->tmpimg3=7;
    ennemi3-> imgcourante3=rand()%NIMG;
    ennemi3->vie3=1;
    return ennemi3;
}

/*****************************************************************************/
void remplirTabActeur(t_ennemi*tab[NACTEUR])///table de création des tomates
{
    int i;
    for(i=0; i<NACTEUR; i++)
    {
        tab[i]=creer();
    }
}

void remplirTabActeur2(t_ennemi2*tab2[NACTEUR])///table de création des broccolis
{
    int i;
    for(i=0; i<NACTEUR; i++)
    {
        tab2[i]=creer2();
    }
}
void remplirTabActeur3(t_ennemi3*tab3[NACTEUR])///table de création des pommes de terre
{
    int i;
    for(i=0; i<NACTEUR; i++)
    {
        tab3[i]=creer3();
    }
}

void remplirToustab_2(t_ennemi*mesEnnemis[NACTEUR],t_ennemi2*mesEnnemis2[NACTEUR]) ///appel des fonctions pour le niveau 2
{
    remplirTabActeur(mesEnnemis);
    remplirTabActeur2(mesEnnemis2);
}

void remplirToustab_3(t_ennemi*mesEnnemis[NACTEUR],t_ennemi2*mesEnnemis2[NACTEUR],t_ennemi3*mesEnnemis3[NACTEUR]) ///appel des fonctions pour le niveau 3
{
    remplirTabActeur(mesEnnemis);
    remplirTabActeur2(mesEnnemis2);
    remplirTabActeur3(mesEnnemis3);

}

/*****************************************************************************/
void actualiser_ennemi(t_ennemi*ennemi, BITMAP* page)
{
    int ralentissement=getpixel(page,ennemi->x+20,ennemi->y+20); ///pour le ketchup: recuperer la couleur

    if(ennemi->vie==1) ///si l'ennemi existe et il passe sur une zone ralentissement il est forcé à s'arreter
    {
        if(ralentissement==makecol(255,0,0)) ///la zone de ralentissement est rouge
        {
            ennemi->dx=frand(0.9,1.0);
        }
        else
        {
            ennemi->dx=2; ///sinon la vitesse est conserver
        }


        ennemi->x-=ennemi->dx; ///incrementation de la position

        if(ennemi->x<0) ///si il arrive à la fin de l'écran il reapparait de l'autre coté
        {
            ennemi->x = SCREEN_W;
        }
        ennemi->cptimg++; ///incrementation des immages -> sequence annimé
        if (ennemi->cptimg>=ennemi->tmpimg)
        {
            ennemi->cptimg=0;
            ennemi-> imgcourante++;
        }
        if(ennemi->imgcourante==NIMG)
            ennemi->imgcourante=0;
    }

}

void actualiser_ennemi2(t_ennemi2*ennemi, BITMAP* page)
///(exactement la meme chose que pour les tommates sauf que les brocolis sont plus puissants et moins aptes à rester bloque par le ketchup)
{
    int ralentissement=getpixel(page,ennemi->x2+20,ennemi->y2+20);
    if(ennemi->vie2==1)
    {
        if(ralentissement==makecol(255,0,0))
        {
            ennemi->dx2=frand(0.9,1.2);
        }
        else
        {
            ennemi->dx2=3;
        }
        if(ennemi->x2<0)
        {
            ennemi->x2 = SCREEN_W;
        }
        /*       if(ennemi->y2>470&&ennemi->y2<650&&ennemi->x2>0&& ennemi->x2<155)
               {
                   finished=1;
               }
        */
        ennemi->x2-=ennemi->dx2;
        ennemi->cptimg2++;
        if (ennemi->cptimg2>=ennemi->tmpimg2)
        {
            ennemi->cptimg2=0;
            ennemi-> imgcourante2++;
        }
        if(ennemi->imgcourante2==NIMG)
            ennemi->imgcourante2=0;
    }

}

void actualiser_ennemi3(t_ennemi3*ennemi,BITMAP*page) ///(exactement comme les tomates)
{
    int ralentissement=getpixel(page,ennemi->x3+20,ennemi->y3+20);
    if(ennemi->vie3==1)
    {
        if(ralentissement==makecol(255,0,0))
        {
            ennemi->dx3=frand(0.9,1.0);
        }
        else
        {
            ennemi->dx3=2;
        }
        if(ennemi->x3<0)
        {
            ennemi->x3 = SCREEN_W;
        }

        ennemi->x3-=ennemi->dx3;

        ennemi->cptimg3++;
        if (ennemi->cptimg3>=ennemi->tmpimg3)
        {
            ennemi->cptimg3=0;
            ennemi-> imgcourante3++;
        }

        if(ennemi->imgcourante3==NIMG)
            ennemi->imgcourante3=0;
    }

}

/*****************************************************************************/

void actualiserTabEnnemi(t_ennemi *tab[NACTEUR], BITMAP* page) ///actualisation pour toutes les tomates
{
    int i;
    for (i=0; i<NACTEUR; i++)
    {
        actualiser_ennemi(tab[i], page);
    }
}
void actualiserTabEnnemi2(t_ennemi2*tab[NACTEUR],BITMAP* page) ///actualisation pour tous les brocolis
{
    int i;
    for (i=0; i<NACTEUR; i++)
    {
        actualiser_ennemi2(tab[i], page);
    }
}
void actualiserTabEnnemi3(t_ennemi3*tab[NACTEUR],BITMAP* page) ///actualisation pour toutes les pommes de terre
{
    int i;
    for (i=0; i<NACTEUR; i++)
    {
        actualiser_ennemi3(tab[i],page);
    }
}

void actualiserToutTabEnnemi2(t_ennemi *tab[NACTEUR],t_ennemi2*tab2[NACTEUR],BITMAP* page) ///appel des fonctions pour le niveau 2
{
    actualiserTabEnnemi(tab, page);
    actualiserTabEnnemi2(tab2, page);
}
void actualiserToutTabEnnemi3(t_ennemi *tab[NACTEUR],t_ennemi2*tab2[NACTEUR],t_ennemi3*tab3[NACTEUR],BITMAP* page)///appel des fonctions pour le niveau 3
{
    actualiserTabEnnemi(tab, page);
    actualiserTabEnnemi2(tab2, page);
    actualiserTabEnnemi3(tab3, page);
}
/*****************************************************************************/
void dessinerEnnemi(BITMAP*bmp,t_ennemi*ennemi,BITMAP*animation[NIMG]) ///apparition des tomates une fois que le tableau d'animation est appele dans les differents niveau
{
    if(ennemi->vie==1)
        draw_sprite(bmp,animation[ennemi->imgcourante],ennemi->x,ennemi->y);
}
void dessinerEnnemi2(BITMAP*bmp,t_ennemi2*ennemi2,BITMAP*animation2[NIMG])///apparition des broccolis une fois que le tableau d'animation est appele dans les differents niveau
{
    if(ennemi2->vie2==1)
        draw_sprite(bmp,animation2[ennemi2->imgcourante2],ennemi2->x2,ennemi2->y2);
}
void dessinerEnnemi3(BITMAP*bmp,t_ennemi3*ennemi3,BITMAP*animation3[NIMG])///apparition des pommes de terre une fois que le tableau d'animation est appele dans les differents niveau
{
    if(ennemi3->vie3==1)
        draw_sprite(bmp,animation3[ennemi3->imgcourante3],ennemi3->x3,ennemi3->y3);
}

/*****************************************************************************/
void dessinerTabEnnemi(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG]) ///dessin fait pour toutes les tomates
{
    int i;

    for (i=0; i<NACTEUR; i++)
    {
        dessinerEnnemi(bmp,tab[i],animation);
    }

}
void dessinerTabEnnemi2(BITMAP*bmp,t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG])///dessin fait pour toutes les tomates
{
    int i;
    for (i=0; i<NACTEUR; i++)
        dessinerEnnemi2(bmp,tab2[i],animation2);

}
void dessinerTabEnnemi3(BITMAP*bmp,t_ennemi3*tab3[NACTEUR],BITMAP*animation3[NIMG])///dessin fait pour toutes les tomates
{
    int i;
    for (i=0; i<NACTEUR; i++)
        dessinerEnnemi3(bmp,tab3[i],animation3);

}

void dessinerToutTabEnnemi2(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG],t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG]) /// appel des fonctions pour le niveau 2
{
    dessinerTabEnnemi(bmp,tab,animation);
    dessinerTabEnnemi2(bmp,tab2,animation2);
}

void dessinerToutTabEnnemi3(BITMAP*bmp,t_ennemi*tab[NACTEUR],BITMAP*animation[NIMG],t_ennemi2*tab2[NACTEUR],BITMAP*animation2[NIMG],t_ennemi3*tab3[NACTEUR],BITMAP*animation3[NIMG])/// appel des fonctions pour le niveau 3
{
    dessinerTabEnnemi(bmp,tab,animation);
    dessinerTabEnnemi2(bmp,tab2,animation2);
    dessinerTabEnnemi3(bmp,tab3, animation3);
}

/*****************************************************************************/

void TomatesToFrite(t_ennemi* ennemi[NACTEUR], t_frites* frite[NACTEURD],BITMAP* page) ///collision tomates frites
{
    int IsCollision = 0;

    IsCollision = collisionFrite(ennemi,frite,page);///appel de la fonction qui fait la collision

}

int collisionFrite(t_ennemi*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page) ///fonction de collision / mort des tomates
{
    int enmPos,i;
    int ennemiDead=0; /// Si ennemiDead=0 alors la tomate n'est pas morte

    int DistanzaInLine = 5;

    for (i=0; i<NACTEURD; i++) ///on parcours la boucle de defense/ des frites dans ce cas
    {

        for(enmPos=0; enmPos<NACTEUR; enmPos++) ///on parcours la boucle des tomates
        {
            if(frite[i]->nbr==1) ///on pose une condition de validation
            {
                if((frite[i]->y==ennemi[enmPos]->y) &&(frite[i]->x-DistanzaInLine <= ennemi[enmPos]->x) && (frite[i]->x+DistanzaInLine >= ennemi[enmPos]->x))///zone de contact frite-tomate
                {

                    ennemiDead=1; ///tomate morte

                    ennemi[enmPos]->vie=2; /// arrete d'etre crée
                    ennemi[enmPos]->x=-1000;/// enlevé de l'ecran
                    frite[i]->nbr = 0; ///la condition n'est plus validé donc la frite reviens à la position de la défense
                    frite[i]->vie = 0;
                    frite[i]->x = -1000;
                    ennemi[enmPos]->y=-100; ///afin qu'ils ne soit plus present sur l'ecran
                    monnaietot += 20; ///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                }

            }
        }

    }
    return ennemiDead;
}


void BrocolisToFrite(t_ennemi2* ennemi2[NACTEUR], t_frites* frite[NACTEURD], BITMAP* page)///collision broccolis frites
{
    int IsCollision = 0;

    IsCollision = collisionFrite2(ennemi2,frite,page);///appel de la fonction qui fait la collision

}

int collisionFrite2(t_ennemi2*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page) ///fonction de collision / mort des broccolis
{
    int enmPos,i;
    int ennemiDead=0; /// Si ennemiDead=0 alors le broccolis n'est pas morte

    int DistanzaInLine = 5;

    for (i=0; i<NACTEURD; i++) ///on parcours la boucle de defense/ des frites dans ce cas
    {

        for(enmPos=0; enmPos<NACTEUR; enmPos++) ///on parcours la boucle des broccolis
        {
            if(frite[i]->nbr==1) ///on pose une condition de validation
            {
                if((frite[i]->y==ennemi[enmPos]->y2) &&(frite[i]->x-DistanzaInLine <= ennemi[enmPos]->x2) && (frite[i]->x+DistanzaInLine >= ennemi[enmPos]->x2))///zone de contact frite-broccolis
                {

                    ennemiDead=1; ///broccolis morte

                    ennemi[enmPos]->vie2=2; /// arrete d'etre crée
                    ennemi[enmPos]->x2=-1000;/// enlevé de l'ecran
                    frite[i]->nbr = 0; ///la condition n'est plus validé donc la frite reviens à la position de la défense
                    frite[i]->vie = 0;
                    frite[i]->x = -1000;
                    ennemi[enmPos]->y2=-100;
                    monnaietot += 20; ///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                }

            }
        }

    }
    return ennemiDead;
}

void PommeDeTerreToFrite(t_ennemi3* ennemi3[NACTEUR], t_frites* frite[NACTEURD], BITMAP* page)///collision pommes de terre frites
{
    int IsCollision = 0;

    IsCollision = collisionFrite3(ennemi3,frite,page);///appel de la fonction qui fait la collision
}

int collisionFrite3(t_ennemi3*ennemi[NACTEUR],t_frites*frite[NACTEURD],BITMAP*page) ///fonction de collision / mort des pommes de terre
{
    int enmPos,i;
    int ennemiDead=0; /// Si ennemiDead=0 alors la pomme de terre n'est pas morte

    int DistanzaInLine = 5;

    for (i=0; i<NACTEURD; i++) ///on parcours la boucle de defense/ des frites dans ce cas
    {

        for(enmPos=0; enmPos<NACTEUR; enmPos++) ///on parcours la boucle des pommes de terre
        {
            if(frite[i]->nbr==1) ///on pose une condition de validation
            {
                if((frite[i]->y==ennemi[enmPos]->y3) &&(frite[i]->x-DistanzaInLine <= ennemi[enmPos]->x3) && (frite[i]->x+DistanzaInLine >= ennemi[enmPos]->x3))///zone de contact frite-pommes de terre
                {

                    ennemiDead=1; ///tomate morte

                    ennemi[enmPos]->vie3=2; /// arrete d'etre crée
                    ennemi[enmPos]->x3=-1000;/// enlevé de l'ecran
                    frite[i]->nbr = 0; ///la condition n'est plus validé donc la frite reviens à la position de la défense
                    frite[i]->vie = 0;
                    frite[i]->x = -1000;
                    ennemi[enmPos]->y3=-100;
                    monnaietot += 20; ///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                }

            }
        }

    }
    return ennemiDead;
}


void TabDefenseToTomate(t_ennemi*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page)///collision tomates defense
{
    int j = 0;
    int IsCollision = 0;

    IsCollision = collisionEnemy(tab,defense,explosion,page,&j);///appel à la fonction de collision

}

int collisionEnemy(t_ennemi*ennemi[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses)
{
    int enmPos,i;
    int ennemiDead=0; /// Ennemi vivant
    int defenseDead=0;  /// Défense vivante

    int DistanzaInLine = 0; ///mesures pour le rayon d'impacte de la pizza
    int DistansaUpper  = 0;
    int DistanzaUnder  = 0;

    for (i=0; i<NACTEURD; i++)///on parcours le tableau de defances pour verifer si il y a collision
    {
        defenseDead=0;

        for(enmPos=0; enmPos<NACTEUR; enmPos++)/// on parcours te tableau des ennemies pour voir combiens sont dans le rayon de l'explosion
        {

            if((ennemi[enmPos]->x>=0&&ennemi[enmPos]->x<=155)&&(ennemi[enmPos]->y>=470&&ennemi[enmPos]->y<=650))
            {
                gameOver=1;
            }
            if(ennemiDead==0) ///si la tomate n'est pas encore morte => pas de collision alors le rayon d'attac est de:
            {
                DistanzaInLine = 30;
                DistansaUpper  = 10;
                DistanzaUnder  = 10;
            }
            else ///sinon il s'agrandis
            {
                DistanzaInLine = 200;
                DistansaUpper  = 200;
                DistanzaUnder  = 200;
            }

            if((defenses[i]->y == ennemi[enmPos]->y)&&(defenses[i]->x-DistanzaInLine <= ennemi[enmPos]->x)&& (defenses[i]->x+DistanzaInLine >= ennemi[enmPos]->x))
            {
                ///si une tomate autre que celle de contact se trouve à l'interieur de la zone d'explosion elle meurt avec la dèfense touché

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)///les conditions précedentes sont vraies seullement pour la défense de type pizza
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi[enmPos]->vie=2;
                    monnaietot += 20; ///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                    ennemi[enmPos]->y=-100;
                }

            }

            if((defenses[i]->y-100 == ennemi[enmPos]->y-100)&&(defenses[i]->x-DistanzaUnder <= ennemi[enmPos]->x)&& (defenses[i]->x+DistanzaUnder >= ennemi[enmPos]->x))
            {
                /// on vrifie pour toutes les dimensions

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi[enmPos]->vie=2;
                    monnaietot += 20;///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                    ennemi[enmPos]->y=-100;
                }

            }
            if((defenses[i]->y+100 == ennemi[enmPos]->y+100)&&((defenses[i]->x-DistansaUpper <= ennemi[enmPos]->x)&& (defenses[i]->x+DistansaUpper >= ennemi[enmPos]->x)))
            {
                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi[enmPos]->vie=2;
                    monnaietot += 20;///ennemi mort ce qui implique la formation d'une cagnotte pour le niveau suivant
                    ennemi[enmPos]->y=-100;
                }

            }


        }
        if(defenseDead==1)///quelque soit la défense touché par la tomate elle arrete d'exister
        {
            defenses[i]->creer = 2;
            defenses[i]->presence = 0;
            defenses[i]->vie = 2;
            defenses[i]->x = -15000;

            monnaietot-= 10 ; ///defense morte => malus dans la cagnotte
        }
    }
    monnaieDebut = monnaie + monnaietot; ///ajout de la cagnote à l'argent de base
    return ennemiDead;

}





void TabDefenseToBroccolis(t_ennemi2*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page)///collision broccolis defense
{
    int j=0,IsCollision=0;


    IsCollision = collisionEnemy2(tab,defense,explosion,page,&j);///appel de la fonction de collision


}

int collisionEnemy2(t_ennemi2*ennemi2[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses)
{
    ///toutes les meme regles que pour les tomates sont appliquees

    int enmPos,i;
    int ennemiDead=0;
    int defenseDead=0;

    int DistanzaInLine = 0;
    int DistansaUpper  = 0;
    int DistanzaUnder  = 0;

    for (i=0; i<NACTEURD; i++)
    {
        defenseDead=0;

        for(enmPos=0; enmPos<NACTEUR; enmPos++)
        {
            if(ennemiDead==0)
            {
                DistanzaInLine = 30;
                DistansaUpper  = 10;
                DistanzaUnder  = 10;
            }
            else
            {
                DistanzaInLine = 150;
                DistansaUpper  = 100;
                DistanzaUnder  = 100;
            }

            if(defenses[i]->y == ennemi2[enmPos]->y2
                    &&(defenses[i]->x-DistanzaInLine <= ennemi2[enmPos]->x2
                       && defenses[i]->x+DistanzaInLine >= ennemi2[enmPos]->x2))
            {

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi2[enmPos]->vie2=2;
                    monnaietot += 20; ///ennemi dead
                    ennemi2[enmPos]->y2=-100;
                }

            }

            if(defenses[i]->y-100 == ennemi2[enmPos]->y2-100
                    &&(defenses[i]->x-DistanzaUnder <= ennemi2[enmPos]->x2
                       && defenses[i]->x+DistanzaUnder >= ennemi2[enmPos]->x2))
            {

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi2[enmPos]->vie2=2;
                    monnaietot += 20; ///ennemi dead
                    ennemi2[enmPos]->y2=-100;
                }

            }
            if((defenses[i]->y+100 == ennemi2[enmPos]->y2+100)
                    &&((defenses[i]->x-DistansaUpper <= ennemi2[enmPos]->x2)
                       && (defenses[i]->x+DistansaUpper >= ennemi2[enmPos]->x2)))
            {
                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi2[enmPos]->vie2=2;
                    monnaietot += 20; ///ennemi mort
                    ennemi2[enmPos]->y2=-100;
                }
            }
        }
        if(defenseDead==1)
        {
            defenses[i]->creer = 2;
            defenses[i]->presence = 0;
            defenses[i]->vie = 2;
            defenses[i]->x = 15000;
            monnaietot -= 10; ///defense morte
        }
    }
    monnaieDebut = monnaie + monnaietot;
    return ennemiDead;

}


void TabDefenseToPommeDeTerre(t_ennemi3*tab[NACTEUR], t_defense* defense[NACTEURD],BITMAP* explosion,BITMAP* page)///collision pommes de terre defense
{

    int j=0,IsCollision=0;


    IsCollision = collisionEnemy3(tab,defense,explosion,page,&j);///appel de la fonction de collision


}

int collisionEnemy3(t_ennemi3*ennemi3[NACTEUR],t_defense*defenses[NACTEURD],BITMAP*explosion,BITMAP*page,int *deadDefeses)
{
    ///toutes les meme regles que pour les tomates sont appliquees
    int enmPos,i;
    int ennemiDead=0;
    int defenseDead=0;

    int DistanzaInLine = 0;
    int DistansaUpper  = 0;
    int DistanzaUnder  = 0;

    for (i=0; i<NACTEURD; i++)
    {
        defenseDead=0;

        for(enmPos=0; enmPos<NACTEUR; enmPos++)
        {
            if(ennemiDead==0)
            {
                DistanzaInLine = 30;
                DistansaUpper  = 10;
                DistanzaUnder  = 10;
            }
            else
            {
                DistanzaInLine = 150;
                DistansaUpper  = 100;
                DistanzaUnder  = 100;
            }

            if(defenses[i]->y == ennemi3[enmPos]->y3
                    &&(defenses[i]->x-DistanzaInLine <= ennemi3[enmPos]->x3
                       && defenses[i]->x+DistanzaInLine >= ennemi3[enmPos]->x3))
            {

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi3[enmPos]->vie3=2;
                    monnaietot += 20; ///ennemi dead
                    ennemi3[enmPos]->y3=-100;
                }

            }

            if(defenses[i]->y-100 == ennemi3[enmPos]->y3-100
                    &&(defenses[i]->x-DistanzaUnder <= ennemi3[enmPos]->x3
                       && defenses[i]->x+DistanzaUnder >= ennemi3[enmPos]->x3))
            {

                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi3[enmPos]->vie3=2;
                    monnaietot += 20; ///ennemi dead
                    ennemi3[enmPos]->y3=-100;
                }

            }
            if((defenses[i]->y+100 == ennemi3[enmPos]->y3+100)
                    &&((defenses[i]->x-DistansaUpper <= ennemi3[enmPos]->x3)
                       && (defenses[i]->x+DistansaUpper >= ennemi3[enmPos]->x3)))
            {
                ennemiDead=1;
                defenseDead =1;

                if(defenses[i]->type==2)
                {
                    draw_sprite(screen,explosion,defenses[i]->x,defenses[i]->y);
                    rest(30);
                    ennemi3[enmPos]->vie3=2;
                    monnaietot += 20; ///ennemi dead
                    ennemi3[enmPos]->y3=-100;
                }
            }
        }
        if(defenseDead==1)
        {
            defenses[i]->creer = 2;
            defenses[i]->presence = 0;
            defenses[i]->vie = 2;
            defenses[i]->x = 15000;
            monnaietot -= 10; ///ennemi dead
        }
    }
    monnaieDebut = monnaie + monnaietot;
    return ennemiDead;
}
