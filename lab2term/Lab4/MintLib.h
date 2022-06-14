#pragma once

#include <iostream>
#include <deque>

namespace MintLib {
    template<class T>  // simplest c++ 98 allocator
    struct allocator {
        typedef size_t size_type;

        T* allocate(size_type n) {
            return static_cast<T*> (::operator new(n * sizeof(T)));    // operator return void*
        }

        void deallocate(T* p, size_type n) {
            ::operator delete(p);
        }

        void construct(T* p, const T& value) {
            // placement new <-> called for address p contractor for
            // object with type T and parameter (value);
            ::new((void*)p) T(value);
        }

        void destroy(T* p) {
            p->~T();
        }
    };

    template<class T, class Alloc = MintLib::allocator<T>>
    class vector {
    private:
        T* arr = nullptr;
        size_t _size_ = 0;
        size_t _capacity_ = 2;
        Alloc alloc;

    public:
        size_t size() {
            return _size_;
        }

        vector() {
            arr = alloc.allocate(_capacity_);
        }

        ~vector() {
            alloc.deallocate(arr, _capacity_);
            arr = nullptr;
        }

        T& operator[](size_t index) { // for non const vector
            return arr[index];
        }

        const T& operator[](size_t index) const {  // for const vector
            return arr[index];
        }

        void push_back(const T& x) {
            if (_size_ < _capacity_) {
                alloc.construct(arr + _size_, x);
                ++_size_;
                return;
            }

            T* new_arr = alloc.allocate(_capacity_ * 2);
            for (size_t i = 0; i < _capacity_; ++i) {
                alloc.construct(new_arr + i, arr[i]);
            }
            alloc.construct(new_arr + _capacity_, x);
            ++_size_;
            for (size_t i = 0; i < _capacity_; ++i) {
                alloc.destroy(arr + i);
            }
            alloc.deallocate(arr, _capacity_);
            arr = new_arr;
            _capacity_ <<= 1;
        }

        void pop_back() {
            if (!_size_) {
                return;
            }
            --_size_;
            alloc.destroy(arr + _size_);
            if (!_size_) {
                arr = nullptr;
            }
        }

        T& back() {
            return arr[_size_ - 1];
        }

        bool empty() {
            return !_size_;
        }
    };

    template<class T, class container = std::deque<T>, class Alloc = MintLib::allocator<T>>
    class stack : private container {
    public:
        void push(const T& x) {
            container::push_back(x);
        }

        void pop() {
            container::pop_back();
        }

        T& top() {
            return container::back();
        }

        size_t size() {
            return container::size();
        }

        bool empty() {
            return container::empty();
        }
    };

}
namespace mtl = MintLib;
/*
template<class T>
void printVec(T& x) {
    if (x.size() == 0) {
        std::cout << "nothing";
    }
    for (int i = 0; i < x.size(); ++i) {
        std::cout << x[i] << ' ';
    }
    std::cout << '\n';
}

template<class T>
void printStack(T x) {
    if (x.size() == 0) {
        std::cout << "nothing";
    }
    while (!x.empty()) {
        std::cout << x.top() << ' ';
        x.pop();
    }
    std::cout << '\n';
}

int main() {
    mtl::stack<int, mtl::vector<int>> stack;
    for (int i = 0; i < 10; ++i) {
        stack.push(i + 1);
    }
    printStack(stack);

    std::cout << "---Vector Section---\n";
    mtl::vector<int> x;
    for (int i = 0; i < 10; ++i) {
        x.push_back(i + 1);
    }
    printVec(x);
    for (int i = 0; i < 20; ++i) {
        x.pop_back();
    }
    printVec(x);


    return 0;
}
*/
