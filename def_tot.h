#ifndef DEF_TOT_H_INCLUDED
#define DEF_TOT_H_INCLUDED
#define NIMG 3
#define NIMAG 4
#define NACTEURD 50
#define NACTEUR 10

///prototypes des défenses

typedef struct defense
{
    int imgcourante;
    int cptimg;
    int tmpimg;
    int presence;
    int x,y;
    int tx;
    int ty;
    int creer;
    int type;
    int vie;
} t_defense;

typedef struct money
{
    int imgcourante;
    int cptimg;
    int tmpimg;
    int presence;
    int x,y;
    int tx;
    int ty;
    int creer;
    int timer;
    int vie;
} t_money;


void initialiserAllegro();
void chargerFichier(BITMAP*tab[NIMG]);
void chargerFichier2(BITMAP*animation[NIMAG]);
void chargerFichier3(BITMAP*animation[NIMAG]);
void chargerFichier4(BITMAP*animation[NIMAG]);
void chargerMoney(BITMAP*money_bmp[NIMG]);
t_defense*creerD();
t_money*creerM();
void remplirTabActeurD(t_defense*tab[NACTEURD]);
void remplirTabMoney(t_money*tabA[NACTEUR]);
void actualiser_defense(t_defense*defense);
void actualiser_money(t_money*money);
void actualiserTabDefense(t_defense*tab[NACTEURD]);
void actualiserTabMoney(t_money*tabA[NACTEUR]);
void dessinerDefense(BITMAP*bmp,t_defense*defense,BITMAP*animationd[NIMAG],BITMAP*animation2d[NIMAG],BITMAP*animation3d[NIMAG]);
void dessinerMoney(BITMAP*bmp,t_money*money,BITMAP*money_bmp[NIMG]);
void dessinerTabDefense(BITMAP*bmp,t_defense*tab[NACTEURD],BITMAP*animation[NIMAG],BITMAP*animation2[NIMAG],BITMAP*animation3[NIMAG]);
void dessinerTabMoney(BITMAP*bmp,t_money*tabA[NACTEUR],BITMAP*money_bmp[NIMG]);
void creer_perso(t_defense *tab[NACTEURD],int x,int y, int type,BITMAP**tab2);
void creer_money(t_money *tabA[NACTEUR],int x,int y, int timer,BITMAP**tab2);
void chargerTousDefenses(BITMAP*animationd[NIMG],BITMAP*animation2d[NIMG],BITMAP*animation3d[NIMG],BITMAP**tab);

int valAbs(int val);
int DefPos(int py);


#endif // DEF_TOT_H_INCLUDED
