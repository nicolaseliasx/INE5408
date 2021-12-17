//! Copyright [2021] <Nicolas Elias>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H
#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {


//! Classe Lista
template<typename T>
class ArrayList {
 public:
    //! Construtor simples
    ArrayList();
    //! Construtor com parametro tamanho
    explicit ArrayList(std::size_t max_size);
    //! Destrutor
    ~ArrayList();
    //! Limpa lista
    void clear();
    //! Adiciona no fim
    void push_back(const T& data);
    //! Adiciona no inicio
    void push_front(const T& data);
    //! Adiciona na posicao
    void insert(const T& data, std::size_t index);
    //! Adiciona em ordem
    void insert_sorted(const T& data);
    //! Retira da posicao
    T pop(std::size_t index);
    //! Retira do fim
    T pop_back();
    //! Retira do inicio
    T pop_front();
    //! Remove dado especifico
    void remove(const T& data);
    //! Ve se esta cheio
    bool full() const;
    //! Ve se esta vazio
    bool empty() const;
    //! Ve se contem o dado
    bool contains(const T& data) const;
    //! Encontra o dado e retorna posicao
    std::size_t find(const T& data) const;
    //! Tamanho atual
    std::size_t size() const;
    //! Tamanho maximo
    std::size_t max_size() const;
    //! Retorna o dado pelo indice e verifica o indice
    T& at(std::size_t index);
    //! Retorna o dado pelo indice
    T& operator[](std::size_t index);
    // descricao do 'operator []' na FAQ da disciplina
    //! Retorna o dado pelo indice como uma constante e verifica o indice
    const T& at(std::size_t index) const;
    //! Retorna o dado pelo indice como constante
    const T& operator[](std::size_t index) const;

 protected:
    T* contents;
    std::size_t last;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! Lista de Strings
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! Construtor simples
    ArrayListString() : ArrayList() {}
    //! Construtor com parametro tamanho
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! Destrutor
    ~ArrayListString();
    //! Limpa lista
    void clear();
    //! Adiciona no fim
    void push_back(const char *data);
    //! Adiciona no inicio
    void push_front(const char *data);
    //! Adiciona na posicao
    void insert(const char *data, std::size_t index);
    //! Adiciona em ordem
    void insert_sorted(const char *data);
    //! Retira da posicao
    char *pop(std::size_t index);
    //! Retira do fim
    char *pop_back();
    //! Retira do inicio
    char *pop_front();
    //! Remove dado especifico
    void remove(const char *data);
    //! Verifica se contem o dado
    bool contains(const char *data);
    //! Encontra o dado retorna posicao
    std::size_t find(const char *data);
};

}  // namespace structures

#endif


// Metodos ArrayList
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
    delete[] contents;
}


template<typename T>
void structures::ArrayList<T>::clear() {
    last = -1;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        last++;
        contents[size_] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        last++;
        std::size_t position = last;
        while (position > 0) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[0] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        if (index > last + 1 || index < 0) {
            throw std::out_of_range("posicao invalida");
        }
        last++;
        std::size_t position = last;
        while (position > index) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[index] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        std::size_t position = 0;
        while (position < last + 1 && data > contents[position]) {
            position++;
        }
        insert(data, position);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index > last || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            last--;
            T value = contents[index];
            std::size_t position = index;
            while (position < last+1) {
                contents[position] = contents[position + 1];
                position++;
            }
            return value;
        }
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        last--;
        return contents[last + 1];
    }
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        last--;
        T value = contents[0];
        std::size_t position = 0;
        while (position < last + 1) {
            contents[position] = contents[position + 1];
            position++;
        }
        return value;
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        std::size_t position = find(data);
        if (position < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            pop(position);
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (last + 1 == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (last + 1 == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    std::size_t position = 0;
    while (position <= last) {
        if (contents[position] == data) {
            return true;
        }
        position++;
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std::size_t position = 0;
    while (position <= last && data != contents[position]) {
        position++;
    }
    return position;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return (last + 1);
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        if (index > last || index < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            return contents[index];
        }
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        if (index > last || index < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            return contents[index];
        }
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

// Metodos ArrayListString
structures::ArrayListString::~ArrayListString() {
    for (std::size_t i = 0; i < last+1; i++) {
        delete[] contents[i];
    }
}

void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < last+1; i++) {
        delete[] contents[i];
    }
    last = -1;
}

void structures::ArrayListString::push_back(const char *data) {
    char* newdata = new char[strlen(data)+1];
    snprintf(newdata, strlen(data)+1, "%s", data);
    ArrayList<char*>::push_back(newdata);
}

void structures::ArrayListString::push_front(const char *data) {
    char* newdata = new char[strlen(data)+1];
    snprintf(newdata, strlen(data)+1, "%s", data);
    ArrayList<char*>::push_front(newdata);
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
    char* newdata = new char[strlen(data)+1];
    snprintf(newdata, strlen(data)+1, "%s", data);
    ArrayList<char*>::insert(newdata, index);
}

void structures::ArrayListString::insert_sorted(const char *data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        std::size_t position = 0;
        char* newdata = new char[strlen(data)+1];
        snprintf(newdata, strlen(data)+1, "%s", data);
        while (position < last+1 && strcmp(newdata, contents[position]) > 0) {
            position++;
        }
        insert(newdata, position);
    }
}

char* structures::ArrayListString::pop(std::size_t index) {
    char* data = ArrayList<char*>::pop(index);
    char* newdata = new char[strlen(data)+1];
    snprintf(newdata, strlen(data)+1, "%s", data);
    return newdata;
}

char* structures::ArrayListString::pop_back() {
    return pop(last);
}

char* structures::ArrayListString::pop_front() {
    return pop(0);
}

void structures::ArrayListString::remove(const char *data) {
    pop(find(data));
}

bool structures::ArrayListString::contains(const char *data) {
    return !(find(data) == last+1);
}

std::size_t structures::ArrayListString::find(const char *data) {
    std::size_t position = 0;
    while (position <= last && strcmp(data, contents[position]) != 0) {
        position++;
    }
    return position;
}


