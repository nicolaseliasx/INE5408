// Copyright [2021] Nicolas Elias
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H
#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    static  const auto DEFAULT_MAX = 10u;
    T* contents;
    std::size_t last;
    std::size_t max_size_;
};

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    last = -1;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    last = -1;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (last == max_size_ - 1);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    int t = last;
    return (t== -1);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    std::size_t position;
    if (full()) {
        throw std::out_of_range("erro lista cheia");
    }
    if (index > last + 1 || index < 0) {
        throw std::out_of_range("erro na posicao");
    }
    last++;
    position = last;
    while (position > index) {
        contents[position] = contents[position - 1];
        position--;
    }
    contents[index] = data;
}

// retira da posicao
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    std::size_t position;
    std::size_t value;
    if (empty()) {
        throw std::out_of_range("erro lista vazia");
    } else {
        if (index > last) {
            throw std::out_of_range("erro na posicao");
        }
        last--;
        value = contents[index];
        position = index;
        while (position <= last) {
            contents[position] = contents[position + 1];
            position++;
        }
    }
    return(value);
}

// retira do inicio e empurra
template<typename T>
T structures::ArrayList<T>::pop_front() {
    int position;
    int value;
    int temp;
    if (empty()) {
        throw std::out_of_range("erro lista vazia");
    } else {
        last--;
        value = contents[0];
        position = 0;
        temp = last;
        while (position <= temp) {
            contents[position] = contents[position + 1];
            position++;
        }
        return (value);
    }
}

// retirada padrao
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("erro lista vazia");
    }
    int value = contents[last];
    last--;
    return value;
}

// adiciona no inicio
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("erro lista cheia");
    } else {
        int position;
        last++;
        position = last;
        while (position > 0) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[0] = data;
    }
}


template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
       throw std::out_of_range("erro lista cheia");
    }
    last++;
    contents[last] = data;
}


template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
            throw std::out_of_range("lista Cheia.");
        } else {
            int position = 0;
            int t = last + 1;
            while (position < t && data > contents[position]) {
                position++;
            }
            insert(data, position);
        }
    }
}  // namespace structures

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return last + 1;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    last = -1;
}

template <typename T>
T&  structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    if (index > last) {
        throw std::out_of_range("fora do range");
    }
    return contents[index];
}

template <typename T>
const T&  structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    if (index > last) {
        throw std::out_of_range("fora do range");
    }
    return contents[index];
}

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("lista vazia");
    for (std::size_t i = 0; i < max_size_; ++i) {
        if (contents[i] == data) {
            pop(i);
            break;
        }
    }
}

template <typename T>
bool  structures::ArrayList<T>::contains(const T& data) const {
    for (std::size_t i = 0; i < max_size_; ++i) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::size_t  structures::ArrayList<T>::find(const T& data) const {
    int position = 0;
    int t = last;
    while (position <= t && contents[position] != data) {
        position++;
    }
    return position;
}

template <typename T>
T&  structures::ArrayList<T>::operator[](std::size_t index) {
    if (index < 0) {
        throw std::out_of_range("index menor que 0");
    }
    return contents[index];
}

template <typename T>
const T&  structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index < 0) {
        throw std::out_of_range("index menor que 0");
    }
    return contents[index];
}

#endif