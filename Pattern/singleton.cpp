#include<iostream>
#include<vector>

using namespace std;

class Singleton {
public:
  static Singleton& getInstance() {
    // return m_instance;
    static Singleton m_instance;
    return m_instance;
  }

  void print() {
    cout << "hello world\n";
  }

private:
  Singleton() {}
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  // static Singleton m_instance;
};

// Singleton Singleton::m_instance;

int main() {
  // 起一个别名为什么需要调用拷贝构造函数？你脑子给门挤了？
  // 这就是引用的实际用途
  Singleton& single = Singleton::getInstance();
  single.print();
  return 0;
}
