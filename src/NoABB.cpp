#include "NoABB.hpp"

NoABB::NoABB(int valor,int altura) {
    dado = valor; //<! Guarda o valor do número no nó 
    altura = altura; //<! Guarda a altura do nó
    esquerda = nullptr; //<! Guarda o nó filho esquerdo
    direita = nullptr; //<! Guarda o nó filho direito
}