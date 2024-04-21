#ifndef COLUMN_H
#define COLUMN_H

typedef enum {
    NULLVAL = 1,
    UINT,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,
    STRUCTURE
} Enum_type;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char *string_value;
    void *struct_value;
} Col_type;

typedef struct column {
    char *title;
    unsigned int size;
    unsigned int max_size;
    Enum_type column_type;
    Col_type **data;
    unsigned long long int *index;
    int valid_index;
    int sort_dir;
} Column;

Column *create_column(Enum_type type, char *title);
int insert_value(Column *col, void *value);
void delete_column(Column **col);
void convert_value(Column *col, unsigned long long int i, char *str, int size);
void print_col(Column *col);

#endif