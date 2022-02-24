// Copyright [2022] <Nicolas Elias Santana>

#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* node_index(std::size_t index) {
        auto it = head;
        if (index <= size_/2) {
            for (auto i = 1u; i <= index; ++i)
                it = it->next();
        } else {
            for (auto i = 1u; i <= (size_-index); ++i)
                it = it->prev();
        }
        return it;
    }

    void insert(const T& data, Node* current);


    Node* head{nullptr};
    std::size_t size_{0u};
};

template<typename T>
DoublyCircularList<T>::DoublyCircularList() {}

template<typename T>
DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void DoublyCircularList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
        head = new_node;
        head->next(head);
        head->prev(head);
    } else {
        new_node->next(head);
        new_node->prev(head->prev());
        head->prev()->next(new_node);
        head->prev(new_node);
        head = new_node;
    }
    size_++;
}

template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Index > Size!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* current = node_index(index);
        new_node->next(current);
        new_node->prev(current->prev());
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }
}

template<typename T>
void DoublyCircularList<T>::insert(const T& data, Node* previous) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
        head = new_node;
        head->prev(head);
        head->prev(head);
    } else {
        previous->next()->prev(new_node);
        new_node->next(previous->next());
        previous->next(new_node);
        new_node->prev(previous);
    }
    size_++;
}

template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto current = head;
        std::size_t position = 0u;
        while (data > current->data()) {
            if (++position == size_)
                break;
            current = current->next();
        }
        position == 0? push_front(data):
        position == size_? push_back(data):
                           insert(data, current->prev());
    }
}



template<typename T>
T DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Index > size!");
    if (index == 0)
        return pop_front();

    auto out = node_index(index);
    T data = out->data();
    out->prev()->next(out->next());
    out->next()->prev(out->prev());
    size_--;
    delete out;
    return data;
}


template<typename T>
T DoublyCircularList<T>::pop_back() {
    return pop(size_-1);
}


template<typename T>
T DoublyCircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list");

    auto out = head;
    T data = head->data();
    head->prev()->next(head->next());
    head->next()->prev(head->prev());
    head = head->next();
    size_--;
    delete out;

    if (empty())
        head = nullptr;
    return data;
}

template<typename T>
void DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool DoublyCircularList<T>::empty() const {
    return size() == 0u;
}

template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
T& DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = node_index(index);
    return current->data();
}

template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = node_index(index);
    return current->data();
}

template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    auto current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t DoublyCircularList<T>::size() const {
    return size_;
}

}  // namespace structures
#endif
