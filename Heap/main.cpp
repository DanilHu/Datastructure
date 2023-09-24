// 大顶堆的实现 已测试过
// STL里的大顶堆跟实现的一样：不提供遍历，无法查询，只能通过两个接口去操作堆结构
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

class BinaryHeap {
private:
  vector<int> heap_vec;
  int heapSz;

  void heapify(int index) {
    while (index < heapSz) {
      int left_index = 2 * index + 1;
      int right_index = 2 * index + 2;
      int max_index = index;
      if (left_index < heapSz && heap_vec[left_index] > heap_vec[max_index])
        max_index = left_index;
      if (right_index < heapSz && heap_vec[right_index] > heap_vec[max_index])
        max_index = right_index;
      if (max_index != index) {
        swap(heap_vec[index], heap_vec[max_index]);
        index = max_index;
      } else
        break;
    }
    return;
  }

  void heapInsert() {
    int index = heapSz - 1;
    while (index > 0) {
      int parent_index = (index % 2 == 0) ? index / 2 - 1 : index / 2;
      if (heap_vec[parent_index] < heap_vec[index]) {
        swap(heap_vec[parent_index], heap_vec[index]);
        index = parent_index;
      } else
        break;
    }
  }

public:
  BinaryHeap() : heap_vec(), heapSz(0) {}

  void insert(int val) {
    heap_vec.push_back(val);
    swap(heap_vec.back(), heap_vec[heapSz]);
    heapSz++;
    heapInsert();
  }

  void pop() {
    swap(heap_vec[0], heap_vec[heapSz - 1]);
    heapSz--;
    heapify(0);
  }

  int top() { return heap_vec[0]; }
};

int main() {
  BinaryHeap heap;
  heap.insert(1);
  heap.insert(3);
  heap.insert(5);
  heap.insert(2);
  heap.insert(9);
  heap.insert(4);
  cout << heap.top() << endl;
  heap.pop();
  heap.insert(6);
  cout << heap.top() << endl;
  return 0;
}
