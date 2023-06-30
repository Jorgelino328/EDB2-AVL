#ifndef NO_ABB_HPP
#define NO_ABB_HPP

class NoABB {
public:
    int dado;
    int altura;
    NoABB* esquerda;
    NoABB* direita;
    NoABB(int valor, int altura);
};

#endif
