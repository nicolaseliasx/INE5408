// Copyright [2022] <Mauricio Konrath e Nicolas ELias>

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <string>

#define ALPHABET_SIZE 26

namespace structures { 

class Trie {
 public:
  Trie(); //Novo Trie
  void inserir(std::string word, int index, int length);
  std::pair<int, int> procurar(std::string word);
  int n_prefixo(std::string word);
  int n_children();
  int n_palavras();

 private:
    Trie* children[ALPHABET_SIZE];
    int index{0}, length{0};
};

}  // namespace structures

#endif

//  No novo Trie o index que é a posição e o lenght que é o comprimento vão 
//  ser definidos inicialmente como 0 e as posições de children que 
//  são os nodos filhos são  nulos

structures::Trie::Trie() {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		children[i] = nullptr;
	}
}
// Vai adicionar uma chave na árvore, word é a palavra a ser inserida, 
// o index a posição no dicionario da palavra a ser inserida, e o lenght o 
//comprimento da linha do dicionario que possui a palavra a ser inserida.

void structures::Trie::inserir(std::string word, int index, int length) {
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			current->children[position] = new Trie;
    	}
		current = current->children[position];
	}
	current->index = index;
	current->length = length;
}

// Vai procurar uma palavra na árvore, word é a palavra a ser procurada
std::pair<int, int> structures::Trie::procurar(std::string word) {
    //indica se a palavra pertence ao dicionario ou ou se é um prefixo
	std::pair<int, int> pair; 
// Caso a palavra pertença ao dicionário, o primeiro valor do par representa 
// a posição da palavra enquanto o segundo  representa o comprimeto da linha.
  
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			pair.first = -1;
			pair.second = -1;
			return pair;
		}
		current = current->children[position];
	}
	if (current && current->length == 0) {
		pair.first = 0;
		pair.second = 0;
		return pair;
	}
	pair.first = current->index;
	pair.second = current->length;
	return pair;
}
// Conta o número de vezes que a palavra é prefixo, 
//o word é a palavra a ser contada, 
//ele ira retornar um número inteiro com as vezes que a palavra foi prefixo

int structures::Trie::n_prefixo(std::string word) {
	auto current = this;
	int n_prefix = 0;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			break;
		}
		current = current->children[position];
	}
	if (current) {
		if (current->length != 0) {
			n_prefix++;
		}
		n_prefix += current->n_palavras();
	}
	return n_prefix;
}

//  Conta o número de filhos, e retorna um inteiro sendo ele o número de filhos

int structures::Trie::n_children() {
	auto current = this;
	int n_children = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (current->children[i]) {
			n_children++;
		}
	}
	return n_children;
}
//  Conta o número de palavras a partir do nodo, e retorna um número inteiro 
//  com a quantidade de palavras.

int structures::Trie::n_palavras() {
	int n_words = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (children[i]) {
			if (children[i]->length != 0) {
				n_words++;
			}
			n_words += children[i]->n_palavras();
		}
	}
	return n_words;
}
