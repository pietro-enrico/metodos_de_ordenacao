#include <windows.h>

#include "src/headers/menu.h"

int main() {
    // Configura o console do Windows para exibir e ler caracteres em UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    menuMain();
    return 0;
}