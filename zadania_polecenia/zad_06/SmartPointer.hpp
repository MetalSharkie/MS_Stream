#pragma once

template<typename T>
class SmartPointer {
private:
  class ReferenceCounter {
  private:
    int counter;
  public:
    ReferenceCounter() : counter(0) {}
    ReferenceCounter(int counter) : counter(counter) {}
    void add_ref() { counter++; }
    void del_ref() { counter--; }
    int count() { return counter; }
  };

  T* ptr;
  ReferenceCounter* counter;
public:
  SmartPointer() : ptr(nullptr), counter(new ReferenceCounter) {}
  SmartPointer(T* ptr) : ptr(ptr), counter(new ReferenceCounter(1)) {}
  SmartPointer(const SmartPointer<T>* ptr) : ptr(ptr), counter(counter) {
    counter->add_ref();
  }

  ~SmartPointer() {
    counter->del_ref();
    if (counter->count() == 0) {
      delete ptr;
      delete counter;
    }
  }
  
  SmartPointer<T>& operator=(SmartPointer<T>& rhs) {
    //TODO
  }

  T* operator*() {
    return ptr;
  }

  T* operator->() {
    return ptr;
  }

  operator bool() {
    //TODO
  }

  void reset() {
    //TODO
  }

  void reset(T* val) {
    //TODO
  }

  void swap(SmartPointer<T>& val) {
    //TODO
  }
};


template <typename T, typename... Args>
SmartPointer<T> make_smart_pointer(Args... args) {
  SmartPointer<T> p(new T(args...));
  return p;
}
