#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colone.h"

#define N 5
#define REALOC_SIZE 256
#define ASC 0
#define DESC 1


Column *create_column(Enum_type type, char *title) {
  Column *nouveau_col = (Column *)malloc(sizeof(Column));
  if (nouveau_col == NULL) {
    fprintf(stderr, "Erreur memoire Col \n");
  }
  nouveau_col->title = strdup(title);
  if (nouveau_col->title == NULL) {
    fprintf(stderr, "Erreur memoire Col \n");
    free(nouveau_col);
  }
  nouveau_col->size = 0;
  nouveau_col->max_size = 0;
  nouveau_col->column_type = type;
  nouveau_col->data = NULL;
  nouveau_col->index = NULL;
  return nouveau_col;
}

int insert_value(Column *col, void *value) {
  if (col->size == col->max_size) {
    col->max_size += REALOC_SIZE;
    if (col->data == NULL) {
      col->data = (Col_type **)malloc(col->max_size * sizeof(Col_type *));
    } else {
      col->data =
          (Col_type **)realloc(col->data, col->max_size * sizeof(Col_type *));
    }
    if (col->data == NULL) {
      fprintf(stderr, "Erreur memoire Col \n");
      exit(EXIT_FAILURE);
    }
  }

  switch (col->column_type) {
  case UINT:
    col->data[col->size] = (Col_type *)malloc(sizeof(unsigned int));
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size]->uint_value = *((unsigned int *)value);
    }
    break;
  case INT:
    col->data[col->size] = (Col_type *)malloc(sizeof(int));
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size]->int_value = *((int *)value);
    }
    break;
  case CHAR:
    col->data[col->size] = (Col_type *)malloc(sizeof(char));
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size]->char_value = *((char *)value);
    }
    break;
  case FLOAT:
    col->data[col->size] = (Col_type *)malloc(sizeof(float));
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size]->float_value = *((float *)value);
    }
    break;
    ;
  case DOUBLE:
    col->data[col->size] = (Col_type *)malloc(sizeof(double));
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size]->double_value = *((double *)value);
    }
    break;
  case STRING:
    if (value == NULL) {
      col->data[col->size] = NULL;
    } else {
      col->data[col->size] = (Col_type *)malloc(sizeof(char *));
      if (col->data[col->size] == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la chaîne de caractères\n");
        exit(EXIT_FAILURE);
      }
      col->data[col->size]->string_value = (char *)malloc(strlen((char *)value) + 1);
      if (col->data[col->size]->string_value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la chaîne de caractères\n");
        exit(EXIT_FAILURE);
      }
      strcpy(col->data[col->size]->string_value, (char *)value);
    }
    break;

  case STRUCTURE:
    break;
  default:
    fprintf(stderr, "Type de colonne non pris en charge\n");
    exit(EXIT_FAILURE);
  }
  col->size++;
  return 1;
}




void delete_column(Column **col) {
  if (col != NULL && *col != NULL) {
    free((*col)->title);
    if ((*col)->data != NULL) {
      for (unsigned int i = 0; i < (*col)->size; i++) {
        free((*col)->data[i]);
      }
      free((*col)->data);
    }
    free((*col)->index);
    free(*col);
    *col = NULL;
  }
}


void convert_value(Column *col, unsigned long long int i, char *str, int size) {
    if (i >= col->size) {
        fprintf(stderr, "Erreur : Indexation invalide\n");
        return;
    }
    switch (col->column_type) {
    case UINT:
        snprintf(str, size, "%u", *((unsigned int*)(col->data[i])));
        break;
    case INT:
        snprintf(str, size, "%d", *((int*)(col->data[i])));
        break;
    case CHAR:
        snprintf(str, size, "%c", *((char*)(col->data[i])));
        break;
    case FLOAT:
        snprintf(str, size, "%f", *((float*)(col->data[i])));
        break;
    case DOUBLE:
        snprintf(str, size, "%lf", *((double*)(col->data[i])));
        break;
    case STRING:
        strncpy(str, *((char**)(col->data[i])), size);
        str[size - 1] = '\0';
        break;
    case STRUCTURE:
        break;
    default:
        fprintf(stderr, "Erreur : Type de colonne non pris en charge\n");
        break;
    }
}





void print_col(Column *col) {
  if (col == NULL) {
    fprintf(stderr, "Erreur : Colonne invalide\n");
    return;
  }
  char str[256];
  for (unsigned int i = 0; i < col->size; ++i) {
    printf("[%d] ", i);
    if (col->data[i] == NULL) {
      printf("NULL\n");
      continue;
    }
    convert_value(col, i, str, sizeof(str));
    printf("%s\n", str);
  }
}


