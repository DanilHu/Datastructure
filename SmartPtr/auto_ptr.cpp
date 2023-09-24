template <typename _Tp> class auto_ptr {
private:
  _Tp *_M_ptr; // auto_ptr对象使用_M_ptr_指向一个heap内的对象
public:
  typedef _Tp element_type;
  // 显式构造函数，接收一个原生指针来生成auto_ptr对象，不抛出异常（里面一定有异常处理机制）
  explicit auto_ptr(element_type *__p = 0) throw() : _M_ptr(__p) {}
  // 拷贝构造函数，只能接收一个作为左值的auto_ptr对象
  auto_ptr(auto_ptr &__a) throw() : _M_ptr(__a.release()) {}
  // 拷贝构造函数，兼容_Tp1*可以隐式转换为_Tp*的auto_ptr对象作为初值
  template <typename _Tp1>
  auto_ptr(auto_ptr<_Tp1> &__a) throw() : _M_ptr(__a.release()) {}
  // 拷贝赋值函数，同样只能接收一个作为左值的auto_ptr对象
  auto_ptr &operator=(auto_ptr &__a) throw() {
    reset(__a.release());
    return *this;
  }
  template <typename _Tp1>
  // 拷贝赋值函数，同样只能接收一个作为左值的auto_ptr对象
  auto_ptr &operator=(auto_ptr<_Tp1> &__a) throw() {
    reset(__a.release());
    return *this;
  }
  ~auto_ptr() { delete _M_ptr; }

  element_type &operator*() const throw() {
    __glibcxx_assert(_M_ptr != 0);
    return *_M_ptr;
  }

  element_type *operator->() const throw() {
    __glibcxx_assert(_M_ptr != 0);
    return _M_ptr;
  }

  element_type *get() const throw() { return _M_ptr; }
  element_type *release() throw() {
    element_type *__tmp = _M_ptr;
    _M_ptr = 0;
    return __tmp;
  }

  void reset(element_type *__p = 0) throw() {
    if (__p != _M_ptr) {
      delete _M_ptr;
      _M_ptr = __p;
    }
  }
};
