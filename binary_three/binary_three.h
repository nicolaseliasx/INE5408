#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree() = default;

    ~BinaryTree() {
        delete root;
        size_ = 0;
    }

    void insert(const T& data) {
        if (empty()) {
            root = new Node(data)
        } else {
            root->insert(data);
        }
        size_++;
    }

    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("ERRO ÁRVORE VAZIA!!!");
        } else {
            size_--;
            root->remove(data);
        }
    }

    //Nao entendi essa parte
    bool contains(const T& data) const {
        bool temp = false;
        if (!empty())
            temp = root->contains(data);
        return temp;
    }

    bool empty() const {
        return (size_ == 0);
    }

    std::size_t size() const {
        return(size_);
    }

    // Jogando pra uma lista pra q?
    ArrayList<T> pre_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->pre_order(v);
        }
        return v;
    }

    ArrayList<T> in_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->in_order(v);
        }
        return v;
    }

    ArrayList<T> post_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->post_order(v);
        }
        return v;
    }

private:
    struct Node {
        explicit Node(const T& data) : data{data}, left{nullptr}, right{nullptr}
        {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            
        }

        bool remove(const T& data_){

        }

        bool contains(const T& data_) const {

        }

        void pre_order(ArrayList<T>& v) const {

        }

        void in_order(ArrayList<T>& v) const {

        }

        void post_order(ArrayList<T>& v) const {
            
        }
    };

    Node* root;
    std::size_t size_;
};

}