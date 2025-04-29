#include <iostream>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
};

TrieNode* root = new TrieNode();

void insert(const string& word){
    TrieNode* node = root;
    for(char ch : word){
        int index = ch - 'a';
        if(node->children[index] == nullptr){
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool search(const string& word){
    TrieNode* node = root;
    for(char ch : word){
        int index = ch - 'a';
        if(node->children[index] == nullptr){
            return false;
        }
        node = node->children[index];
    }
    return node->isEndOfWord;
}

bool deleteWord(TrieNode* node, const string& word, int i){
    if(!node) return false;
    if(i == word.length()){
        node->isEndOfWord = false;
    }else{
        int index = word[i] - 'a';
        if(deleteWord(node->children[index], word, i + 1)){
            delete node->children[index];
            node->children[index] = nullptr;
        }
    }

    if(node->isEndOfWord){
        return false;
    }

    for(int k = 0; k < 26; k++){
        if(node->children[k]){
            return false;
        }
    }

    return true;
}

int main(){
    string word;
    insert("hello");
    insert("world");
    insert("heaven");
    insert("heavy");

    deleteWord(root, "hello", 0);

    cout << search("hello") << endl;
}