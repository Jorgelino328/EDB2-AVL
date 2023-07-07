#include "ArvoreBuscaBinaria.hpp"

//Construtor
ArvoreBuscaBinaria::ArvoreBuscaBinaria() {
    raiz = nullptr;
}

//Helpers e outras funções privadas
NoABB* ArvoreBuscaBinaria::inserirHelper(NoABB* no, int valor) {


    if (no == nullptr) {
        std::cout << valor << " adicionado" << std::endl;
        NoABB* newNode = new NoABB(valor, 1);
        newNode->esquerda = newNode->direita = nullptr;
        return newNode;
    }
    

    if (valor < no->dado){
        no->esquerda = inserirHelper(no->esquerda, valor);
        updateAltura(no->esquerda);
    }else if (valor > no->dado){
        no->direita = inserirHelper(no->direita, valor);
        updateAltura(no->direita);
    }else {
        std::cout << valor << " já está na árvore, não pode ser inserido" << std::endl;
        return no; // If the value already exists, return the current node.
    }
    
    updateAltura(no);

    int fatorBalanco = getAltura(no->esquerda) - getAltura(no->direita);

    // Left Case
    if (fatorBalanco > 1 && valor < no->esquerda->dado){
        std::cout << "Rotação Esquerda ("<<no->dado<<")" << std::endl;
        return rodarDireita(no);
    }
    // Right Case
    if (fatorBalanco < -1 && valor > no->direita->dado){
        std::cout << "Rotação Direita ("<<no->dado<<")" << std::endl;
        return rodarEsquerda(no);
    }
    // Left-Right Case
    if (fatorBalanco > 1 && valor > no->esquerda->dado) {
        std::cout << "Rotação Dupla Direita ("<<no->dado<<")" << std::endl;
        no->esquerda = rodarEsquerda(no->esquerda);
        return rodarDireita(no);
    }

    // Right-Left Case
    if (fatorBalanco < -1 && valor < no->direita->dado) {
        std::cout << "Rotação Dupla Esquerda("<<no<<")" << std::endl;
        no->direita = rodarDireita(no->direita);
        return rodarEsquerda(no);
    }

    return no;
}

NoABB* ArvoreBuscaBinaria::removerHelper(NoABB* no, int valor,int valorRemovido) {
    if (no == nullptr) {
        std::cout << valor << " não está na árvore, não pode ser removido" << std::endl;
        return nullptr;
    }

    if (valor < no->dado) {
        no->esquerda = removerHelper(no->esquerda, valor, valorRemovido);
    } else if (valor > no->dado) {
        no->direita = removerHelper(no->direita, valor, valorRemovido);
    } else {
        if (no->esquerda == nullptr && no->direita == nullptr) {
            
            delete no;
            no = nullptr;
            std::cout << valorRemovido << " removido" << std::endl;
        } else if (no->esquerda == nullptr) {
            
            NoABB* temp = no;
            no = no->direita;
            delete temp;
            std::cout << valorRemovido << " removido" << std::endl;
        } else if (no->direita == nullptr) {
            
            NoABB* temp = no;
            no = no->esquerda;
            delete temp;
            std::cout << valorRemovido << " removido" << std::endl;
        } else {
            NoABB* mindireita = minNo(no->direita);
            no->dado = mindireita->dado;
            no->direita = removerHelper(no->direita, mindireita->dado, valorRemovido);
        }
    }

    if (no != nullptr) {
        no->altura = 1 + std::max(getAltura(no->esquerda), getAltura(no->direita));

        int fatorBalanco = getAltura(no->esquerda) - getAltura(no->direita);

        // Left-Left Case
        if (fatorBalanco > 1 && getAltura(no->esquerda->esquerda) >= getAltura(no->esquerda->direita))
            return rodarDireita(no);

        // Right-Right Case
        if (fatorBalanco < -1 && getAltura(no->direita->esquerda) <= getAltura(no->direita->direita))
            return rodarEsquerda(no);

        // Left-Right Case
        if (fatorBalanco > 1 && getAltura(no->esquerda->esquerda) < getAltura(no->esquerda->direita)) {
            no->esquerda = rodarEsquerda(no->esquerda);
            return rodarDireita(no);
        }

        // Right-Left Case
        if (fatorBalanco < -1 && getAltura(no->direita->esquerda) > getAltura(no->direita->direita)) {
            no->direita = rodarDireita(no->direita);
            return rodarEsquerda(no);
        }
    }

    return no;
}

std::string ArvoreBuscaBinaria::preOrdemHelper(NoABB* no) {
    std::string travessia;

    // Verifica se o nó atual é nulo, caso seja, retorna a string de travessia.
    if (no == nullptr)
        return travessia;

    // Adiciona o valor do nó atual à string de travessia e usa recursão com 
    // os nós esquerdos e direitos
    travessia += std::to_string(no->dado) + " ";
    travessia += preOrdemHelper(no->esquerda);
    travessia += preOrdemHelper(no->direita);

    return travessia;
}

NoABB* ArvoreBuscaBinaria::buscarHelper(NoABB* no, int valor) {

    // Verifica se o nó atual é nulo ou se o valor do nó atual é igual ao valor procurado.
    // Em ambos os casos, retorna o nó atual.
    if (no == nullptr || no->dado == valor) {
        return no;
    }

    // Verifica se o valor é menor que o valor do nó atual.
    // Chama recursivamente a função para buscar o valor na subárvore esquerda do nó atual.
    if (valor < no->dado) {
        return buscarHelper(no->esquerda, valor);
    
    // Caso contrário, o valor é maior que o valor do nó atual.
    // Chama recursivamente a função para buscar o valor na subárvore direita do nó atual.
    } else {
        return buscarHelper(no->direita, valor);
    }
}

bool ArvoreBuscaBinaria::ehCheiaHelper(NoABB* no) {

    // Verifica se o nó atual é nulo, indicando uma árvore vazia.
    // Nesse caso, a árvore é considerada cheia.
    if (no == nullptr) {
        return true;
    }

    // Verifica se o nó atual é uma folha, ou seja, não tem filhos.
    // Nesse caso, a árvore é considerada cheia.
    if (no->esquerda == nullptr && no->direita == nullptr) {
        return true;
    }

    // Verifica se o nó atual tem tanto filho esquerdo quanto filho direito.
    // Chama recursivamente a função para verificar se as subárvores esquerda e direita também são cheias.
    // Se ambas as subárvores forem cheias, a árvore é considerada cheia.
    if (no->esquerda != nullptr && no->direita != nullptr) {
        return ehCheiaHelper(no->esquerda) && ehCheiaHelper(no->direita);
    }

    // Se nenhuma das condições anteriores for atendida, significa que a árvore não é cheia.
    return false;
}

bool ArvoreBuscaBinaria::ehCompletaHelper(NoABB* no, int index, int numeroNos) {
    // Verifica se o nó atual é nulo, indicando uma árvore vazia.
    // Nesse caso, a árvore é considerada completa.
    if (no == nullptr)
        return true;

    // Verifica se o índice atual ultrapassa o número total de nós na árvore.
    // Se isso ocorrer, a árvore não é completa, então retorna falso.
    if (index >= numeroNos)
        return false;

    // Realiza chamadas recursivas para verificar se as subárvores esquerda e direita são completas.
    // Se ambas as subárvores forem completas, a árvore é considerada completa.
    return (ehCompletaHelper(no->esquerda, 2*index + 1, numeroNos) &&
            ehCompletaHelper(no->direita, 2*index + 2, numeroNos));
}

void ArvoreBuscaBinaria::imprimeArvore1Helper(NoABB* no, std::string prefixo) {
    // Verifica se o nó atual é nulo, indicando uma árvore vazia.
    // Nesse caso, não há nada a ser impresso, então retorna.
    if (no == nullptr)
        return;

    // Verifica se o prefixo está vazio, indicando a raiz da árvore.
    // Nesse caso, imprime apenas o valor do nó seguido de linhas.
    if (prefixo.empty()) {
        std::cout << no->dado << "----------------------------------" << std::endl;

    // Caso contrário, imprime o prefixo seguido do valor do nó e as linhas.
    } else {
        std::cout << prefixo << no->dado << "----------------------------" << std::endl;
    }

    imprimeArvore1Helper(no->esquerda, prefixo + "\t\t");
    imprimeArvore1Helper(no->direita, prefixo + "\t\t");
}

void ArvoreBuscaBinaria::imprimeArvore2Helper(NoABB* no, int numeroNos) {
    // Verifica se o nó atual é nulo, indicando uma árvore vazia.
    // Nesse caso, não há nada a ser impresso, então retorna.
    if (no == nullptr)
        return;

    std::cout << "(" << no->dado << " ";
    imprimeArvore2Helper(no->esquerda,numeroNos);
    std::cout << " ";
    imprimeArvore2Helper(no->direita,numeroNos);
    std::cout << ")";
}
double ArvoreBuscaBinaria::media (int x){
    NoABB* newraiz = buscarHelper(raiz, x);
    if (newraiz == nullptr) {
        return 0.0; 
    }
     return media(newraiz);
}

double ArvoreBuscaBinaria::media(NoABB* newraiz){
    if (newraiz == nullptr) {
        return 0.0;
    }
    int quantiNos = 1;
    double soma = newraiz->dado;
    
     if (newraiz->esquerda != nullptr) {
        soma += media(newraiz->esquerda); // soma os nós da subárvore esquerda
        quantiNos += contarNos(newraiz->esquerda); // conta o número de nós da subárvore esquerda
    }
  
    if (newraiz->direita != nullptr) {
        soma += media(newraiz->direita); // soma os nós da subárvore direita
        quantiNos += contarNos(newraiz->direita); // conta o número de nós da subárvore direita
    }
  
    // Retorna a média aritmética
    return soma / quantiNos;
    
}

NoABB* ArvoreBuscaBinaria::minNo(NoABB* no) {
    // Inicia o nó atual com o nó passado como argumento.
    NoABB* current = no;

    // Percorre a árvore pela esquerda até encontrar o nó com o menor valor.
    while (current->esquerda != nullptr) {
        current = current->esquerda;
    }

    // Retorna o nó com o menor valor encontrado.
    return current;
}

int ArvoreBuscaBinaria::contarNos(NoABB* raiz) {
    // Verifica se a raiz é nula, indicando uma árvore vazia.
    // Nesse caso, o número de nós é zero.
    if (raiz == nullptr)
        return 0;

    // Retorna a soma do número de nós da subárvore esquerda, da subárvore direita
    // e mais um para contar a própria raiz.
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}
 
void ArvoreBuscaBinaria::lerArquivos(std::string arquivo1 , std::string arquivo2){
    int numero;
    std::ifstream arquivo_entrada;
    // Abre o arquivo de entrada e lê os valores da ABB
    arquivo_entrada.open(arquivo1);
    if (arquivo_entrada.is_open()) { 
        while(arquivo_entrada >> numero)
            inserir(numero); 
        arquivo_entrada.close();
    }

    std::string linha;
    std::string comando;
    int valor;
    std::ifstream arquivo_comandos;

    // Abre o arquivo de entrada e lê os comandos a serem executados
    arquivo_comandos.open(arquivo2);
    if (arquivo_comandos.is_open()) { 
        while(getline(arquivo_comandos,linha)){
            std::istringstream iss(linha);
            iss >> comando >> valor;

            // Checa por cada comando e chama suas respectivas funções
            if(comando == "INSIRA"){
                inserir(valor);
            }
            else if(comando == "REMOVA"){
                remover(valor);
            }
            else if(comando == "BUSCAR"){
                if(buscar(valor))
                    std::cout << "Chave encontrada" << std::endl;
                else
                    std::cout << "Chave não encontrada" << std::endl;
            }
            else if(comando == "ENESIMO"){
                std::cout << enesimoElemento(valor) << std::endl;
            }
            else if(comando == "POSICAO"){
                std::cout << posicao(valor) << std::endl;
            }
            else if(comando == "MEDIANA"){
                std::cout << mediana() << std::endl;
            }
            else if(comando == "MEDIA"){
                std::cout << media(valor) << std::endl;
            }
            else if(comando == "CHEIA"){
                if(ehCheia())
                   std::cout << "A árvore é cheia" << std::endl;
                else
                    std::cout << "A árvore não é cheia" << std::endl;
            }
            else if(comando == "COMPLETA"){
                if(ehCompleta())
                   std::cout << "A árvore é completa" << std::endl;
                else
                    std::cout << "A árvore não é completa" << std::endl;
            }
            else if(comando == "PREORDEM"){
                std::cout << pre_ordem() << std::endl;
            }
            else if(comando == "IMPRIMA"){
                imprimeArvore(valor);
            }

        }
        arquivo_comandos.close();
    }

}

//Funções públicas
void ArvoreBuscaBinaria::inserir(int valor) {
    raiz = inserirHelper(raiz, valor);
}

std::string ArvoreBuscaBinaria::pre_ordem() {
    return preOrdemHelper(raiz);
}

void ArvoreBuscaBinaria::remover(int valor) {
    raiz = removerHelper(raiz, valor,valor);
}

bool ArvoreBuscaBinaria::buscar(int valor) {
    NoABB* noEncontrado = buscarHelper(raiz, valor);
    return noEncontrado != nullptr;
}

bool ArvoreBuscaBinaria::ehCheia() {
    return ehCheiaHelper(raiz);
}

bool ArvoreBuscaBinaria::ehCompleta() {
    int numeroNos = contarNos(raiz);
    return ehCompletaHelper(raiz, 0, numeroNos);
}

void ArvoreBuscaBinaria::imprimeArvore (int s) {
    int numeroNos = contarNos(raiz);

    if(s == 1) //<! Caso seja o formato 1
        imprimeArvore1Helper(raiz,"");
    else if (s == 2) //<! Caso seja o formato 1
        imprimeArvore2Helper(raiz,numeroNos);
    else //<! Caso não seja especificado um formato válido, imprime um erro.
        std::cout << "Erro: Formato Inválido!";
    std::cout << std::endl;
}

void ArvoreBuscaBinaria::ordemNes(NoABB* raiz, int &cont, int n, int &enesimo){
    if (raiz == nullptr) {
        return;
    }    // Percorre a subárvore esquerda
    ordemNes(raiz->esquerda, cont, n, enesimo);
   
    // Verifica se o elemento atual é o n-ésimo elemento
    cont++;
    if (cont == n) {
        enesimo = raiz->dado;
        return;
    }

 // Percorre a subárvore direita
    ordemNes(raiz->direita, cont, n, enesimo);
}

int ArvoreBuscaBinaria::enesimoElemento (int n){
    int cont = 0;  // Contador para rastrear a posição atual no percurso em ordem
    int enesimo = 0; // Variável para armazenar o resultado
    // Realiza o percurso em ordem e atualiza o resultado quando encontrar o n-ésimo elemento
    ordemNes(raiz, cont, n, enesimo);


    return enesimo;
}

bool ArvoreBuscaBinaria::ordemPos(NoABB* raiz, int &cont, int x) {
    if (raiz == nullptr) {
        return false;
    }

    if (ordemPos(raiz->esquerda, cont, x)) {
        return true;
    }

    cont++;
    if (raiz->dado == x) {
        return true;
    }

    return ordemPos(raiz->direita, cont, x);
}

int ArvoreBuscaBinaria::posicao(int x) {
    int cont = 0;  // Inicia o contador como 0

    if (ordemPos(raiz, cont, x)) {
        return cont; 
    }

    return -1;  
}

int ArvoreBuscaBinaria::mediana(){
    if((contarNos(raiz)%2)==0){
        return enesimoElemento ((contarNos(raiz)/2));
    }
    else{
        int y=(contarNos(raiz)+1)/2;
        return enesimoElemento (y);
    }

}

int ArvoreBuscaBinaria::getAltura(NoABB* node) {
    if (node == nullptr)
        return 0;
    return node->altura;
}

void ArvoreBuscaBinaria::updateAltura(NoABB* node) {
    int alturaEsquerda = getAltura(node->esquerda);
    int alturaDireita = getAltura(node->direita);
    node->altura = 1 + std::max(alturaEsquerda, alturaDireita);
}

NoABB* ArvoreBuscaBinaria::rodarEsquerda(NoABB* node) {
    NoABB* newRoot = node->direita;
    node->direita = newRoot->esquerda;
    newRoot->esquerda = node;
    updateAltura(node);
    updateAltura(newRoot);
    return newRoot;
}

NoABB* ArvoreBuscaBinaria::rodarDireita(NoABB* node) {
    NoABB* newRoot = node->esquerda;
    node->esquerda = newRoot->direita;
    newRoot->direita = node;
    updateAltura(node);
    updateAltura(newRoot);
    return newRoot;
}