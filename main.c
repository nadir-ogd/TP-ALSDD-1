#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphique.h"
//#define max 1000
#define east 35
#define center 42
#define ouest 31

//Groupe 5

//Réalisé par :


// Ouagued Nadir
// Boukerfa Mohamed elamin




/*           _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |  bibliothèque de la partie 1  |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */




//------------------------------------------------------------------------------------------------
//------------------------------(  la machine abstraite   )---------------------------------------
//------------------------------------------------------------------------------------------------

typedef struct pop_1
{
    char nomfam_1[20];
    struct pop_1 *suivant_1;
} pop_1;
//------------------------------------------------------------------------------------------------
typedef struct Liste_1
{
    struct pop_1 *premier_1;
    int taille_1;
} Liste_1;
//------------------------------------------------------------------------------------------------

Liste_1 *initialisation_1()
{
    Liste_1 *liste = malloc(sizeof(*liste));
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    liste->premier_1 = NULL;
    return liste;
}
//------------------------------------------------------------------------------------------------

void allouer_1(pop_1 **nouveau)
{
    *nouveau = (pop_1 *)malloc(sizeof(pop_1));
}

//------------------------------------------------------------------------------------------------

void aff_adr_1(pop_1 *p, pop_1 *q)
{
    p->suivant_1 = q;
}

//------------------------------------------------------------------------------------------------

pop_1 *suivant_1(pop_1 *p)
{
    return p->suivant_1;
}

//------------------------------------------------------------------------------------------------
/*nous affiche le contenu des maillons  */

void afficher_1(Liste_1 *tete)
{
    int i=1;
    if (tete != NULL)
    {
        pop_1 *p = tete->premier_1;
        while (p != NULL)
        {
            printf("La famille n%c%d    : %s\n",248,i,p->nomfam_1);
            p = suivant_1(p);
            i++;
        }
        printf("\n");
    }
}
//------------------------------------------------------------------------------------------------
/*nous renvoie un pointeur sur le maillon qui précede 'elem'  */

pop_1 *avant_1(Liste_1 *tete, pop_1 *elem)
{
    pop_1 *p = tete->premier_1;

    if (tete != NULL)
    {
        while (suivant_1(p) != elem)
        {
            p = suivant_1(p);
        }
    }
    return p;
}

//------------------------------------------------------------------------------------------------
//-----------------------------------(  modules TP01  )-------------------------------------------
//------------------------------------------------------------------------------------------------

/*crée une llc a partir de 'nbfamille' noms de familles saisis d'un fichier  */

Liste_1 *creer_popf_1(int nbFamille)
{
    Liste_1 *tete = initialisation_1();
    if (nbFamille)
    {
        pop_1 *p, *q;
        FILE *fic = fopen("brr", "r");
        allouer_1(&p);
        fgets((p->nomfam_1), 20, fic);
        tete->premier_1 = p;
        for (int i = 1; i < nbFamille; i++)
        {
            allouer_1(&q);
            fgets((q->nomfam_1), 20, fic);
            aff_adr_1(p, q);
            p = q;
        }
        aff_adr_1(p, NULL);
        fclose(fic);
    }
    tete->taille_1 = nbFamille;
    return tete;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*permute les adresses de  p et q  */

void permutAdr_1(Liste_1 *tete, pop_1 *p, pop_1 *q)
{
    pop_1 *i = avant_1(tete, p);
    pop_1 *i1 = avant_1(tete, q);
    pop_1 *i2 = suivant_1(q);
    pop_1 *i3 = suivant_1(p);

    aff_adr_1(i, q);
    aff_adr_1(i1, p);
    aff_adr_1(p, i2);
    aff_adr_1(q, i3);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
int test_1(char a[], char b[], int i)
{
    int vrai = 1;
    while (i)
    {
        if (a[i - 1] != b[i - 1])
        {
            vrai = 0;
        }
        i--;
    }
    return vrai;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
pop_1 *acceVal(Liste_1 *tete, char nom[])
{
    pop_1 *p = tete->premier_1;
    int i = 0;
    int vrai = 1;

    while ((nom[i] > p->nomfam_1[i]) && (test(nom, p->nomfam_1, i)) && (suivant_1(p) != NULL))
    {
        while (nom[i] == (suivant_1(p)->nomfam_1[i]))
        {
            i++;
        }
        p = suivant_1(p);
        vrai = 0;
    }
    if (vrai || (suivant_1(p) == NULL)) /*|| (avant(tete, p)==tete->premier)) */ /*le cas ou on doit ajouter le nouveau maillon a la téte ou a la queue*/
    {
        return p;
    }
    else
        return avant_1(tete, p);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*permute le contenu des maillons p et q  */

void permutCont_1(pop_1 *p, pop_1 *q)
{
    char i[20];
    strcpy(i, q->nomfam_1);
    strcpy(q->nomfam_1, p->nomfam_1);
    strcpy(p->nomfam_1, i);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
pop_1 *acceePos(Liste_1 *tete, int pos)
{
    pop_1 *p = tete->premier_1;
    if (pos != 0)
    {
        int i = 1;
        while (i < pos)
        {
            if (suivant_1(p) == NULL)
            {
                break;
            }
            else
            {
                p = suivant_1(p);
            }
            i++;
        }
    }

    return p;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

/*genere un entier compri entre min et max aléatoirement */

int numAleatoire_1(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

/*genere un nom aléatoirelent et le range dans nom[] */

void genererNom_1(char nom[])
{

    int taille = numAleatoire_1(3, 15);

    nom[0] = numAleatoire_1(65, 90);

    for (int i = 1; i < taille; i++)
    {
        nom[i] = numAleatoire_1(97, 122);
    }
    nom[taille] = '\0';
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

/*crée une llc a partir de 'nbfamille' noms de familles générés aléatoirement  */

Liste_1 *creer_pop_1(int nb_famille)
{
    Liste_1 *tete = initialisation_1();
    if (nb_famille)
    {
        pop_1 *p, *q;
        allouer_1(&p);
        genererNom_1(p->nomfam_1);
        tete->premier_1 = p;
        for (int i = 1; i < nb_famille; i++)
        {
            allouer_1(&q);
            genererNom_1(q->nomfam_1);
            aff_adr_1(p, q);
            p = q;
        }
        aff_adr_1(p, NULL);
    }
    tete->taille_1 = nb_famille;

    return tete;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*nous renvoie le nombre de maillons dans la liste (nombre de familles )  */

int nbfamille_1(pop_1 *tete)
{
    int nb = 0;
    while (tete)
    {
        nb++;
        tete = suivant_1(tete);
    }
    return nb;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*nous renvoie l'adresse du maillon qui contient le nom de famille "nom"
      et NULL si ce dernier n'est pas présent dans la liste  */

pop_1 *present(pop_1 *tete, char nom[])
{
    while ((strcmp(nom, tete->nomfam_1)) && (tete != NULL))
    {
        tete = suivant_1(tete);
        printf("%s\n", tete->nomfam_1);
    }
    return tete;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*tri les maillons de la liste par ordre alphabétique
( inspiré du tri par bulles )  */
void trier_pop_1(Liste_1 *liste)
{
    pop_1 *p, *q;
    char vrai = 100;
    while (vrai == 100)
    {

        p = liste->premier_1;
        q = suivant_1(p);
        vrai = 0;
        while (q)
        {
            char i = 0;
            //dans le cas ou les premiéres léttres sont identiques
            while ((p->nomfam_1[i]) == q->nomfam_1[i])
            {
                i++;
            }
            if (((p->nomfam_1[i]) > (q->nomfam_1[i])) && (strcmp(q->nomfam_1, p->nomfam_1)))
            {
                permutCont_1(p, q);
                vrai = 100;
            }
            p = q;
            q = suivant_1(q);
        }
    }
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void inserDebut(Liste_1 *tete, char nom[])
{
    pop_1 *q;
    allouer_1(&q);
    aff_adr_1(q, tete->premier_1);
    strcpy(q->nomfam_1, nom);
    tete->premier_1 = q;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void inserFin(Liste_1 *tete, char nom[])
{
    pop_1 *q;
    allouer_1(&q);
    aff_adr_1(acceVal(tete, nom), q);
    aff_adr_1(q, NULL);
    strcpy(q->nomfam_1, nom);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void inserMilieu(Liste_1 *tete, char nom[])
{
    pop_1 *q;
    allouer_1(&q);
    aff_adr_1(q, suivant_1(acceVal(tete, nom)));
    aff_adr_1(acceVal(tete, nom), q);
    strcpy(q->nomfam_1, nom);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*insére 'nom' dans la liste trié*/
void inser(Liste_1 *tete, char nom[])
{
    if ((nom[0] != NULL))
    {

        pop_1 *p = acceVal(tete, nom);
        if (p == tete->premier_1)
        {
            if (strcmp(p->nomfam_1, nom) != 0)
            {
                inserDebut(tete, nom);
                tete->taille_1++;
            }
        }
        else if (suivant_1(p) == NULL)
        {
            if (strcmp(p->nomfam_1, nom) != 0)
            {
                inserFin(tete, nom);
                tete->taille_1++;
            }
        }
        else
        {
            if (strcmp(suivant_1(p)->nomfam_1, nom) != 0)
            {
                inserMilieu(tete, nom);
                tete->taille_1++;
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void suppDebut(Liste_1 *tete, char nom[])  /* module qui supprime une famille du debut */
{
    pop_1 *i;
    i = suivant_1(tete->premier_1);
    free(tete->premier_1);
    tete->premier_1 = i;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void suppFin(Liste_1 *tete, char nom[]) /* module qui supprime une famille de la fin */
{
    free(acceVal(tete, nom));
    aff_adr_1(avant_1(tete, acceVal(tete, nom)), NULL);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void suppMilieu(Liste_1 *tete, char nom[])  /* module qui supprime une famille du milieu */
{
    pop_1 *i = acceVal(tete, nom), *j = suivant_1(i);
    aff_adr_1(i, suivant_1(j));

    free(j);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void supp(Liste_1 *tete, char nom[])  /* module qui supprime une famille de n'importe quelle position  */
{
    if (nom[0] != NULL)
    {
        int vrai = 0;
        pop_1 *p = acceVal(tete, nom);
        if (p == tete->premier_1)
        {
            if (strcmp(p->nomfam_1, nom) == 0)
            {
                suppDebut(tete, nom);
                vrai = 1;
            }
        }
        else if (suivant_1(p) == NULL)
        {
            if (strcmp(p->nomfam_1, nom) == 0)
            {
                suppFin(tete, nom);
                vrai = 1;
            }
        }
        else if ((suivant_1(p) != NULL) && (p != tete->premier_1))
        {
            if (strcmp(suivant_1(p)->nomfam_1, nom) == 0)
            {

                suppMilieu(tete, nom);
                vrai = 1;
            }
        }
        if (vrai ==  1)
        {
            tete->taille_1--;
            gotoxy(43,16);
            textbackground(0);
            textcolor(15);
            printf("Le famille '%s' a %ct%c supprim%c .",nom,130,130,130);
        }
        else
        {
            gotoxy(43,16);
            textbackground(0);
            textcolor(15);
            printf("Le famille '%s' n'%cxiste pas .",nom,130);
        }
    }
}



/*           _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |  bibliothèque de la partie 2  |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */





//--------------------------------------------------------------------------------------
//-----------------------  ( * déclaration des types *)  -------------------------------
//--------------------------------------------------------------------------------------
typedef char ch20[20];
typedef struct famille *pf;
typedef struct voiture *pv;
typedef struct personne *pp;
typedef struct pop
{
    pf premier;
    pf dernier;
    int nbFam;
} pop;

struct famille
{
    ch20 nom;
    pp parent;
    pp enfant;
    pv voiture;
    pf suivant;
};

struct personne
{
    ch20 prenom;
    char sexe;
    pp suivant;
};

struct voiture
{
    ch20 marque;
    ch20 numero;
    pf family;
    pv suivant;
};

//---------------------------------------------------------------------------------------
//------------------------  ( * modules nécessaires  *)  -------------------------------
//--------------------------------------------------------------------------------------
pop *initialisation()  /* module qui initialise la population */
{
    pop *tete = malloc(sizeof(struct pop));
    if (tete == NULL)
    {
        exit(EXIT_FAILURE);
    }
    tete->premier = NULL;
    tete->nbFam = 0;
    return tete;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
pf suivantf(pf fam)
{
    fam = fam->suivant;
}

pv suivantv(pv voit)
{
    voit = (voit->suivant);
}

pp suivantp(pp perso)
{
    perso = (perso->suivant);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void allouerFamille(pf *tete)
{
    *tete = malloc(sizeof(struct famille));
}
void allouerVoiture(pv *tete)
{
    *tete = malloc(sizeof(struct voiture));
}
void allouerPersonne(pp *tete)
{
    *tete = malloc(sizeof(struct personne));
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*nous renvoie un pointeur sur le maillon qui précede 'elem'  */

pf avant(pop *tete, pf elem)
{

    while (tete->premier->suivant != elem)
    {
        tete->premier = tete->premier->suivant;
    }
    return tete->premier;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

void aff_adr(pf p, pf q)
{
    p->suivant = q;
}

void aff_adrv(pv p, pv q)
{
    p->suivant = q;
}
void aff_adrp(pp p, pp q)
{
    p->suivant = q;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void afficherp(pf tete)  /* module qui affiche les parents d'une famille tete */
{
    if (tete != NULL)
    {
        textbackground(15);
        textcolor(0);
        printf("Les parents sont :");

        if (tete->parent)
        {
            pp p = tete->parent;
            while (p != NULL)
            {
                if (p->sexe == 'H')
                {
                    textbackground(15);
                    textcolor(9);
                    printf("Le p%cre : %s |  ",138,p->prenom);
                }
                else
                {
                    textbackground(15);
                    textcolor(9);
                    printf("La m%cre : %s |  ",138,p->prenom);
                }
                p = p->suivant;
            }
        }
    }
}
void affichere(pf tete)  /* module qui affiche les enfants d'une famille tete */
{
    if (tete != NULL)
    {
        textbackground(15);
        textcolor(0);
        printf("Les enfants sont : ");

        if (tete->enfant)
        {
            pp p = tete->enfant;
            while (p != NULL)
            {
                textbackground(15);
                textcolor(9);
                printf("%s :", p->prenom);
                printf("%c |", p->sexe);
                p = p->suivant;
            }
        }
    }
}
void afficherv(pf tete)  /* module qui affiche les voitures posédées d'une famille tete */
{
    if (tete != NULL)
    {
        textbackground(15);
        textcolor(0);
        printf("Les voitures pos%cd%ces: ",130,130);

        pv p = tete->voiture;
        while (p != NULL)
        {
            textbackground(15);
            textcolor(9);
            printf("%s :", p->marque);
            printf("%s |", p->numero);

            p = p->suivant;
        }
    }
}
void afficher(pop *tete)  /* module qui affiche toutes les familles de la population */
{
    if (tete != NULL)
    {
        int i = 1;
        pf p = tete->premier;
        while (p != NULL)
        {
            printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            textbackground(15);
            textcolor(0);
            printf("%d_Le Nom de famille est :%s   ", i, p->nom);
            printf("\n");

            afficherp(p);
            printf("\n");

            affichere(p);
            printf("\n");

            afficherv(p);
            p = p->suivant;
            i++;
            printf("\n");
        }
    }
}
void afficher1(pop *tete)
{
    if (tete != NULL)
    {
        int i = 1;
        pf p = tete->premier;
        while (p != NULL)
        {
            textbackground(15);
            textcolor(0);
            printf("%d_Le Nom de famille est : ", i);
            textbackground(15);
            textcolor(9);
            printf("%s",p->nom);
            printf("\n");

            afficherp(p);
            printf("\n");

            affichere(p);
            printf("\n");

            afficherv(p);
            p = p->suivant;
            i++;
            printf("\n");
            textbackground(7);
            textcolor(7);
            printf("                                                                                                                                                      ");
            textbackground(15);
            textcolor(15);
            char a = getchar();
        }
    }
    else {
                    gotoxy(67,12);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
    }
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

/*un module qui genere un entier compri entre min et max aléatoirement */
int numAleatoire(int min, int max)
{
    return ((rand() % (max - min + 1)) + min);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

/*un module qui genere un nom aléatoirement et le range dans nom[] */

void genererNom(char nom[])
{

    int taille = numAleatoire(3, 15);

    nom[0] = numAleatoire(65, 90);

    for (int i = 1; i < taille; i++)
    {
        nom[i] = numAleatoire(97, 122);
    }
    nom[taille] = '\0';
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------*
void nomVoiture(ch20 a)   /*un module qui genere un nom d'une voiture aléatoirement et le range dans a[20]*/
{
    FILE *fic = fopen("nomVoiture", "r");
    char b[20];
    int i;
    for (i = numAleatoire(1, 38); i >= 0; i--)
    {
        fgets(b, 20, fic);
    }
    i = 0;
    while (b[i] != '\n')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';

    fclose(fic);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void sexe(pp enfant)  /*un module qui genere le sexe d'un enfant aléatoirement */
{
    int i = numAleatoire(0, 1);
    if (i == 0)
        enfant->sexe = 'H';

    else
        enfant->sexe = 'F';
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void creerParent(pf par) /* un module qui crée les parents de la famille par */
{
    int i = numAleatoire(0, 2);
    pp p, q;

    if (i > 0)
    {
        allouerPersonne(&p);
        genererNom(p->prenom);
        sexe(p);
        par->parent = p;
        --i;

        if (i > 0)
        {
            allouerPersonne(&q);
            genererNom(q->prenom);
            if (par->parent->sexe == 'H')
            {
                q->sexe = 'F';
            }
            else
            {
                q->sexe = 'H';
            }

            aff_adrp(p, q);
            p = q;
        }
        aff_adrp(p, NULL);
    }
    else
    {
        par->parent = NULL;
    }
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

void creerEnfant(pf enf)  /* un module qui crée les enfants de la famille par */
{
    int i = numAleatoire(0, 5);
    pp p, q;

    if (i > 0)
    {
        allouerPersonne(&p);
        genererNom(p->prenom);
        sexe(p);
        enf->enfant = p;

        while (i > 0)
        {
            allouerPersonne(&q);
            genererNom(q->prenom);
            sexe(q);
            aff_adrp(p, q);
            p = q;
            i--;
        }

        aff_adrp(p, NULL);
    }
    else
    {
        enf->enfant = NULL;
        aff_adrp(p, NULL);
    }
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void creerNumero(ch20 voit) /*un module qui genere le matricule d'une voiture aléatoirement et le range dans voit[]*/
{
    char p;
    for (int i = 0; i < 5; i++)
    {
        voit[i] = (char)numAleatoire(48, 57);
    }
    voit[5] = '-';
    voit[6] = '1';
    voit[7] = (char)numAleatoire(48, 49);
    voit[8] = (char)numAleatoire(48, 57);
    voit[9] = '-';
    voit[10] = (char)numAleatoire(48, 52);
    voit[11] = (char)numAleatoire(48, 56);
    voit[12] = '\0';
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void creerVoiture(pf fam)  /* un module qui crée les voitures de la famille fam */
{
    pv p, q;
    allouerVoiture(&p);
    nomVoiture(p->marque);
    creerNumero(p->numero);
    fam->voiture = p;

    for (int i = 1; i <= numAleatoire(1, 3); i++)
    {
        allouerVoiture(&q);
        nomVoiture(q->marque);
        creerNumero(q->numero);

        aff_adrv(p, q);
        p = q;
    }

    aff_adrv(p, NULL);
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
/*crée une llc a partir de 'nbfamille' noms de familles générés aléatoirement  */

pop *creer_pop(int nb_famille)
{
    pop *tete = initialisation();

    if (nb_famille)
    {
        pf p, q;
        allouerFamille(&p);
        creerParent(p);
        creerVoiture(p);
        creerEnfant(p);
        genererNom(p->nom);
        tete->premier = p;
        for (int i = 1; i < nb_famille; i++)
        {
            allouerFamille(&q);
            creerParent(q);
            creerVoiture(q);
            creerEnfant(q);
            genererNom(q->nom);
            aff_adr(p, q);
            p = q;
        }
        aff_adr(p, NULL);
        tete->dernier = p;
    }
       return tete;

}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void permutCont(pf p, pf q) /* un module qui sert a permiter entre deux familles p & q (pour le tri) */
{
    ch20 ic;
    strcpy(ic, p->nom);
    strcpy(p->nom, q->nom);
    strcpy(q->nom, ic);
    pp i = p->parent;
    p->parent = q->parent;
    q->parent = i;
    i = p->enfant;
    p->enfant = q->enfant;
    q->enfant = i;
    pv in = p->voiture;
    p->voiture = q->voiture;
    q->voiture = in;
} //------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void trier_enf(pf fam) /* un module qui sert à trier la liste  des enfants de la famille fam */
{
    if (fam->enfant)
    {

        pp p, q;
        char vrai = 100;
        while (vrai == 100)
        {

            p = fam->enfant;
            q = fam->enfant->suivant;
            vrai = 0;
            while (q)
            {
                char i = 0;
                //dans le cas ou les premiéres léttres sont identiques
                while (p->prenom[i] == q->prenom[i])
                {
                    i++;
                }
                if (((p->prenom[i]) > (q->prenom[i])) && (strcmp(q->prenom, p->prenom)))
                {
                    ch20 in;
                    strcpy(in, p->prenom);
                    strcpy(p->prenom, q->prenom);
                    strcpy(q->prenom, in);
                    char inte = p->sexe;
                    p->sexe = q->sexe;
                    q->sexe = inte;
                    vrai = 100;
                }
                p = q;
                q = q->suivant;
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void trier_pop(pop *liste)  /* un module qui sert à trier la liste  de population liste */
{

    pf p, q;
    char vrai = 100;
    while (vrai == 100)
    {

        p = liste->premier;
        q = suivantf(p);
        vrai = 0;
        while (q)
        {
            trier_enf(p);
            char i = 0;
            //dans le cas ou les premiéres léttres sont identiques
            while (p->nom[i] == q->nom[i])
            {
                i++;
            }
            if (((p->nom[i]) > (q->nom[i])) && (strcmp(q->nom, p->nom)))
            {
                permutCont(p, q);
                vrai = 100;
            }
            p = q;
            q = suivantf(q);
        }
    }
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
int nbfamillesansparent(pop *liste)  /* un module qui renvoie le nombre de familles sans parents dans la population */
{
    pf fam = liste->premier;
    int i = 0;
    while (fam)
    {
        if (fam->parent == NULL)
        {
            i++;
        }
        fam = suivantf(fam);
    }
    return i;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
int nbenfantfam(pf fam)  /* un module qui renvoie le nombre des enfants d'une famille fam */
{
    int i = 0;
    if (fam->enfant != NULL)
    {
        pp enf = fam->enfant;
        while (enf)
        {
            i++;
            enf = enf->suivant;
        }
    }
    return i;
}
int nbenfant(pop *liste)  /* un module qui renvoie le nombre des enfants de la population liste */
{
    int i = 0;
    pf p = NULL;
    if (p = liste->premier)
    {
        while (p)
        {
            i += nbenfantfam(p);
            p = suivantf(p);
        }
    }
    return i;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

int test(ch20 a, ch20 b, int i)
{
    int vrai = 1;
    while (i)
    {
        if (a[i - 1] != b[i - 1])
        {
            vrai = 0;
        }
        i--;
    }
    return vrai;
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

pf acceNom(pop *liste, ch20 nom) /* un module qui sert a accéder a un nom d'une famille afin de vérifier si la famille existe */
{
    int i = 0;
    pf p = NULL;
    if (liste->premier)
    {
        p = liste->premier;
        int i = 0;
        int vrai = 1;

        while ((nom[i] > p->nom[i]) && (test(nom, p->nom, i)) && (suivantf(p) != NULL))
        {
            while (nom[i] == (suivantf(p)->nom[i]))
            {
                i++;
            }
            p = suivantf(p);
            vrai = 0;
        }
        if (vrai || (suivantf(p) == NULL)) // || (avant(tete, p)==tete->premier)) */ /*le cas ou on doit ajouter le nouveau maillon a la tete ou a la queue
        {
            if ((strcmp(nom, p->nom)) && (strcmp(nom, liste->premier->nom)))
            {
                return NULL;
            }
            else
            {
                return p;
            }
        }
        else
            return p;
    }
    else
    {
        return NULL;
    }
}
int nbenfnomfam(pop *liste, ch20 nom)  /* un module qui renvoie le nombre des enfants d'une famille fam  par son nom */
{
    pf p = NULL;
    if (p = acceNom(liste, nom))
    {
      return (nbenfantfam(p));
    }
    else
    {
        return -1;
    }
}
void naissanceTrie(pop *liste, ch20 fam, ch20 nom, char sexe)  /* sert à ajouter un nouveau né à la famille fam par nom , sexe (la liste d'enfants est triée) */
{

    pf p = acceNom(liste , fam);
    if (p == NULL)
    {
        gotoxy(39,23);
        textbackground(0);
        textcolor(15);
        printf("\nCette famille n'appartient pas a la liste \n");

    }
    else
    {
        pp nv = NULL;
        allouerPersonne(&nv);
        strcpy(nv->prenom, nom);
        nv->sexe = sexe;
        aff_adrp(nv, p->enfant);
        p->enfant = nv;
        trier_enf(p);
        gotoxy(39,23);
        textbackground(0);
        textcolor(15);
        printf("Le nouveau n%c '%s' a %ct%c ajout%c %c la famille '%s'\n",130,nom,130,130,130,133,fam);
    }
}


  pf RechFamVoit1(pop *liste , ch20 number)  /* Un module qui renvoie l'adresse de la famille possédant la voitur volée par son matricule */
{
    pf fam = (liste->premier),pointf;
    int verif = 1;
    while((fam != NULL) && (verif == 1))
    {
         pv voit = (fam->voiture);
        while((voit != NULL) && (verif == 1))
        {
           if (strcmp(voit->numero,number) == 0)
           {
            verif = 0;
            pointf = fam;
           }
         voit = suivantv(voit);
        }
    fam = suivantf(fam);
    }

    if (verif == 0)
    {
        gotoxy(38,20);
        textbackground(0);
        textcolor(15);
        printf("L'adresse de la famille possedant cette voiture est : \n");
        gotoxy(57,22);
        printf("%p\n",pointf);
    }
    else if (verif == 1)
    {
        gotoxy(35,20);
        textbackground(0);
        textcolor(15);
        printf("La voiture demand%ce n'existe pas et l'adresse de cette famille est : \n",130);
        gotoxy(57,22);
        printf("%p\n",NULL);
    }
}


/* Le deuxieme module facultatif qui renvoie l'adresse de la famille possédant la voiture volée en
 ajoutant dans la structure de la voiture un nouveau champs qui est l'adresse de la famille : */


  pf RechFamVoit2(pop *liste , ch20 number)
{
    pf fam = (liste->premier);
    int verif = 1;
    pv p;
    while((fam != NULL) && (verif == 1))
    {
         pv voit = (fam->voiture);
        while((voit != NULL) && (verif == 1))
        {
           if (strcmp(voit->numero,number) == 0)
           {
            verif = 0;
            p = voit;
           }
         voit = suivantv(voit);
        }
    fam = suivantf(fam);
    }

    if (verif == 0)
    {
        printf("L'adresse de la famille possedant cette voiture est : %p\n",p->family);
    }
    else if (verif == 1)
    {
        printf("La voiture demandée n'existe pas ou l'adresse de cette famille est : %p\n",NULL);
    }
}
















/*           _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |       Programme Général       |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */




int main()
{
   intro(); //module d'acceuil
   deb: //étiquette de début
   basemenu_partie();// affichage menu choix des parties
   textcolor(0);
   textbackground(7);
   printdirection("VEUILLEZ CHOISIR LA PARTIE QUE VOUS VOULLEZ TRAITER :","right",35,18,10);
   Liste_1 *liste = initialisation_1();
   int taille = nbfamille_1(liste->premier_1);
   liste->taille_1 = NULL;
   switch (choix_partie()) { //menu choix des parties
    case 1:
    men1:
    system("cls");
    basemenu_1(); //affichage menu choix de la partie 1
    srand(time(NULL));
        switch (choix_1()) { //menu choix de la partie 1
        case 1:{
             system("cls");
             textcolor(0);
             textbackground(7);
             printdirection("                                            CREATION D'UNE NOUVELLE POPULATION                                          ","right",1,4,5);
             decalrectangle(3);
            int d = choix_c_i();
            if (d <= 0) {
            liste = NULL;
            }
            else {
            liste = creer_pop_1(d);
            trier_pop_1(liste);
            }
             textcolor(15);
             textbackground(0);
             printdirection("                      PROGRESSION                     ","right",33,20,0);textbackground(7);
             printdirection("                                                      ","right",33,21,0);textbackground(7);
             printdirection("                                                      ","right",33,22,0);textbackground(7);
             printdirection("                                                      ","right",33,23,0);textbackground(7);
             printdirection("                                                      ","right",35,22,0);
             gotoxy(58,22);
             textcolor(0);
             printf("FIN");
             gotoxy(40,30);
             system("pause");
           break;
          }
          case 2:
            system("cls");
            textcolor(0);
            textbackground(7);
            printdirection("                                             AJOUT D'UNE NOUVELLE FAMILLE                                        ","right",1,4,5);
            decalrectangle(3);
            textcolor(15);
            textbackground(7);
            if(liste == NULL){
            gotoxy(40,19);
            textbackground(0);
            textcolor(15);
            printf("La liste de population est vide ! \n");
            }
            else {
            if (liste->taille_1)
            {
                char a[20];
                gotoxy(4,12);
                printf(" <> LE NOM DE LA FAMILLE : ");
                textcolor(0);
                textbackground(15);
                gotoxy(36,12);
                scanf(" %s", a);
                if (a[0] > 92)
                {
                    a[0] -= 32;
                }
                inser(liste, a);
                 gotoxy(50,20);
                 textbackground(0);
                 textcolor(15);
                 printf("Famille ajout%ce !",130);
            }
            else if(liste->taille_1 == NULL)
            {
             gotoxy(43,16);
             textbackground(0);
             textcolor(15);
             printf("La liste est vide !");
            }
            }
            textbackground(15);
            textcolor(0);
            gotoxy(40,30);
            system("pause");
            break;
        case 3:
        {
            system("cls");
                textcolor(0);
                textbackground(7);
                printdirection("                                           SUPPRESSION D'UNE FAMILLE PAR NOM                                           ","right",1,4,5);
                decalrectangle(3);
                textcolor(15);
                textbackground(7);
                if(liste == NULL){
                gotoxy(40,19);
                textbackground(0);
                textcolor(15);
                printf("La liste de population est vide ! \n");
                }
                else {
                textcolor(15);
                textbackground(7);
                int t= liste->taille_1;
                char a[20];
                gotoxy(4,8);
                printf(" <> LE NOM DE LA FAMILLE A SUPPRIMER : ");gotoxy(4,10);
                textcolor(0);
                textbackground(15);
                gotoxy(50,8);
                scanf("%s", &a);gotoxy(50,15);
                if (a[0] > 92)
                {
                    a[0] -= 32;
                }
                supp(liste, a);
                }
                 gotoxy(40,30);
                 textbackground(15);
                 textcolor(0);
                 system("pause");
            break;

        }
        case 4:
            system("cls");
            textcolor(0);
                textbackground(7);
                printdirection("                                                AFFICHAGE DE LA LISTE                                                  ","right",1,4,5);
                     if (liste == NULL )
                     {
                     gotoxy(40,19);
                     textbackground(0);
                     textcolor(15);
                     printf("La liste de population est vide ! \n");
                     }
                     else{
                     if (liste->taille_1)
                     {
                     gotoxy(4,12);
                     afficher_1(liste);
                     }
                     }
                     gotoxy(40,30);
                     textbackground(15);
                     textcolor(0);
                     system("pause");
                     break;
        case 5:
         goto deb; //cas de cliquer sur exit
        break;
        }
        goto men1;
        break;
        case 2:
                men2:
                system("cls");
                srand(time(NULL));
                basemenu_2(); //affichage menu choix de la partie 2
                switch (choix_2())// menu choix de la partie 2
                {
                case 1:
                    system("cls");
                    textcolor(0);
                    textbackground(7);
                    printdirection("                                            CREATION D'UNE NOUVELLE POPULATION                                          ","right",1,4,5);
                    decalrectangle(3);
                    int m=0,nb = choix_c_i();
                    pop *mpp = NULL;
                    if (nb <= 0) {
                        mpp = NULL;
                    }
                     else {
                    mpp = creer_pop(nb);
                    trier_pop(mpp);}
                     textcolor(15);
                     textbackground(0);
                     printdirection("                      PROGRESSION                     ","right",33,20,0);textbackground(7);
                     printdirection("                                                      ","right",33,21,0);textbackground(7);
                     printdirection("                                                      ","right",33,22,0);textbackground(7);
                     printdirection("                                                      ","right",33,23,0);textbackground(7);
                     printdirection("                                                  ","right",35,22,0);
                     gotoxy(58,22);
                     textcolor(0);
                     printf("FIN!");
                     gotoxy(40,30);
                    system("pause");
                    break;
                case 2:
                system("cls");
                 textcolor(0);
                textbackground(7);
                printdirection("                                             NOMBRE DE FAMILLES SANS PARENT(S)                                          ","right",1,4,5);
                decalrectangle(3);
                textcolor(15);
                textbackground(7);
                gotoxy(4,12);
                if(mpp == NULL){
                        gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
                }
                else{
                gotoxy(39,16);
                 textbackground(0);
                 textcolor(15);
                printf("Le nombre de familles sans parent(s) est : %d\n", nbfamillesansparent(mpp));
                }
                textbackground(15);
                textcolor(0);
                gotoxy(40,30);
                system("pause");
                break;
                case 3:
                system("cls");
                 textcolor(0);
                textbackground(7);
                printdirection("                                             NOMBRE D'ENFANTS DE LA POPULATION                                          ","right",1,4,5);
                decalrectangle(3);
                textcolor(15);
                textbackground(7);
                if(mpp == NULL){
                        gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
                }
                else {
                gotoxy(40,16);
                 textbackground(0);
                 textcolor(15);
                printf("Le nombre d'enfant de la population est : %d\n", nbenfant(mpp));
                }
                 textbackground(15);
                textcolor(0);
                gotoxy(40,30);
                system("pause");
                break;
                case 4:
                system("cls");
                textcolor(0);
                textbackground(7);
                printdirection("                                             NOMBRE D'ENFANTS D'UNE FAMILLE                                             ","right",1,4,5);
                decalrectangle(3);
                 textcolor(15);
                textbackground(7);
                if(mpp == NULL){
                        gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
                }
                else {
                gotoxy(4,12);
                printf(" <> LE NOM DE LA FAMILLE : ");gotoxy(4,12);
                textcolor(0);
                textbackground(15);
                gotoxy(36,12);
                ch20 fami;
                scanf("%s", fami);
                int i = nbenfnomfam(mpp , fami);
                if ( i >= 0)
                {
                    gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("Le nombre d'enfants de la famille est : %d\n",nbenfnomfam(mpp , fami));
                }
                else if (i < 0)
                {
                    gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("Cette famille n'existe pas \n");
                }
                }
                 textbackground(15);
                textcolor(0);
                gotoxy(40,30);
                system("pause");
                break;
                case 5:
                system("cls");
                textcolor(0);
                textbackground(7);
                printdirection("                                             AJOUT D'UN NOUVEAU NE A UNE FAMILLE                                       ","right",1,4,5);
                decalrectangle(3);
                 textcolor(15);
                textbackground(7);
                if(mpp == NULL){
                    gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
                }
                else {
                ch20 fam, nom,sexee;
                gotoxy(4,11);
                printf("<> NOM DE LA FAMILLE QUI A EU UN NOUVEAU N%c : ",144);
                textcolor(0);
                textbackground(15);
                gotoxy(65,11);
                scanf("%s", fam);
                textcolor(15);
                textbackground(7);
                gotoxy(4,13);
                printf("<> NOM DU NOUVEAU NE n%c : ",144);
                textcolor(0);
                textbackground(15);
                gotoxy(65,13);
                scanf("%s", nom);
                textcolor(15);
                textbackground(7);
                gotoxy(4,15);
                printf("<> SEXE DU NOUVEAU N%c (H/F) : ",144);
                textcolor(0);
                textbackground(15);
                gotoxy(65,15);
                scanf("%s", sexee);
                naissanceTrie(mpp, fam, nom, sexee[0]);
                }
                textbackground(15);
                textcolor(0);
                gotoxy(40,30);
                system("pause");
                break;
                case 6:
                   system("cls");
                   textcolor(0);
                textbackground(7);
                printdirection("                                          ADRESSE D'UNE FAMILLE POSSEDANT LA VOITURE VOLEE                              ","right",1,4,5);
                decalrectangle(3);
                 textcolor(15);
                textbackground(7);
                if(mpp == NULL){
                        gotoxy(40,19);
                    textbackground(0);
                    textcolor(15);
                    printf("La liste de population est vide ! \n");
                }
                else{
                 ch20 number;
                 gotoxy(4,10);
                printf("<> MATRICULE DE LA VOITURE VOL%cE : \n",144);
                gotoxy(50,10);
                textbackground(15);
                textcolor(0);
                scanf("%s",number);
                RechFamVoit1(mpp, number);
                }
                textbackground(15);
                textcolor(0);
                gotoxy(40,30);
                system("pause");
                break;

                 case 7:
                 system("cls");
                 system("mode con lines=70 cols=150");
                 textcolor(0);
                textbackground(7);
                printdirection("                                                              AFFICHAGE DE LA LISTE DE POPULATION                                                     \n","right",1,4,5);
                afficher1(mpp);
                printf("\n");
                gotoxy(70,120);
                system("pause");
                break;
                 case 8:
                   goto deb; // cas de cliquer sur exit
                   break;
             }
           goto men2;
           break;


               case 3:
                goto fin; // cas de cliquer sur exit (fin du programme)
                break;



         goto deb;


    //affichage de fin de programme
fin: fin();
    }
}




