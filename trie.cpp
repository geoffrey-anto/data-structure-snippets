#include<bits/stdc++.h>
using namespace std;

class Node {
    private:
    int n = 26;

    public:
    Node* ref[26];
    int prefix;
    int end;

    Node() {
        memset(ref, NULL, sizeof(ref));
        prefix = 0;
        end = 0;
    }

    bool contains(char a) {
        return (ref[a - 'a'] != nullptr);
    }

    void set(char a, Node* node) {
        ref[a - 'a'] = node;
    }

    Node* get(char a) {
        return ref[a - 'a'];
    } 

    void setPrefix() {
        prefix++;
    }

    void setEnd() {
        end++;
    }

    void eraseEnd() {
        end--;
    }

    void erasePrefix() {
        prefix--;
    }

    int getEnd() {
        return end;
    }

    int getPrefix() {
        return prefix;
    }
};

class Trie {
    public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string &s) {
        Node* temp = root;

        for(auto &ch: s) {
            if(!temp->contains(ch)) {
                Node* node = new Node();
                temp->set(ch, node);
            }
            temp = temp->get(ch);
            temp->setPrefix();
        }
        temp->setEnd();
    }

    int countWordsEqualTo(string &s) {
        Node* temp = root;

        for(auto &ch: s) {
            if(!temp->contains(ch)) {
                return 0;
            }
            temp = temp->get(ch);
        }

        return temp->getEnd();
    }

    int countWordsStartingWith(string &s) {
        Node* temp = root;

        for(auto &ch: s) {
            if(!temp->contains(ch)) {
                return 0;
            }
            temp = temp->get(ch);
        }

        return temp->getPrefix();
    }

    void erase(string &s) {
        Node* temp = root;

        for(auto &ch: s) {
            if(!temp->contains(ch)) {
                return;
            }

            temp = temp->get(ch);
            temp->erasePrefix();
        }

        temp->eraseEnd();
    }
};