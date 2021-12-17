// Copyright [2019] <COLOQUE SEU NOME AQUI...>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// Construtor com falor constante 10
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

// Construtor com valor especificado
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

// Destrutor
template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

// Verifica se a pilha esta cheia, se não estiver aumenta o valor
// do topo e coloca o dano na posicao do topo
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("pilha cheia");
    ++top_;
    contents[top_] = data;
}

// verifica se esta vazio a pilha, se nao estiver cria uma variavel
// auxiliar que armazena o conteudo do top antes de subtrair 1 e o retorna
template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("erro pilha vazia");
    T aux;
    aux = contents[top_];
    top_--;
    return aux;
}

// verifica se a pilha esta vazia se estiver ele
// lanca uma exception se nao retorna o conteudo do top
template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("erro pilha vazia ao acessar!");
    return contents[top_];
    }

// coloca o top em -1 para quando inserir resetar a pilha
template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

// tamanho da pilha é topo + 1
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

// retorna valor atribuido no atributo max_size
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

// verifica se top_ == -1 se for retorna true se nao retorna false
template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (top_ == -1);
}

// Obtive um erro ao fazer da mesma maneira que foi feito
// no metodo acima, entao criei uma variavel local unsigned
// verifica se top_ = ao tamanho maaximo se foir verdade esta cheio
template<typename T>
bool structures::ArrayStack<T>::full() {
    unsigned teste = top_;
    return (teste+1 == max_size());
}
