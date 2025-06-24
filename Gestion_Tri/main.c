#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
============================================================
|  GESTION D'INSERTIONS DANS TABLEAU                       |
|  Auteur : FOTSI TAKAM Harel Franck                       |
|  Encadrant : M. GUIFO                                   |
|  Annee : 2024-2025                                       |
|  Description : TP sur l'insertion et le tri de tableaux   |
============================================================
*/

#define MAX 100

int tableau[MAX] = {3, 7, 12, 18, 22, 25, 29, 33, 37, 40};
int tableau1[MAX];
int taille = 10;
int taille1 = 0;

/* Affiche l'entete du TP */
void Entete()
{
    system("cls");
    printf("|=====================================================================|\n");
    printf("|                GESTION D'INSERTIONS DANS TABLEAU                    |\n");
    printf("|                                                                     |\n");
    printf("| Presente par                                          Dirige par    |\n");
    printf("| FOTSI TAKAM Harel Franck                              M. GUIFO       |\n");
    printf("|                                                                     |\n");
    printf("|ING 1                                                  2024-2025      |\n");
    printf("|=====================================================================|\n");
}

/* Affiche le contenu d'un tableau */
void afficherTableau(int tab[], int taille)
{
    printf("Tableau : ");
    for (int i = 0; i < taille; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

/* Saisie d'un tableau non trie */
void SaisirValeurs()
{
    int n = -1, valeur;
    taille1 = 0;
    Entete();
    do
    {
        printf("Combien de valeurs voulez-vous entrer ? (max %d) : ", MAX);
        if (scanf("%d", &n) != 1)
        {
            printf("Entree invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n')
                ;
            n = -1;
            continue;
        }
        if (n < 1 || n > MAX)
        {
            printf("Nombre invalide.\n");
        }
    } while (n < 1 || n > MAX);
    for (int i = 0; i < n; i++)
    {
        printf("Valeur %d : ", i + 1);
        while (scanf("%d", &valeur) != 1)
        {
            printf("Entree invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n')
                ;
        }
        tableau1[taille1++] = valeur;
    }
    printf("Saisie terminee.\n");
}

/* Genere un tableau aleatoire */
void GenererTableauAleatoire()
{
    int n = -1;
    taille1 = 0;
    Entete();
    srand((unsigned int)time(NULL));
    do
    {
        printf("Combien de valeurs voulez-vous generer ? (max %d) : ", MAX);
        if (scanf("%d", &n) != 1)
        {
            printf("Entree invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n')
                ;
            n = -1;
            continue;
        }
        if (n < 1 || n > MAX)
        {
            printf("Nombre invalide.\n");
        }
    } while (n < 1 || n > MAX);
    for (int i = 0; i < n; i++)
    {
        tableau1[taille1++] = rand() % 100;
    }
    printf("Tableau aleatoire genere :\n");
    afficherTableau(tableau1, taille1);
}

/* Sauvegarde le tableau saisi dans un fichier texte */
void SauvegarderTableau()
{
    char nomFichier[100];
    printf("Nom du fichier pour sauvegarder (ex: tableau.txt) : ");
    scanf("%s", nomFichier);
    FILE *f = fopen(nomFichier, "w");
    if (!f)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    fprintf(f, "%d\n", taille1);
    for (int i = 0; i < taille1; i++)
    {
        fprintf(f, "%d ", tableau1[i]);
    }
    fclose(f);
    printf("Tableau sauvegarde dans %s\n", nomFichier);
}

/* Charge un tableau depuis un fichier texte */
void ChargerTableau()
{
    char nomFichier[100];
    printf("Nom du fichier a charger (ex: tableau.txt) : ");
    scanf("%s", nomFichier);
    FILE *f = fopen(nomFichier, "r");
    if (!f)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    fscanf(f, "%d", &taille1);
    if (taille1 < 1 || taille1 > MAX)
    {
        printf("Fichier corrompu ou taille invalide.\n");
        fclose(f);
        taille1 = 0;
        return;
    }
    for (int i = 0; i < taille1; i++)
    {
        fscanf(f, "%d", &tableau1[i]);
    }
    fclose(f);
    printf("Tableau charge depuis %s :\n", nomFichier);
    afficherTableau(tableau1, taille1);
}

/* Insere une valeur dans un tableau trie */
void insererDansTableauTrie(int tab[], int *taille, int valeur)
{
    int i = *taille - 1;
    while (i >= 0 && tab[i] > valeur)
    {
        tab[i + 1] = tab[i];
        i--;
    }
    tab[i + 1] = valeur;
    (*taille)++;
}

/* Trie un tableau par insertion */
void trierTableau(int tab[], int taille)
{
    for (int i = 1; i < taille; i++)
    {
        int val = tab[i];
        int j = i - 1;
        while (j >= 0 && tab[j] > val)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = val;
    }
}

/* Insertion dans un tableau trie */
void InsertionTableauTrie()
{
    int valeur;
    trierTableau(tableau, taille);
    Entete();
    printf("\nEntrez la valeur a inserer dans le tableau trie : ");
    scanf("%d", &valeur);
    insererDansTableauTrie(tableau, &taille, valeur);
    printf("Tableau apres insertion :\n");
    afficherTableau(tableau, taille);
}

/* Partitionne et insere avec un pivot */
void InsertionAvecPivot()
{
    int pivot;
    int resultat[MAX], tailleResultat = 0;
    int gauche[MAX], droite[MAX], tailleG = 0, tailleD = 0;
    Entete();
    printf("\nEntrez la valeur du pivot : ");
    scanf("%d", &pivot);
    for (int i = 0; i < taille1; i++)
    {
        if (tableau1[i] < pivot)
            gauche[tailleG++] = tableau1[i];
        else if (tableau1[i] > pivot)
            droite[tailleD++] = tableau1[i];
    }
    for (int i = 0; i < tailleG; i++)
        insererDansTableauTrie(resultat, &tailleResultat, gauche[i]);
    insererDansTableauTrie(resultat, &tailleResultat, pivot);
    for (int i = 0; i < tailleD; i++)
        insererDansTableauTrie(resultat, &tailleResultat, droite[i]);
    printf("Tableau apres partition et insertion :\n");
    afficherTableau(resultat, tailleResultat);
}

/* Echange deux entiers */
void echanger(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition pour quicksort */
int partition(int tab[], int debut, int fin)
{
    int pivot = tab[fin];
    int i = debut - 1;
    for (int j = debut; j < fin; j++)
    {
        if (tab[j] <= pivot)
        {
            i++;
            echanger(&tab[i], &tab[j]);
        }
    }
    echanger(&tab[i + 1], &tab[fin]);
    return i + 1;
}

/* Tri rapide (quicksort) recursif */
void quicksort(int tab[], int debut, int fin)
{
    if (debut < fin)
    {
        int p = partition(tab, debut, fin);
        quicksort(tab, debut, p - 1);
        quicksort(tab, p + 1, fin);
    }
}

/* Trie le tableau saisi par l'utilisateur avec quicksort */
void TriRapideTableau()
{
    if (taille1 == 0)
    {
        printf("Aucun tableau saisi a trier.\n");
        return;
    }
    int copie[MAX];
    for (int i = 0; i < taille1; i++)
        copie[i] = tableau1[i];
    quicksort(copie, 0, taille1 - 1);
    printf("Tableau trie par tri rapide (quicksort) :\n");
    afficherTableau(copie, taille1);
}

/* Menu principal du programme */
void Menu()
{
    int Choix;
    char rep = 'o';
    do
    {
        Entete();
        printf("-----------------------------------------------\n");
        printf("|              MENU PRINCIPAL                 |\n");
        printf("|                                             |\n");
        printf("|1. Saisir un tableau non trie                |\n");
        printf("|2. Insertion dans un tableau trie            |\n");
        printf("|3. Tri et insertion avec Pivot               |\n");
        printf("|4. Afficher les tableaux actuels             |\n");
        printf("|5. Tri rapide (quicksort) du tableau saisi   |\n");
        printf("|6. Generer un tableau aleatoire              |\n");
        printf("|7. Sauvegarder le tableau saisi              |\n");
        printf("|8. Charger un tableau depuis un fichier      |\n");
        printf("|9. Quitter                                   |\n");
        printf("-----------------------------------------------\n");
        printf("Entrez Votre Choix : ");
        if (scanf("%d", &Choix) != 1)
        {
            printf("Entree invalide.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (Choix)
        {
        case 1:
            SaisirValeurs();
            break;
        case 2:
            InsertionTableauTrie();
            break;
        case 3:
            InsertionAvecPivot();
            break;
        case 4:
            Entete();
            printf("Tableau trie predefini :\n");
            afficherTableau(tableau, taille);
            printf("Tableau saisi par l'utilisateur :\n");
            afficherTableau(tableau1, taille1);
            break;
        case 5:
            TriRapideTableau();
            break;
        case 6:
            GenererTableauAleatoire();
            break;
        case 7:
            SauvegarderTableau();
            break;
        case 8:
            ChargerTableau();
            break;
        case 9:
            printf("Au revoir !\n");
            exit(0);
            break;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
        printf("\nVoulez-vous revenir au menu ? (o/n) : ");
        scanf(" %c", &rep);
    } while (rep == 'o' || rep == 'O');
}

int main()
{
    Menu();
    return 0;
}
