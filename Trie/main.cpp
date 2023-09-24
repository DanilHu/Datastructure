#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
  vector<Trie *> children;
  bool isEnd;

  Trie *searchPrefix(string prefix) {
    Trie *p = this;
    for (int i = 0; i < prefix.length(); i++) {
      int index = prefix[i] - 'a';
      if (p->children[index] == nullptr)
        return nullptr;
      p = p->children[index];
    }
    return p;
  }

public:
  Trie() {
    for (int i = 0; i < 26; i++)
      children.push_back(nullptr);
  }

  ~Trie() {
    for (int i = 0; i < 26; i++)
      delete children[i];
  }

  void insert(string word) {
    Trie *p = this;
    for (int i = 0; i < word.length(); i++) {
      int index = word[i] - 'a';
      if (p->children[index] == nullptr)
        p->children[index] = new Trie();
      p = p->children[index];
    }
    p->isEnd = true;
  }

  bool search(string word) {
    bool result = true;
    Trie *node = searchPrefix(word);
    return (node == nullptr) ? false : node->isEnd;
  }

  bool startsWith(string prefix) { return searchPrefix(prefix) != nullptr; }
};

int main() {
  Trie trie = Trie();
  trie.insert("apple");
  cout << trie.search("apple") << endl;
  cout << trie.search("app") << endl;
  cout << trie.startsWith("app") << endl;
  trie.insert("app");
  cout << trie.search("app") << endl;
}
