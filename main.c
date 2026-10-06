#include <stdlib.h>

#include "src/headers/menu.h"
#include "src/headers/array.h"

int main() {
    int *array = gerarArray(30, false, ALEATORIO);
    free(array);
    menuMain();
    return 0;
}