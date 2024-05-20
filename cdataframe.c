#include "colone.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Cdataframe *create_cdataframe(Enum_type *cdftype) {
  Cdataframe *nouveau_cdataframe = (Cdataframe *)malloc(sizeof(Cdataframe));
  if (nouveau_cdataframe == NULL) {
    fprintf(stderr, "Erreur d'allocation\n");
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




void delete_column_cdf(Cdataframe *cdf, char *nom_colonne) {
  if (cdf == NULL || nom_colonne == NULL) {
    fprintf(stderr, "Erreur : CDataframe\n");
    return;
  }

  lnode *actu = cdf->head;
  while (actu != NULL) {
    Column *col = (Column *)actu->data;
    if (col != NULL && col->title != NULL &&
        strcmp(col->title, nom_colonne) == 0) {
      if (actu->prev != NULL) {
        actu->prev->next = actu->next;
      } else {
        cdf->head = actu->next;
      }
      if (actu->next != NULL) {
        actu->next->prev = actu->prev;
      } else {
        cdf->tail = actu->prev;
      }
      delete_column(&col);
      free(actu);
      return;
    }
    actu = actu->next;
  }
  fprintf(stderr, "Erreur CDataframe\n");
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




void remplir_cdataframe_saisie_utilisateur(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }

  int nombre_colonnes;
  printf("Entrez le nombre de colonnes : ");
  scanf("%d", &nombre_colonnes);

  for (int i = 0; i < nombre_colonnes; ++i) {
    char titre_colonne[100];
    printf("Entrez le nom de la colonne %d : ", i + 1);
    scanf("%s", titre_colonne);

    Column *nouvelle_colonne = create_column(STRING, titre_colonne);
    if (nouvelle_colonne == NULL) {
      fprintf(stderr, "Erreur lors de la création de la colonne %s\n",
              titre_colonne);
      return;
    }

    lnode *nouveau_noeud = lst_create_lnode(nouvelle_colonne);
    if (nouveau_noeud == NULL) {
      fprintf(stderr, "Erreur lors de la création du nouveau noeud\n");
      delete_column(&nouvelle_colonne);
      return;
    }
    lst_insert_tail(cdf, nouveau_noeud);
  }



  
  int nombre_valeurs;
  printf("Entrez le nombre de valeurs pour chaque colonne : ");
  scanf("%d", &nombre_valeurs);

  lnode *actuel = cdf->head;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL) {
      printf("Remplissage de la colonne %s\n", colonne->title);
      for (int i = 0; i < nombre_valeurs; ++i) {
        char valeur[100];
        printf("Entrez la valeur %d pour la colonne %s : ", i + 1,
               colonne->title);
        scanf("%s", valeur);
        insert_value(colonne, valeur);
      }
    }
    actuel = actuel->next;
  }
}




void remplir_cdataframe_en_dur(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }

  Column *colonne_noms = create_column(STRING, "Noms");
  insert_value(colonne_noms, "Alice");
  insert_value(colonne_noms, "Bob");
  insert_value(colonne_noms, "Charlie");
  lst_insert_tail(cdf, lst_create_lnode(colonne_noms));

  Column *colonne_ages = create_column(INT, "Ages");
  insert_value(colonne_ages, &(int){25});
  insert_value(colonne_ages, &(int){30});
  insert_value(colonne_ages, &(int){40});
  lst_insert_tail(cdf, lst_create_lnode(colonne_ages));

  Column *colonne_salaires = create_column(FLOAT, "Salaires");
  insert_value(colonne_salaires, &(float){2500.50});
  insert_value(colonne_salaires, &(float){3500.75});
  insert_value(colonne_salaires, &(float){4500.90});
  lst_insert_tail(cdf, lst_create_lnode(colonne_salaires));
}




void afficher_cdataframe(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }
  lnode *actuel = cdf->head;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL) {
      printf("Colonne : %s\n", colonne->title);
      print_col(colonne);
      printf("\n");
    }
    actuel = actuel->next;
  }
}




void print_ligne(Cdataframe *cdf, int debut, int fin) {
  int max_rows = 0;
  lnode *actuel = cdf->head;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL && colonne->size > max_rows) {
      max_rows = colonne->size;
    }
    actuel = actuel->next;
  }

  if (fin >= max_rows) {
    fin = max_rows - 1;
  }



  
  printf("Affichage des lignes de %d à %d :\n", debut, fin);
  for (int i = debut; i <= fin; ++i) {
    printf("[%d] ", i);
    actuel = cdf->head;
    while (actuel != NULL) {
      Column *colonne = (Column *)actuel->data;
      if (colonne != NULL && i < colonne->size) {
        char str[256];
        convert_value(colonne, i, str, sizeof(str));
        printf("%s ", str);
      }
      actuel = actuel->next;
    }
    printf("\n");
  }
}




void affiche_partie_cdataframe_ligne(Cdataframe *cdf) {
  printf("Que voulez-vous afficher ?\n");
  printf("1- une ligne spécifique \n");
  printf("2- un intervale de ligne \n");
  printf("3- les 10 premiere ligne \n");

  printf("Selection : ");
  int selection;
  scanf("%d", &selection);

  switch (selection) {
  case 1: {
    int ligne;
    printf("Entrez le numero de la ligne : ");
    scanf("%d", &ligne);
    print_ligne(cdf, ligne, ligne);
    break;
  }
  case 2: {
    int debut, fin;
    printf("Entrez le debut de l'intervalle : ");
    scanf("%d", &debut);
    printf("Entrez la fin de l'intervalle : ");
    scanf("%d", &fin);
    print_ligne(cdf, debut, fin);
    break;
  }
  case 3: {
    print_ligne(cdf, 0, 9);
    break;
  }
  }
}




void affiche_partie_cdataframe_colone(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }

  printf("Que voulez-vous afficher ?\n");
  printf("1- une colonne spécifique\n");
  printf("2- les 10 premières colonnes\n");
  printf("3- les colonnes entre deux nombres\n");

  printf("Sélection : ");
  int selection;
  scanf("%d", &selection);

  switch (selection) {
  case 1: {
    char nom_colonne[100];
    printf("Entrez le nom de la colonne : ");
    scanf("%s", nom_colonne);

    lnode *actuel = cdf->head;
    while (actuel != NULL) {
      Column *colonne = (Column *)actuel->data;
      if (colonne != NULL && strcmp(colonne->title, nom_colonne) == 0) {
        printf("Colonne : %s\n", colonne->title);
        print_col(colonne);
        return;
      }
      actuel = actuel->next;
    }
    fprintf(stderr, "Erreur : Colonne introuvable\n");
    break;
  }
  case 2: {
    int col_index = 0;
    lnode *actuel = cdf->head;
    while (actuel != NULL && col_index < 10) {
      Column *colonne = (Column *)actuel->data;
      if (colonne != NULL) {
        printf("Colonne : %s\n", colonne->title);
        print_col(colonne);
        printf("\n");
      }
      actuel = actuel->next;
      col_index++;
    }
    break;
  }
  case 3: {
    int debut, fin;
    printf("Entrez le début de l'intervalle : ");
    scanf("%d", &debut);
    printf("Entrez la fin de l'intervalle : ");
    scanf("%d", &fin);

    if (debut < 0 || fin < debut) {
      fprintf(stderr, "Erreur : Intervalles invalides\n");
      return;
    }

    lnode *actuel = cdf->head;
    int col_index = 0;
    while (actuel != NULL && col_index <= fin) {
      if (col_index >= debut) {
        Column *colonne = (Column *)actuel->data;
        if (colonne != NULL) {
          printf("Colonne : %s\n", colonne->title);
          print_col(colonne);
          printf("\n");
        }
      }
      actuel = actuel->next;
      col_index++;
    }
    break;
  }
  default:
    fprintf(stderr, "Erreur : Option invalide\n");
    break;
  }
}




void ajouter_ligne(Cdataframe *cdf, char **valeurs) {
  if (cdf == NULL || valeurs == NULL) {
    fprintf(stderr, "Erreur : CDataframe ou valeurs invalides\n");
    return;
  }

  lnode *actuel = cdf->head;
  int col_index = 0;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL) {
      if (col_index >= 0 && col_index < get_cdataframe_cols_size(cdf)) {
        insert_value(colonne, valeurs[col_index]);
      } else {
        fprintf(stderr, "Erreur : Nombre de valeurs invalide\n");
        return;
      }
    }
    actuel = actuel->next;
    col_index++;
  }
}

void ajouter_ligne_cdataframe(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }

  lnode *actuel = cdf->head;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL) {
      printf("Entrez une valeur pour la colonne \"%s\": ", colonne->title);
      switch (colonne->column_type) {
      case STRING: {
        char *string_val = (char *)malloc(256 * sizeof(char));
        if (string_val == NULL) {
          fprintf(stderr, "Erreur d'allocation mémoire\n");
          return;
        }
        scanf("%s", string_val);
        insert_value(colonne, string_val);
        break;
      }
      case STRUCTURE:
        fprintf(stderr,
                "Impossible de saisir des valeurs pour ce type de colonne.\n");
        break;
      case UINT: {
        unsigned int uint_val;
        scanf("%u", &uint_val);
        insert_value(colonne, &uint_val);
        break;
      }
      case INT: {
        int int_val;
        scanf("%d", &int_val);
        insert_value(colonne, &int_val);
        break;
      }
      case CHAR: {
        char char_val;
        scanf(" %c", &char_val);
        insert_value(colonne, &char_val);
        break;
      }
      case FLOAT: {
        float float_val;
        scanf("%f", &float_val);
        insert_value(colonne, &float_val);
        break;
      }
      case DOUBLE: {
        double double_val;
        scanf("%lf", &double_val);
        insert_value(colonne, &double_val);
        break;
      }
      }
    }
    actuel = actuel->next;
  }
}




void suprimer_ligne_cdataframe(Cdataframe *cdf) {
  if (cdf == NULL) {
    fprintf(stderr, "Erreur : CDataframe invalide\n");
    return;
  }
  int numero_ligne;
  printf("Entrez le numéro de la ligne à supprimer : ");
  scanf("%d", &numero_ligne);

  if (numero_ligne < 0) {
    fprintf(stderr, "Erreur : numéro de ligne invalide\n");
    return;
  }

  lnode *actuel = cdf->head;
  while (actuel != NULL) {
    Column *colonne = (Column *)actuel->data;
    if (colonne != NULL && numero_ligne < colonne->size) {
      free(colonne->data[numero_ligne]);
      for (int i = numero_ligne; i < colonne->size - 1; i++) {
        colonne->data[i] = colonne->data[i + 1];
      }
      colonne->size--;
    }
    if (numero_ligne < colonne->size - 1) {
      free(colonne->data[colonne->size - 1]);
      colonne->data[colonne->size - 1] = NULL;
      colonne->size--;
    }
    actuel = actuel->next;
  }
}



void ajouter_colonne_cdataframe(Cdataframe *cdf) {
    if (cdf == NULL) {
        fprintf(stderr, "Erreur : CDataframe invalide\n");
        return;
    }

    char nom_colonne[100];
    printf("Entrez le nom de la colonne : ");
    scanf("%s", nom_colonne);

    printf("Choisissez le type de données pour la colonne %s :\n", nom_colonne);
    printf("1. Entier non signé\n");
    printf("2. Entier signé\n");
    printf("3. Caractère\n");
    printf("4. Flottant\n");
    printf("5. Double\n");
    printf("6. Chaîne de caractères\n");
    printf("Votre choix : ");

    int choix_type;
    scanf("%d", &choix_type);

    Enum_type type_colonne;
    switch (choix_type) {
        case 1:
            type_colonne = UINT;
            break;
        case 2:
            type_colonne = INT;
            break;
        case 3:
            type_colonne = CHAR;
            break;
        case 4:
            type_colonne = FLOAT;
            break;
        case 5:
            type_colonne = DOUBLE;
            break;
        case 6:
            type_colonne = STRING;
            break;
        default:
            fprintf(stderr, "Type invalide\n");
            return;
    }

    int nombre_valeurs;
    printf("\nEntrez le nombre de valeurs pour la colonne %s : ", nom_colonne);
    scanf("%d", &nombre_valeurs);

    Column *nouvelle_colonne = create_column(type_colonne, nom_colonne);
    if (nouvelle_colonne == NULL) {
        fprintf(stderr, "Erreur lors de la création de la colonne %s\n", nom_colonne);
        return;
    }

    lnode *nouveau_noeud = lst_create_lnode(nouvelle_colonne);
    if (nouveau_noeud == NULL) {
        fprintf(stderr, "Erreur lors de la création du nouveau nœud\n");
        delete_column(&nouvelle_colonne);
        return;
    }

    lst_insert_tail(cdf, nouveau_noeud);

    char reponse;
    printf("\nVoulez-vous saisir des valeurs pour cette colonne ? (o/n) : ");
    scanf(" %c", &reponse);

    if (reponse == 'o' || reponse == 'O') {
        for (int i = 0; i < nombre_valeurs; ++i) {
            printf("\nEntrez la valeur %d pour la colonne %s : ", i + 1, nom_colonne);
            switch (type_colonne) {
                case UINT: {
                    unsigned int valeur;
                    scanf("%u", &valeur);
                    insert_value(nouvelle_colonne, &valeur);
                    break;
                }
                case INT: {
                    int valeur;
                    scanf("%d", &valeur);
                    insert_value(nouvelle_colonne, &valeur);
                    break;
                }
                case CHAR: {
                    char valeur;
                    scanf(" %c", &valeur);
                    insert_value(nouvelle_colonne, &valeur);
                    break;
                }
                case FLOAT: {
                    float valeur;
                    scanf("%f", &valeur);
                    insert_value(nouvelle_colonne, &valeur);
                    break;
                }
                case DOUBLE: {
                    double valeur;
                    scanf("%lf", &valeur);
                    insert_value(nouvelle_colonne, &valeur);
                    break;
                }
                case STRING: {
                    char valeur[256];
                    scanf("%s", valeur);
                    insert_value(nouvelle_colonne, valeur);
                    break;
                }
                default:
                    fprintf(stderr, "Type de colonne invalide\n");
                    return;
            }
        }
    }
}




void supprimer_colonne_cadataframe(Cdataframe *cdf, char *nom_colonne) {
    if (cdf == NULL || nom_colonne == NULL) {
        fprintf(stderr, "Erreur : CDataframe ou nom de colonne invalide\n");
        return;
    }

    lnode *current = cdf->head;
    while (current != NULL) {
        Column *col = (Column *)current->data;
        if (col != NULL && col->title != NULL && strcmp(col->title, nom_colonne) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                cdf->head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                cdf->tail = current->prev;
            }
            delete_column(&col);
            free(current);
            return;
        }
        current = current->next;
    }
    fprintf(stderr, "Erreur : Colonne introuvable dans le CDataframe\n");
}


void renomme_colonne_cdataframe(Cdataframe *cdf, char *ancien_nom, char *nouveau_nom) {
    if (cdf == NULL || ancien_nom == NULL) {
        fprintf(stderr, "Erreur : CDataframe ou nom de colonne invalide\n");
        return;
    }

    if (nouveau_nom == NULL) {
        fprintf(stderr, "Erreur : Nouveau nom de colonne invalide\n");
        return;
    }

    lnode *current = cdf->head;
    while (current != NULL) {
        Column *col = (Column *)current->data;
        if (col != NULL && col->title != NULL && strcmp(col->title, ancien_nom) == 0) {
            free(col->title);
            col->title = strdup(nouveau_nom);
            if (col->title == NULL) {
                fprintf(stderr, "Erreur d'allocation lors du renommage du titre de la colonne\n");
                return;
            }
            return;
        }
        current = current->next;
    }
    fprintf(stderr, "Erreur : Colonne introuvable dans le CDataframe\n");
}


int valeur_existante_cdataframe(Cdataframe *cdf, void *valeur) {
    if (cdf == NULL || valeur == NULL) {
        fprintf(stderr, "Erreur : CDataframe ou valeur invalide\n");
        return 0;
    }

    lnode *current = cdf->head;
    while (current != NULL) {
        Column *col = (Column *)current->data;
        if (col != NULL && col->data != NULL) {
            for (unsigned int i = 0; i < col->size; i++) {
                switch (col->column_type) {
                    case UINT:
                        if (*((unsigned int *)col->data[i]) == *((unsigned int *)valeur))
                            return 1;
                        break;
                    case INT:
                        if (*((int *)col->data[i]) == *((int *)valeur))
                            return 1;
                        break;
                    case CHAR:
                        if (*((char *)col->data[i]) == *((char *)valeur))
                            return 1;
                        break;
                    case FLOAT:
                        if (*((float *)col->data[i]) == *((float *)valeur))
                            return 1;
                        break;
                    case DOUBLE:
                        if (*((double *)col->data[i]) == *((double *)valeur))
                            return 1;
                        break;
                    case STRING:
                        if (strcmp((char *)col->data[i], (char *)valeur) == 0)
                            return 1;
                        break;
                    default:
                        fprintf(stderr, "Type de colonne non pris en charge\n");
                        return 0;
                }
            }
        }
        current = current->next;
    }
    return 0;
}


void acces_remplace_valeur_cellule(Cdataframe *cdf, int ligne, int colonne, void *nouvelle_valeur) {
    if (cdf == NULL) {
        fprintf(stderr, "Erreur : CDataframe invalide\n");
        return;
    }

    lnode *current = cdf->head;
    int current_colonne = 0;
    while (current != NULL && current_colonne <= colonne) {
        if (current_colonne == colonne) {
            Column *col = (Column *)current->data;
            if (col != NULL && ligne < col->size) {
                switch (col->column_type) {
                    case UINT:
                        *((unsigned int *)col->data[ligne]) = *((unsigned int *)nouvelle_valeur);
                        break;
                    case INT:
                        *((int *)col->data[ligne]) = *((int *)nouvelle_valeur);
                        break;
                    case CHAR:
                        *((char *)col->data[ligne]) = *((char *)nouvelle_valeur);
                        break;
                    case FLOAT:
                        *((float *)col->data[ligne]) = *((float *)nouvelle_valeur);
                        break;
                    case DOUBLE:
                        *((double *)col->data[ligne]) = *((double *)nouvelle_valeur);
                        break;
                    case STRING:
                        free(col->data[ligne]);
                        col->data[ligne] = strdup((char *)nouvelle_valeur);
                        break;
                    default:
                        fprintf(stderr, "Type de colonne non pris en charge\n");
                        break;
                }
            } else {
                fprintf(stderr, "Erreur : Indice de ligne invalide\n");
            }
            return;
        }
        current = current->next;
        current_colonne++;
    }
    fprintf(stderr, "Erreur : Indice de colonne invalide\n");
}


void afficher_noms_colonnes(Cdataframe *cdf) {
    if (cdf == NULL) {
        fprintf(stderr, "Erreur : CDataframe invalide\n");
        return;
    }

    lnode *current = cdf->head;
    while (current != NULL) {
        Column *colonne = (Column *)current->data;
        if (colonne != NULL) {
            printf("%s\n", colonne->title);
        }
        current = current->next;
    }
}


int nombre_de_lignes(Cdataframe *cdf) {
    int count = 0;
    lnode *current = cdf->head;
    while (current != NULL) {
        Column *colonne = (Column *)current->data;
        if (colonne != NULL) {
            count = (colonne->size > count) ? colonne->size : count;
        }
        current = current->next;
    }
    return count;
}


int nombre_de_colonnes(Cdataframe *cdf) {
    int count = 0;
    lnode *current = cdf->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int nombre_de_cellules_egal_x(Cdataframe *cdf, void *x) {
    int count = 0;
    lnode *current = cdf->head;
    while (current != NULL) {
        Column *colonne = (Column *)current->data;
        if (colonne != NULL) {
            for (unsigned int i = 0; i < colonne->size; i++) {
                if (colonne->data[i] != NULL && memcmp(colonne->data[i], x, sizeof(Col_type)) == 0) {
                    count++;
                }
            }
        }
        current = current->next;
    }
    return count;
}


int nombre_de_cellules_sup_x(Cdataframe *cdf, void *x) {
    int count = 0;
    lnode *current = cdf->head;
    while (current != NULL) {
        Column *colonne = (Column *)current->data;
        if (colonne != NULL) {
            for (unsigned int i = 0; i < colonne->size; i++) {
                if (colonne->data[i] != NULL && memcmp(colonne->data[i], x, sizeof(Col_type)) > 0) {
                    count++;
                }
            }
        }
        current = current->next;
    }
    return count;
}


int nombre_de_cellules_inf_x(Cdataframe *cdf, void *x) {
    int count = 0;
    lnode *current = cdf->head;
    while (current != NULL) {
        Column *colonne = (Column *)current->data;
        if (colonne != NULL) {
            for (unsigned int i = 0; i < colonne->size; i++) {
                if (colonne->data[i] != NULL && memcmp(colonne->data[i], x, sizeof(Col_type)) < 0) {
                    count++;
                }
            }
        }
        current = current->next;
    }
    return count;
}


Cdataframe* load_from_csv(char *file_name, Enum_type *dftype, int size) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    Cdataframe *cdf = (Cdataframe *)malloc(sizeof(Cdataframe));
    if (cdf == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le CDataframe.\n");
        fclose(file);
        return NULL;
    }
    cdf->head = NULL;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Column *colonne = (Column *)malloc(sizeof(Column));
        if (colonne == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour une colonne.\n");
            fclose(file);
            free(cdf);
            return NULL;
        }
        colonne->title = strtok(line, ",");
        colonne->data = (void **)malloc(size * sizeof(void *));
        colonne->size = size;

        lnode *node = (lnode *)malloc(sizeof(lnode));
        if (node == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour un nœud.\n");
            fclose(file);
            free(colonne);
            free(cdf);
            return NULL;
        }
        node->data = (void *)colonne;
        node->next = cdf->head;
        cdf->head = node;
    }
    fclose(file);

    return cdf;
}


void save_into_csv(Cdataframe *cdf, char *file_name) {
    if (cdf == NULL || file_name == NULL) {
        printf("Error: Invalid arguments\n");
        return;
    }
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", file_name);
        return;
    }
    lnode *current = cdf->head;
    while (current != NULL) {
        Column *col = (Column *)current->data;
        if (col != NULL) {
            fprintf(fp, "%s,", col->title);
            for (size_t i = 0; i < col->size; i++) {
                switch (col->column_type) {
                    case INT:
                        fprintf(fp, "%d", *((int *)(col->data[i])));
                        break;
                    case FLOAT:
                        fprintf(fp, "%f", *((float *)(col->data[i])));
                        break;
                    case DOUBLE:
                        fprintf(fp, "%lf", *((double *)(col->data[i])));
                        break;
                    case STRING:
                        fprintf(fp, "%s", (char *)(col->data[i]));
                        break;
                    default:
                        printf("Error: Unknown data type\n");
                        break;
                }
                if (i < col->size - 1) {
                    fprintf(fp, ",");
                }
            }
            fprintf(fp, "\n");
        }
        current = current->next;
    }
    fclose(fp);
}
