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

int countWordsRecur(TrieNode* node){
    if(node == nullptr){
        return 0;
    }
    if(node->isEndOfWord){
        return 1;
    }
    
    int count = 0;

    for(int i = 0; i < 26; i++){
        if(node->children[i] != nullptr){
            count += countWordsRecur(node->children[i]);
        }
    }
    return count;
}

int countWords(const string& pref){
    TrieNode* node = root;
    for(char ch : pref){
        int index = ch - 'a';
        if(node->children[index] == nullptr){
            return 0;
        }
        node = node->children[index];
    }
    return countWordsRecur(node);
}

int main(){
    string word;
    insert("hello");
    insert("world");
    insert("heaven");
    insert("heavy");

    cout << countWords("hea") << endl;
}