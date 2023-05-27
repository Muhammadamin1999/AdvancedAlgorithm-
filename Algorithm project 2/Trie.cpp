
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie {
public:
    Trie() {
        root = getNode();
    }

    void insert(string key)
    {
        TrieNode* pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                pCrawl->children[index] = getNode();

            pCrawl = pCrawl->children[index];
        }

        pCrawl->isEndOfWord = true;
    }

    bool search(string key)
    {
        TrieNode* pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }

        return (pCrawl->isEndOfWord);
    }

    ~Trie() {
        deleteNode(root);
        delete root;
    }

private:
    TrieNode* getNode()
    {
        TrieNode* node = new TrieNode;

        node->isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = nullptr;

        return node;
    }

    void deleteNode(TrieNode* node) {
        for (int x = 0; x < ALPHABET_SIZE; x++) {
            if (node->children[x] != nullptr) {
                deleteNode(node->children[x]);
                delete node->children[x];
            }
        }
    }

private:
    TrieNode* root;
};
