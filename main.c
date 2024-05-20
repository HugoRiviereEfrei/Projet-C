#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define REALOC_SIZE 256
#include "cdataframe.h"
#include "colone.h"
#include "list.h"

int main() {
  Cdataframe *cdf = NULL;
  int choix_menu;

  do {
    printf("\nMenu :\n");
    printf("1. Alimentation\n");
    printf("2. Affichage\n");
    printf("3. Opérations usuelles\n");
    printf("4. Analyse et statistiques\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix_menu);

    switch (choix_menu) {
    case 1: {
      printf("\n--- Alimentation ---\n");
      printf("1. Création d'un CDataframe vide\n");
      printf("2. Remplissage du CDataframe à partir de saisies utilisateurs\n");
      printf("3. Remplissage en dur du CDataframe\n");
      printf("Votre choix : ");
      int choix_alimentation;
      scanf("%d", &choix_alimentation);
      switch (choix_alimentation) {
      case 1:
        cdf = create_cdataframe(NULL);
        if (cdf == NULL) {
          printf("Erreur lors de la création du CDataframe.\n");
        } else {
          printf("CDataframe créé avec succès.\n");
        }
        break;
      case 2:
        if (cdf == NULL) {
          printf("Veuillez d'abord créer un CDataframe vide.\n");
        } else {
          remplir_cdataframe_saisie_utilisateur(cdf);
        }
        break;
      case 3:
        if (cdf == NULL) {
          printf("Veuillez d'abord créer un CDataframe vide.\n");
        } else {
          remplir_cdataframe_en_dur(cdf);
          printf("CDataframe rempli avec succès.\n");
        }
        break;
      default:
        printf("Choix invalide.\n");
      }
      break;
    }
    case 2: {
      printf("\n--- Affichage ---\n");
      printf("1. Afficher tout le CDataframe\n");
      printf("2. Afficher une partie des lignes du CDataframe selon une limite "
             "fournie par l'utilisateur\n");
      printf("3. Afficher une partie des colonnes du CDataframe selon une "
             "limite fournie par l'utilisateur\n");
      printf("Votre choix : ");
      int choix_affichage;
      scanf("%d", &choix_affichage);
      switch (choix_affichage) {
      case 1:
        if (cdf == NULL) {
          printf("Le CDataframe est vide.\n");
        } else {
          afficher_cdataframe(cdf);
        }
        break;
      case 2:
        if (cdf == NULL) {
          printf("Le CDataframe est vide.\n");
        } else {
          affiche_partie_cdataframe_ligne(cdf);
        }
        break;
      case 3:
        if (cdf == NULL) {
          printf("Le CDataframe est vide.\n");
        } else {
          affiche_partie_cdataframe_colone(cdf);
        }
        break;
      default:
        printf("Choix invalide.\n");
      }
      break;
    }
    case 3: {
      printf("\n--- Opérations usuelles ---\n");
      printf("1. Ajouter une ligne de valeurs au CDataframe\n");
      printf("2. Supprimer une ligne de valeurs du CDataframe\n");
      printf("3. Ajouter une colonne au CDataframe\n");
      printf("4. Supprimer une colonne du CDataframe\n");
      printf("5. Renommer le titre d'une colonne du CDataframe\n");
      printf("6. Vérifier l'existence d'une valeur (recherche) dans le "
             "CDataframe\n");
      printf("7. Accéder/remplacer la valeur se trouvant dans une cellule du "
             "CDataframe en utilisant son numéro de ligne et de colonne\n");
      printf("8. Afficher les noms des colonnes\n");
      printf("Votre choix : ");
      int choix_operations;
      scanf("%d", &choix_operations);
      switch (choix_operations) {
      case 1:
        ajouter_ligne_cdataframe(cdf);
        break;
      case 2:
        suprimer_ligne_cdataframe(cdf);
        break;
      case 3:
        ajouter_colonne_cdataframe(cdf);
        break;
      case 4:
        printf("Entrez le nom de la colonne à supprimer : ");
        char nom_colonne[50];
        scanf("%s", nom_colonne);
        supprimer_colonne_cadataframe(cdf, nom_colonne);
        break;
      case 5:
        printf("Entrez le nom de la colonne à renommer : ");
        char ancien_nom[50];
        scanf("%s", ancien_nom);
        printf("Entrez le nouveau nom de la colonne : ");
        char nouveau_nom[50];
        scanf("%s", nouveau_nom);
        renomme_colonne_cdataframe(cdf, ancien_nom, nouveau_nom);
        break;
      case 6:
        printf("Entrez la valeur à rechercher : ");
        int valeur;
        scanf("%d", &valeur);
        valeur_existante_cdataframe(cdf, &valeur);
        break;
      case 7:
        printf("Entrez le numéro de ligne : ");
        int ligne;
        scanf("%d", &ligne);
        printf("Entrez le numéro de colonne : ");
        int colonne;
        scanf("%d", &colonne);
        printf("Entrez la nouvelle valeur : ");
        int nouvelle_valeur;
        scanf("%d", &nouvelle_valeur);
        acces_remplace_valeur_cellule(cdf, ligne, colonne, &nouvelle_valeur);
        break;
      case 8:
        afficher_noms_colonnes(cdf);
        break;
      default:
        printf("Choix invalide.\n");
      }
      break;
    }
    case 4: {
      printf("\n--- Analyse et statistiques ---\n");
      printf("1. Afficher le nombre de lignes\n");
      printf("2. Afficher le nombre de colonnes\n");
      printf("3. Nombre de cellules égales à x (x donné en paramètre)\n");
      printf("4. Nombre de cellules contenant une valeur supérieure à x (x "
             "donné en paramètre)\n");
      printf("5. Nombre de cellules contenant une valeur inférieure à x (x "
             "donné en paramètre)\n");
      printf("Votre choix : ");
      int choix_analyse;
      scanf("%d", &choix_analyse);
      switch (choix_analyse) {
      case 1:
        printf("Nombre de lignes : %d\n", nombre_de_lignes(cdf));
        break;
      case 2:
        printf("Nombre de colonnes : %d\n", nombre_de_colonnes(cdf));
        break;
      case 3:
        printf("Entrez la valeur x : ");
        int x;
        scanf("%d", &x);
        printf("Nombre de cellules égales à %d : %d\n", x,
               nombre_de_cellules_egal_x(cdf, &x));
        break;
      case 4:
        printf("Entrez la valeur x : ");
        int val_sup;
        scanf("%d", &val_sup);
        printf("Nombre de cellules supérieures à %d : %d\n", val_sup,
               nombre_de_cellules_sup_x(cdf, &val_sup));
        break;
      case 5:
        printf("Entrez la valeur x : ");
        int val_inf;
        scanf("%d", &val_inf);
        printf("Nombre de cellules inférieures à %d : %d\n", val_inf,
               nombre_de_cellules_inf_x(cdf, &val_inf));
        break;
      default:
        printf("Choix invalide.\n");
      }
      break;
    }
    case 0:
      printf("Au revoir !\n");
      break;
    default:
      printf("Choix invalide.\n");
    }
  } while (choix_menu != 0);

  delete_cdataframe(&cdf);

  return 0;
}
