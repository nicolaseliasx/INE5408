//! Copyright [2021] <Nicolas Elias>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
    //! Declaração da classe Lista Encadeada
class LinkedList {public:
    //! Construtor Padrão
    LinkedList();
    //! Destrutor
    ~LinkedList();
    //! Método que limpa a lista
    void clear();
    //! Método que insere no final
    void push_back(const T& data);
    //! Método que insere no início
    void push_front(const T& data);
    //! Método que insere no índice do parâmetro
    void insert(const T& data, std::size_t index);
    //! Método que insere na ordem
    void insert_sorted(const T& data);
    //! Método que acessa um elemento na posição do índice
    T& at(std::size_t index);
    //! Método que remove o dado do índice dado por parâmetro
    T pop(std::size_t index);
    //! Método que remove do fim da lista
    T pop_back();
    //! Método que remove do início da lista
    T pop_front();
    //! Método que remove elemento dado por parâmetro
    void remove(const T& data);
    //! Método que informa se a lista está vazia
    bool empty() const;
    //! Método que verifica se o elemento está na lista
    bool contains(const T& data) const;
    //! Método que retorna o índice do elemento dado por parâmetro
    std::size_t find(const T& data) const;
    //! Método que retorna o tamanho atual da lista
    std::size_t size() const;

 private:
    //!  Elemento
    class Node{public:
        explicit Node(const T& data):
            data_{data}
        {}

  Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = {nullptr};
    size_ = 0;
}

template<typename T>
void structures::LinkedList<T>::clear() {
    Node *atual, *anterior;
    atual = head;
    while (atual != nullptr) {
        anterior = atual;
        atual = atual->next();
        delete anterior;
    }
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        insert(data, size_);
    }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* novo = new Node(data, head);
    if (novo == nullptr) {
        throw std::out_of_range("Lista Cheia!");
    }
    head = novo;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node *novo, *anterior;
    if (index > size_) {
        throw std::out_of_range("Posição inválida!");
    } else if (index == 0) {
        push_front(data);
    } else {
        novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Lista Cheia!");
        }
        anterior = head;
        for (auto i = 1u; i < index; i++) {
            anterior = anterior->next();
        }
        novo->next(anterior->next());
        anterior->next(novo);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* atual;
    std::size_t indice;
    if (empty()) {
        return push_front(data);
    } else {
        atual = head;
        indice = 0;
        while (atual->next() != nullptr && data > atual->data()) {
            atual = atual->next();
            indice++;
        }
        if (data > atual->data()) {
            return insert(data, indice + 1);
        } else {
            return insert(data, indice);
        }
    }
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
auto it = head;
for (auto i = 0; i < index; i++) {
       if (it->next() == nullptr) {
           throw std::out_of_range("Possição Inválida!");
       }
       it = it->next();
}
  return it->data();
}


template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    }
    Node *anterior, *retirar;
    T retorno;
    if (index > size_ - 1) {
        throw std::out_of_range("Posição Inválida!");
    } else if (index == 0) {
        return pop_front();
    } else {
        anterior = head;
        for (auto i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        retirar = anterior->next();
        retorno = retirar->data();
        anterior->next(retirar->next());
        size_--;
        delete retirar;
        return retorno;
    }
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    Node* sai;
    T retorno;
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        sai = head;
        retorno = sai->data();
        head = sai->next();
        size_--;
        delete(sai);
        return retorno;
    }
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    }
    auto inicio = head;
    while (inicio != nullptr) {
        if (inicio->data() == data) {
            return true;
        }
        inicio = inicio->next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty()) {
        return -1;
    }
    auto inicio = head;
    auto indice = 0;
    while (inicio->data() != data) {
        inicio = inicio->next();
        indice++;
        if (inicio == nullptr) {
           break;
        }
    }
    return indice;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

}  //! namespace structures

#endif
