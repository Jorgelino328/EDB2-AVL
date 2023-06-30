#include "ArvoreBuscaBinaria.hpp"

int main(int argc, char *argv[])
{
    ArvoreBuscaBinaria abb; //<! Cria um novo objeto abb
    
    //Lê os arquivos inputados, executando seus respectivos comandos
    abb.lerArquivos(argv[1],argv[2]);

    return 0;
}
