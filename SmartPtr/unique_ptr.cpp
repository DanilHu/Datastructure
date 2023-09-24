#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

// helper class for runtime polymorphism demo below
struct B {
  B() { std::cout << "B::B\n"; }
  virtual ~B() { std::cout << "B::~B\n"; }

  virtual void bar() { std::cout << "B::bar\n"; }
};

struct D : B {
  D() { std::cout << "D::D\n"; }
  ~D() { std::cout << "D::~D\n"; }

  void bar() override { std::cout << "D::bar\n"; }
};

// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p) {
  p->bar();
  return p;
}

// helper function for the custom deleter demo below
void close_file(std::FILE *fp) { std::fclose(fp); }

// unique_ptr-based linked list demo
struct List {
  struct Node {
    int data;
    std::unique_ptr<Node> next;
  };

  std::unique_ptr<Node> head;

  ~List() {
    // destroy list nodes sequentially in a loop, the default destructor
    // would have invoked its `next`'s destructor recursively, which would
    // cause stack overflow for sufficiently large lists.
    while (head) {
      auto next = std::move(head->next);
      head = std::move(next);
    }
  }

  void push(int data) {
    head = std::unique_ptr<Node>(new Node{data, std::move(head)});
  }
};

int main() {
  std::cout << "1) Unique ownership semantics demo\n";
  {
    // Create a (uniquely owned) resource
    std::unique_ptr<D> p = std::make_unique<D>();

    // Transfer ownership to `pass_through`,
    // which in turn transfers ownership back through the return value
    std::unique_ptr<D> q = pass_through(std::move(p));

    // p is now in a moved-from 'empty' state, equal to nullptr
    assert(!p);
  }

  std::cout << "\n"
               "2) Runtime polymorphism demo\n";
  {
    // Create a derived resource and point to it via base type
    std::unique_ptr<B> p = std::make_unique<B>();
    p = std::make_unique<D>();

    // Dynamic dispatch works as expected
    p->bar();
  }
  return 0;
}
