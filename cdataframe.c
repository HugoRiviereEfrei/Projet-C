#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colone.h"
#include "list.h"


Cdataframe *create_cdataframe(Enum_type *cdftype) {
    Cdataframe *nouveau_cdataframe = (Cdataframe *)malloc(sizeof(Cdataframe));
    if (nouveau_cdataframe == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nouveau dataframe\n");
        return NULL;
    }

    nouveau_cdataframe->head = NULL;
    nouveau_cdataframe->tail = NULL;

    return nouveau_cdataframe;
}

void delete_cdataframe(Cdataframe **cdf) {
    if (cdf != NULL && *cdf != NULL) {
        lst_delete_list(*cdf);
        *cdf = NULL;
    }
}


void supprimer_colonne(Cdataframe *cdf, char *nom_colonne) {
    if (cdf == NULL || nom_colonne == NULL) {
        fprintf(stderr, "Erreur : CDataframe ou nom de colonne invalide\n");
        return;
    }

    lnode *actu = cdf->head;
    while (actu != NULL) {
        Column *col = (Column *)actu->data;
        if (col != NULL && col->title != NULL && strcmp(col->title, nom_colonne) == 0) {
            if (actu->prev != NULL) {
                  actu->prev->next = actu->next;
            } else {
                cdf->head = current->next;
            }
            if (actu->next != NULL) {
                  actu->next->prev = current->prev;
            } else {
                cdf->tail = current->prev;
            }
            delete_column(&col);
            free(actu);
            return;
        }
          actu = current->next;
    }
    fprintf(stderr, "Erreur : Colonname '%s' non trouvé dans le CDataframe\n", nom_colonne);
}


int get_cdataframe_cols_size(Cdataframe *cdf) {
    if (cdf == NULL) {
        fprintf(stderr, "Erreur : CDataframe invalide\n");
        return -1;
    }

    int cpt = 0;
    lnode *actu = cdf->head;
    while (actu != NULL) {
        cpt++;
        actu = actu->next;
    }
    return cpt;
}