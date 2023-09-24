#include <iostream>
#include <memory>

using namespace std;

struct Object {
  string str;
  Object(string _str) : str(_str) {}
  ~Object() { cout << "destruct object\n"; }
};

// 使用很简单
// 1. shared_ptr<T> ptr(new T()) or shared_ptr<T> ptr = make_ptr<T>();
int main() {
  {
    shared_ptr<Object> p1 = make_shared<Object>("hello world!\n");
    shared_ptr<Object> p2 = make_shared<Object>("hello szs!\n");
    p1 = p2;
  }
  return 0;

}
