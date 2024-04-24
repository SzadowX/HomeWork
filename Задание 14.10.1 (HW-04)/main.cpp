#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

struct TrieNode {
    char c;
    bool isWord;
    TrieNode* children[26];

    TrieNode(char c) : c(c), isWord(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
public:
    Trie() : root(new TrieNode('\0')) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode(c);
            }
            node = node->children[index];
        }
        node->isWord = true;
    }

    void autocomplete(const string& prefix, string& result) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return;
            }
            node = node->children[index];
        }
        collectWords(node, prefix, result);
    }
    
private:
    TrieNode* root;

    void collectWords(TrieNode* node, const string& prefix, string& result) {
        if (node->isWord) {
            result += prefix + "\n";
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                collectWords(node->children[i], prefix + c, result);
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "");

    Trie trie;
    trie.insert("apple");
    trie.insert("application");
    trie.insert("banana");
    trie.insert("orange");
    trie.insert("apartment");

    string input;
    string suggestions;
    while (true) {
        cout << "Enter a word (or press Space for autocomplete): ";
        input.clear();
        while (true) {
            char c = _getch();
            if (c == 32) { // Space
                trie.autocomplete(input, suggestions);
                if (!suggestions.empty()) {
                    cout << endl;
                    cout << "Suggestions: " << endl;
                    cout << suggestions << endl;
                }
                else {
                    cout << "No suggestions found." << endl;
                }
                break;
            }
            else if (c == 13) { // Enter
                cout << endl;
                cout << "You entered: " << input << endl;
                break;
            }
            else if (c == 8) { // Backspace
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                input += c;
                cout << c;
            }
        }
    }
    return 0;
}