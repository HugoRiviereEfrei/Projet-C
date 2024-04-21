#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 5
#define REALOC_SIZE 256
#include "colone.h"



int main() {
    Column *my_col = create_column(INT, "My Column");
    int a = 7, c = 9;
    insert_value(my_col, &a);
    insert_value(my_col, NULL);
    insert_value(my_col, &c);

    print_col(my_col);
    delete_column(&my_col);
    return 0;
}