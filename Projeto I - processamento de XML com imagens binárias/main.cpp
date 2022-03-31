/// Copyright [2022] <Nicolas Elias>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H


#include <iostream> ///ler e gravar
#include <fstream> ///arquivos
#include <sstream> ///dados
#include <tuple> ///tupla
#include <stack> ///pilha
#include <string> ///string e memória
#include <vector> ///array
#include <stdexcept> ///exceções em c++
#include <algorithm> ///intervalos
#include <utility> /// outras funções
#include <cstdint> ///std::size_t


namespace xml {
// Pega a tag
std::string get_tag(
    const std::string& source, 
    const std::string& open_tag,
    const std::string& close_tag, 
    size_t& start_index);
// Pega o valor
std::string get_value(
    const std::string& source,
    const std::string& open_tag,
    const std::string& close_tag);
bool valida(const std::string& contents); // Valida o xml

} //namespace xml

namespace structures {
// Classe LinkedStack
template<typename T>
class LinkedStack {
public:
    // Construtor
    LinkedStack();
    // Destrutor 
    ~LinkedStack();
    // Limpa pilha
    void clear();
    // Empilha
    void push(const T& data);
    // Desempilha
    T pop();
    // Pega o topo 
    T& top() const;
    // Testa vazio   
    bool empty() const; 
    // Retorna o Tamanho
    std::size_t size() const;
 
private:
    class Node {   
     public:
        explicit Node(const T &data) {
            data_ = data;
            next_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        // Getter: dado  
        T& data() { 
            return data_;
        }
        // Getter const: dado 
        const T& data() const {  
            return data_;
        }
        // Getter: próximo
        Node* next() { 
            return next_;
        }
        // Getter const: próximo
        const Node* next() const { 
            return next_;
        }
        // Setter: próximo  
        void next(Node* node) { 
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};
    std::size_t size_{0u};
};
}   // namespace structures

namespace area {
    // Determina a sequencia, se for 0 é preto se for 1 é branco
    enum cor {
        // 0 para preto
        preto,
        // 1 para branco
        branco,
    };
    // Conta area em branco
    int area_contador(std::vector<std::vector<bool>> matrix);
    // Transforma matriz inteira em zeros
    void area_transformada(std::vector<std::vector<bool>>& matrix, int i, int j);
    // Cria nova matriz apartir de uam string de zeros e uns
    std::vector<std::vector<bool>> matriz_nova(const std::string& str_matrix, 
                                                int width, int height);
} // namespace area

int main() {

    char xmlfilename[100];
    std::ifstream xmlfile;
    // Entrada do arquivo xml
    std::cin >> xmlfilename;
    
    xmlfile.open(xmlfilename);
    // Retorna mensagem de erro e -1 caso de erro em abrir o arquivo
    if (not xmlfile.is_open()) {
        std::cout << "error";
        return -1;
    }
    
    std::stringstream stream;
    stream << xmlfile.rdbuf();
    std::string contents = stream.str();
    
    xmlfile.close();
    // Retorna -1 em caso do arquivo xml ser invalido
    if (not xml::valida(contents)) {
        std::cout << "error";
        return -1;
    }
    
    size_t i ={0};

    // Busca a tag da proxima imagem dentro do xml
    while (i < contents.length()) {
        std::string open_tag = "<img>";
        std::string close_tag = "</img>";
        std::string image = xml::get_tag(contents, open_tag, close_tag, i);
        i += image.length() + close_tag.length();        
        // Caso tenha chego no fim das imagens:
        if (i > contents.length()) {
          break;
          }
        // Função get value ultilizada para buscar o conteudo de cada imagem
        std::string data = xml::get_value(image, "<data>", "</data>");
        const std::string name = xml::get_value(image, "<name>", "</name>");
        const int width = std::stoi(xml::get_value(image, "<width>", "</width>"));
        const int height = std::stoi(xml::get_value(image, "<height>", "</height>"));
        // Caso seja uma imagem inválida (altura e largura menores ou iguais a zero) retorna -1
        if (height <= 0|| width <= 0) {
          return -1;
        }
        // Remove o \n presente na string data
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        std::vector<std::vector<bool>> matrix = area::matriz_nova(data, width, height);

        int regions = area::area_contador(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }
}

namespace xml {
bool valida(const std::string& contents) {
    structures::LinkedStack<std::string> tags;
    size_t i = 0u;

    while (i < contents.length()) {
        // Encontra o inicio e final da proxima tag
        size_t pos_inicial = contents.find('<', i);
        size_t pos_final = contents.find('>', pos_inicial);
        // Se a posição final falhar, levanta um erro
        if (pos_inicial == std::string::npos) {
            break;
        }
        /// se a posição final falhar, ocorre um erro
        if (pos_final == std::string::npos) {
            return false;
        }
        
        std::string tag = contents.substr(pos_inicial, pos_final + 1 - pos_inicial);
        i = pos_final + 1;
       // Caso seja uma tag de abertura, coloca / no inicio da pilha
        if (tag[1] != '/') {
            tags.push(tag.insert(1, "/"));
        } else {
            // Caso a pilha esteja vazia e seja uma tag de fechamento, logo o arquivo é invalido
            if (tags.empty()) {
                return false;
            // Se a tag de fechamento foi igual ao topo da pilha, vai ser desempilhado o topo
                tags.pop();
            // Caso contrário da erro
            } else {
                return false;
            }  
        }
    }
    return tags.empty();
}

std::string get_tag(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag, 
    size_t& start_index) {

    size_t pos_inicial = source.find(open_tag, start_index);
    size_t pos_final = source.find(close_tag, pos_inicial);
            
    pos_inicial += open_tag.length();
    std::string tag_contents = source.substr(pos_inicial, pos_final - pos_inicial);
    return tag_contents;
}

std::string get_value(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag) {

    std::size_t pos{0};
    return get_tag(source, open_tag, close_tag, pos);
}
}  // namespace xml


namespace structures {
template<typename T>
// Metodos da LinkedStack vistos em aula
LinkedStack<T>::LinkedStack() {}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::clear() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node* novo = new Node(data, top_);
    top_ = novo;
    size_++;
}

template<typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Empty Stack");
    }
    Node* aux = top_;
    T data = aux->data();
    top_ = top_->next();
    size_--;
    delete aux;
    return data;
}

template<typename T>
T& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Empty Stack");
    }
    return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

} // namespace structures

namespace area {
// Metodo que transforma area conexa inteira em uma matriz de zeros (pretos)
void area_transformada(std::vector<std::vector<bool>>& matrix, int i, int j) {
    structures::LinkedStack<std::tuple<int, int>> stack;

    int largura = matrix[0].size();
    int altura = matrix.size();
    stack.push(std::make_tuple(i, j));

    while (!stack.empty()) {
        std::tuple<int, int> aux = stack.pop();
        
        i = std::get<0>(aux);
        j = std::get<1>(aux);
        matrix[i][j] = 0;
        // Verifica se existe branco na esquerda
        if (j > 0 && matrix[i][j - 1]) {
            stack.push(std::make_tuple(i, j - 1));     
        }
        // Verifica se existe brancos na direita
        if (j < (largura - 1) && matrix[i][j + 1]) {
            stack.push(std::make_tuple(i, j + 1));
        }
        // Verifica se existe branco acima
        if (i > 0 && matrix[i - 1][j]) {
            stack.push(std::make_tuple(i - 1, j));
        }
        // Verifica se existe branco abaixo
        if (i < (altura - 1) && matrix[i + 1][j]) {
            stack.push(std::make_tuple(i + 1, j));
        }
    }
}
/* Conta as area conexas de numeros um, incrementando um contador
 preenchendo com numero 0 esses elementos */
int area_contador(std::vector<std::vector<bool>> matrix) {
    int cont = 0;    
    for (int i = 0; i < (int) matrix.size(); i++) {
        for (int j = 0; j < (int) matrix[0].size(); j++) {
            if (matrix[i][j] == cor::branco) {
                cont++;
                area_transformada(matrix, i, j);
            }
        }
    }
    return cont;
}

// Metodo que cria matriz nova apartir dos zeros e uns
std::vector<std::vector<bool>> matriz_nova(const std::string& str_matrix, int width, int height) {
    std::vector<std::vector<bool>> matrix;

    for (int i = 0u; i < height; i++) {
        std::vector<bool> line;
        for (int j = 0; j < width; j++) {
            line.push_back(str_matrix[i * width + j] == '1');
        }
        matrix.push_back(line);
    } 
    return matrix;
}
} // namespace area

#endif