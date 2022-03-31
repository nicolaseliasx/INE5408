// Copyright [2022] <Mauricio Konrath e Nicolas Elias>

#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"

//Vai receber o um dos arquivos dic e colocar as palavras 
//em uma árvore de prefixos para fazer a busca das palavras
int main() {
    using namespace std;
    using namespace structures;

    string filename;
    cin >> filename;  // Arquido de entrada.
    Trie trie;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        int next_index = 0;
        while (getline(file, line)) {
            string word_read;
            if (line[0] != '[') {
                next_index += line.length() + 1;
                continue;
            }
            for (int i = 1; i < line.length(); i++) {
				if (line[i] == ']') {
                    break;
                }
				word_read += line[i];
			}
            trie.inserir(word_read, next_index, line.length());
            next_index += line.length() + 1;
        }
        file.close();
    } else {
      //se o arquivo não conseguir ser aberto, retornará -1
        cout << "Não foi possivel abrir o arquivo\n";
        return -1;
    }

    string word;
    pair<int, int> pair;
    while (1) {  // Leitura das palavras até encontrar "0".
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        pair = trie.procurar(word);
        string p = word;
        if (pair.first  == 0 && pair.second == 0) {
            int n = trie.n_prefixo(word);
            cout << p << " is prefix of " << n << " words" << endl;
        } else if (pair.first  == -1) {
            cout << p << " is not prefix" << endl;
        } else {
            int n = trie.n_prefixo(word);
            int d = pair.first;
            int c = pair.second;
            cout << p << " is prefix of " << n << " words" << endl;
            cout << p << " is at " << "(" << d << "," << c << ")" << endl;
        }
    }
  //se ocorrer algum erro retorna 0
    return 0;
}