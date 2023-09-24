#include<iostream>
#include <unordered_map>
#include<vector>

#define ll long long

using namespace std;

struct ListNode {
    int key, val;
    ListNode* prev{nullptr};
    ListNode* next{nullptr};

    ListNode(int _key = 0, int _val = 0): key(_key), val(_val) {}
};

class LRU {
public:
    LRU(int _capacity): capacity(_capacity) {
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(!cache.count(key)) {
            return -1; 
        }
        ListNode* node = cache[key];
        removeNode(node);
        addToHead(node);
        return node->val;
    }

    void put(int key, int val) {
        if(cache.count(key)) {
            ListNode* node = cache[key];
            node->val = val;
            removeNode(node);
            addToHead(node);
        } else {
            ListNode* node = new ListNode(key, val);
            cache[key] = node;
            addToHead(node);
            size++;
            if(size > capacity) {
                ListNode* prev = removeNode(tail->prev);
                cache.erase(prev->key);
                size--;
            }
        }
    }

    ListNode* removeNode(ListNode* node) {
        ListNode* prev = node->prev;
        ListNode* next = node->next;
        prev->next = next;
        next->prev = prev;
        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    void addToHead(ListNode* node) {
        ListNode* firstNode = head->next;
        node->next = firstNode;
        node->prev = head;
        firstNode->prev = node;
        head->next = node;
    }


private:
    ListNode* head;
    ListNode* tail;
    int capacity{0}, size{0};
    unordered_map<int, ListNode*> cache;
};

int main() {

}