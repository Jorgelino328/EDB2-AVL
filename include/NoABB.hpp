#ifndef NO_ABB_HPP
#define NO_ABB_HPP

class NoABB {
public:
    int dado;
    int altura;
    NoABB* esquerda;
    NoABB* direita;
    /**
    * @brief Construtor da classe NoABB.
    *
    * @param valor O valor a ser armazenado no nó.
    * @param altura A altura do nó.
    */
    NoABB(int valor, int altura);
};

#endif
