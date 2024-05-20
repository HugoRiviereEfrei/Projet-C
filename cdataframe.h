#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "colone.h"
#include "list.h"

Cdataframe *create_cdataframe(Enum_type *cdftype);
void delete_cdataframe(Cdataframe **cdf);
void delete_column_cdf(Cdataframe *cdf, char *nom_colonne);
int get_cdataframe_cols_size(Cdataframe *cdf);
void remplir_cdataframe_saisie_utilisateur(Cdataframe *cdf);
void remplir_cdataframe_en_dur(Cdataframe *cdf);
void afficher_cdataframe(Cdataframe *cdf);
void print_ligne(Cdataframe *cdf, int debut, int fin);
void affiche_partie_cdataframe_ligne(Cdataframe *cdf);
void affiche_partie_cdataframe_colonne(Cdataframe *cdf);
void ajouter_ligne(Cdataframe *cdf, char **valeurs);
void ajouter_ligne_cdataframe(Cdataframe *cdf);
void supprimer_ligne_cdataframe(Cdataframe *cdf);
void ajouter_colonne_cdataframe(Cdataframe *cdf);
void supprimer_colonne_cdataframe(Cdataframe *cdf, char *nom_colonne);
void renommer_colonne_cdataframe(Cdataframe *cdf, char *ancien_nom, char *nouveau_nom);
int valeur_existante_cdataframe(Cdataframe *cdf, void *valeur);
void acces_remplace_valeur_cellule(Cdataframe *cdf, int ligne, int colonne, void *nouvelle_valeur);
void afficher_noms_colonnes(Cdataframe *cdf);
int nombre_de_lignes(Cdataframe *cdf);
int nombre_de_colonnes(Cdataframe *cdf);
int nombre_de_cellules_egal_x(Cdataframe *cdf, void *x);
int nombre_de_cellules_sup_x(Cdataframe *cdf, void *x);
int nombre_de_cellules_inf_x(Cdataframe *cdf, void *x);
Cdataframe *load_from_csv(char *file_name, Enum_type *dftype, int size);
void save_into_csv(Cdataframe *cdf, char *file_name);

#endif
